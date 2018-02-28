#include "mainview.h"
#include "math.h"
#include "model.h"

#include <QDateTime>

/**
 * @brief MainView::MainView
 *
 * Constructor of MainView
 *
 * @param parent
 */
MainView::MainView(QWidget *parent) : QOpenGLWidget(parent) {
    qDebug() << "MainView constructor";

    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));

    // initialise to starting value of the scale slider
    currentScale            = 100;

    currentShadingMode      = 0;

    lightPosition     = QVector3D(10.0, 10.0, 0.0);
    lightColor        = QVector3D(1.0, 1.0, 1.0);
    materialColor     = QVector3D(1.0, 1.0, 1.0);
    materialIntensity = QVector3D(0.5, 0.8, 0.5);
    phongExponent     = 16;

    textureImage = imageToBytes(QImage(":/textures/cat_diff.png"));

    createObjectFromModel(":/models/cat.obj", QVector3D(0, 0, -5));

    // Initialise the transform matrices
    perspectiveMatrix.perspective(60.0,16.0/9.0,1,100);
}

void MainView::createObjectFromModel(QString filename, QVector3D translateVector){
    Model objectModel(filename);

    Shape model;

    // Set up model
    model.numVertices      = objectModel.getVertices().count();
    model.vertices         = (Vertex *)malloc(sizeof(Vertex)*model.numVertices);
    model.translateVector  = translateVector;

    // Retrieve model vertex data from model and insert into model struct, randomising colour
    // Vertex locations are scaled down to be in same range as the cube and pyramid
    for(int i = 0;i<model.numVertices;i++){
        model.vertices[i].x        = objectModel.getVertices().at(i).x();
        model.vertices[i].y        = objectModel.getVertices().at(i).y();
        model.vertices[i].z        = objectModel.getVertices().at(i).z();
        model.vertices[i].nx       = objectModel.getNormals().at(i).x();
        model.vertices[i].ny       = objectModel.getNormals().at(i).y();
        model.vertices[i].nz       = objectModel.getNormals().at(i).z();
        model.vertices[i].tx       = objectModel.getTextureCoords().at(i).x();
        model.vertices[i].ty       = objectModel.getTextureCoords().at(i).y();
    }

    model.modelMatrix.translate(model.translateVector);

    shapes.append(model);
}

/**
 * @brief MainView::~MainView
 *
 * Destructor of MainView
 * This is the last function called, before exit of the program
 * Use this to clean up your variables, buffers etc.
 *
 */
MainView::~MainView() {
    debugLogger->stopLogging();

    qDebug() << "MainView destructor";

    for(int i = 0;i < shapes.length();i++) {
        glDeleteBuffers(1, &shapes.data()[i].vbo);
        glDeleteBuffers(1, &shapes.data()[i].vao);
        free(shapes.data()[i].vertices);
    }
}

// --- OpenGL initialization

/**
 * @brief MainView::initializeGL
 *
 * Called upon OpenGL initialization
 * Attaches a debugger and calls other init functions
 */
void MainView::initializeGL() {
    qDebug() << ":: Initializing OpenGL";
    initializeOpenGLFunctions();

    debugLogger = new QOpenGLDebugLogger();
    connect( debugLogger, SIGNAL( messageLogged( QOpenGLDebugMessage ) ),
             this, SLOT( onMessageLogged( QOpenGLDebugMessage ) ), Qt::DirectConnection );

    if ( debugLogger->initialize() ) {
        qDebug() << ":: Logging initialized";
        debugLogger->startLogging( QOpenGLDebugLogger::SynchronousLogging );
        debugLogger->enableMessages();
    }

    QString glVersion;
    glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    qDebug() << ":: Using OpenGL" << qPrintable(glVersion);

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable backface culling
    glEnable(GL_CULL_FACE);

    // Default is GL_LESS
    glDepthFunc(GL_LEQUAL);

    // Set the color of the screen to be black on clear (new frame)
    glClearColor(0.2f, 0.5f, 0.7f, 0.0f);

    glGenTextures(1, &texturePointer);
    glBindTexture(GL_TEXTURE_2D, texturePointer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 512, 1024, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage.data());
    glGenerateMipmap(GL_TEXTURE_2D);

    createShaderProgram();

    // Initialise cube buffers
    for(int i=0; i<shapes.length(); i++) {
        glGenBuffers(1, &(shapes.data()[i].vbo));
        glGenVertexArrays(1, &(shapes.data()[i].vao));
        glBindVertexArray(shapes.data()[i].vao);
        glBindBuffer(GL_ARRAY_BUFFER, shapes.data()[i].vbo);
        glBufferData(GL_ARRAY_BUFFER, shapes.data()[i].numVertices*sizeof(Vertex), shapes.data()[i].vertices, GL_STATIC_DRAW);
        setVertexAttribs();
    }
}

void MainView::setVertexAttribs(){
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(3*sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(6*sizeof(float)));
}

void MainView::createShaderProgram()
{
    // Create shader program
    shaderProgramPhong.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           ":/shaders/vertshader_phong.glsl");
    shaderProgramPhong.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           ":/shaders/fragshader_phong.glsl");

    shaderProgramPhong.link();

    modelTransformLocation[MainView::PHONG]       = shaderProgramPhong.uniformLocation("modelTransform");
    perspectiveTransformLocation[MainView::PHONG] = shaderProgramPhong.uniformLocation("perspectiveTransform");
    normalTransformLocation[MainView::PHONG]      = shaderProgramPhong.uniformLocation("normalTransform");
    lightPositionLocation[MainView::PHONG]        = shaderProgramPhong.uniformLocation("lightPosition");
    lightColorLocation[MainView::PHONG]           = shaderProgramPhong.uniformLocation("lightColor");
    materialIntensityLocation[MainView::PHONG]    = shaderProgramPhong.uniformLocation("materialIntensity");
    materialColorLocation[MainView::PHONG]        = shaderProgramPhong.uniformLocation("materialColor");
    phongExponentLocation[MainView::PHONG]        = shaderProgramPhong.uniformLocation("phongExponent");
    texSamplerLocation[MainView::PHONG]           = shaderProgramPhong.uniformLocation("texSampler");

    // Create shader program
    shaderProgramNormal.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           ":/shaders/vertshader_normal.glsl");
    shaderProgramNormal.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           ":/shaders/fragshader_normal.glsl");

    shaderProgramNormal.link();

    modelTransformLocation[MainView::NORMAL]       = shaderProgramNormal.uniformLocation("modelTransform");
    perspectiveTransformLocation[MainView::NORMAL] = shaderProgramNormal.uniformLocation("perspectiveTransform");
    normalTransformLocation[MainView::NORMAL]      = shaderProgramNormal.uniformLocation("normalTransform");

    // Create shader program
    shaderProgramGouraud.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           ":/shaders/vertshader_gouraud.glsl");
    shaderProgramGouraud.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           ":/shaders/fragshader_gouraud.glsl");

    shaderProgramGouraud.link();

    modelTransformLocation[MainView::GOURAUD]       = shaderProgramGouraud.uniformLocation("modelTransform");
    perspectiveTransformLocation[MainView::GOURAUD] = shaderProgramGouraud.uniformLocation("perspectiveTransform");
    normalTransformLocation[MainView::GOURAUD]      = shaderProgramGouraud.uniformLocation("normalTransform");
    lightPositionLocation[MainView::GOURAUD]        = shaderProgramGouraud.uniformLocation("lightPosition");
    lightColorLocation[MainView::GOURAUD]           = shaderProgramGouraud.uniformLocation("lightColor");
    materialIntensityLocation[MainView::GOURAUD]    = shaderProgramGouraud.uniformLocation("materialIntensity");
    materialColorLocation[MainView::GOURAUD]        = shaderProgramGouraud.uniformLocation("materialColor");
    phongExponentLocation[MainView::GOURAUD]        = shaderProgramGouraud.uniformLocation("phongExponent");
    texSamplerLocation[MainView::GOURAUD]           = shaderProgramGouraud.uniformLocation("texSampler");
}

// --- OpenGL drawing

/**
 * @brief MainView::paintGL
 *
 * Actual function used for drawing to the screen
 *
 */
void MainView::paintGL() {
    QMatrix3x3 normalMatrix;

    // Clear the screen before rendering
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    switch(currentShadingMode){
        case MainView::PHONG:
            shaderProgramPhong.bind();
            break;
        case MainView::NORMAL:
            shaderProgramNormal.bind();
            break;
        case MainView::GOURAUD:
            shaderProgramGouraud.bind();
        break;
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texturePointer);

    // Fill perspective uniform with the perspective data
    glUniformMatrix4fv(perspectiveTransformLocation[currentShadingMode], 1, GL_FALSE, perspectiveMatrix.data());

    // For each shape, fill the model uniform with the model date, bind VAO and draw the shape
    for(int i=0; i<shapes.length(); i++) {
        normalMatrix = shapes.data()[i].modelMatrix.normalMatrix();
        glUniformMatrix4fv(perspectiveTransformLocation[currentShadingMode], 1, GL_FALSE, perspectiveMatrix.data());
        glUniformMatrix4fv(modelTransformLocation[currentShadingMode], 1, GL_FALSE, shapes.data()[i].modelMatrix.data());
        glUniformMatrix3fv(normalTransformLocation[currentShadingMode], 1, GL_FALSE, normalMatrix.data());
        if(currentShadingMode != MainView::NORMAL){
            glUniform3f(lightPositionLocation[currentShadingMode], lightPosition[0], lightPosition[1], lightPosition[2]);
            glUniform3f(lightColorLocation[currentShadingMode], lightColor[0], lightColor[1], lightColor[2]);
            glUniform3f(materialIntensityLocation[currentShadingMode], materialIntensity[0], materialIntensity[1], materialIntensity[2]);
            glUniform3f(materialColorLocation[currentShadingMode], materialColor[0],materialColor[1], materialColor[2]);
            glUniform1i(phongExponentLocation[currentShadingMode], phongExponent);
        }
        glBindVertexArray(shapes.data()[i].vao);
        glDrawArrays(GL_TRIANGLES, 0, shapes.data()[i].numVertices);
    }

    switch(currentShadingMode){
        case MainView::PHONG:
            shaderProgramPhong.release();
            break;
        case MainView::NORMAL:
            shaderProgramNormal.release();
            break;
        case MainView::GOURAUD:
            shaderProgramGouraud.release();
        break;
    }
}

/**
 * @brief MainView::resizeGL
 *
 * Called upon resizing of the screen
 *
 * @param newWidth
 * @param newHeight
 */
void MainView::resizeGL(int newWidth, int newHeight) 
{
    // Set new aspect ratio of the viewport
    perspectiveMatrix.setToIdentity();
    perspectiveMatrix.perspective(60.0,(float)newWidth/(float)newHeight,1,20);
}

// --- Public interface

void MainView::setRotation(int rotateX, int rotateY, int rotateZ)
{
    qDebug() << "Rotation changed to (" << rotateX << "," << rotateY << "," << rotateZ << ")";

    for(int i=0; i<shapes.length(); i++) {
        shapes.data()[i].rotateMatrix(rotateX, rotateY, rotateZ, currentScale/100);
    }

    update();
}

void MainView::setScale(int scale)
{
    qDebug() << "Scale changed to " << scale;

    // Calculate the relative change in scale; Keeps the scaling uniform
    float changeInScale = scale/currentScale;

    for(int i=0; i<shapes.length(); i++) {
        shapes.data()[i].modelMatrix.scale(changeInScale);
    }

    // Update the current scale
    currentScale = scale;

    update();
}

void MainView::setShadingMode(ShadingMode shading)
{
    qDebug() << "Changed shading to" << shading;
    currentShadingMode = shading;
    update();
}

void MainView::setMaterialColor(float color1, float color2, float color3)
{
    materialColor = QVector3D(color1,color2,color3);
    update();
}

void MainView::setLightPosition(double x, double y, double z)
{
    lightPosition = QVector3D(x,y,z);
    update();
}

void MainView::setPhongExponent(int i)
{
    phongExponent = i;
    update();
}

// --- Private helpers

/**
 * @brief MainView::onMessageLogged
 *
 * OpenGL logging function, do not change
 *
 * @param Message
 */
void MainView::onMessageLogged( QOpenGLDebugMessage Message ) {
    qDebug() << " → Log:" << Message;
}

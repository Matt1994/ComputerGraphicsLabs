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

}

void MainView::loadModel(QString filename, QVector3D translateVector){
    Model objectModel(filename);
    Shape object;

    // Set up model
    object.numVertices      = objectModel.getVertices().count();
    object.vertices         = (Vertex *)malloc(sizeof(Vertex)*object.numVertices);
    object.translateVector  = translateVector;

    // Retrieve model vertex data from model and insert into model struct
    // Data has been unitized when the model was created
    for(int i = 0;i<object.numVertices;i++){
        object.vertices[i].x  = objectModel.getVertices().at(i).x();
        object.vertices[i].y  = objectModel.getVertices().at(i).y();
        object.vertices[i].z  = objectModel.getVertices().at(i).z();
        object.vertices[i].nx = objectModel.getNormals().at(i).x();
        object.vertices[i].ny = objectModel.getNormals().at(i).y();
        object.vertices[i].nz = objectModel.getNormals().at(i).z();
        object.vertices[i].tx = objectModel.getTextureCoords().at(i).x();
        object.vertices[i].ty = objectModel.getTextureCoords().at(i).y();
    }

    object.modelMatrix.translate(object.translateVector);

    shapes.append(object);
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

    glDeleteTextures(1, &texturePointer);
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

    loadModel(":/models/cat.obj", QVector3D(0, 0, -5));

    perspectiveMatrix.perspective(60.0,width()/height(),1,100);

    glGenTextures(1, &texturePointer);
    loadTexture(":/textures/cat_diff.png", texturePointer);

    createShaderPrograms();

    // Initialise cube buffers
    for(int i=0; i<shapes.length(); i++) {
        glGenBuffers(1, &(shapes.data()[i].vbo));
        glGenVertexArrays(1, &(shapes.data()[i].vao));
        glBindVertexArray(shapes.data()[i].vao);
        glBindBuffer(GL_ARRAY_BUFFER, shapes.data()[i].vbo);
        glBufferData(GL_ARRAY_BUFFER, shapes.data()[i].numVertices*sizeof(Vertex), shapes.data()[i].vertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(3*sizeof(float)));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(6*sizeof(float)));
    }
}

void MainView::loadTexture(QString file, GLuint texturePtr)
{
    textureImage = imageToBytes(QImage(file));
    glBindTexture(GL_TEXTURE_2D, texturePtr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 512, 1024, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage.data());
    glGenerateMipmap(GL_TEXTURE_2D);
}

void MainView::createShaderPrograms()
{
    addShader(MainView::NORMAL, ":/shaders/vertshader_normal.glsl", ":/shaders/fragshader_normal.glsl");
    addShader(MainView::PHONG, ":/shaders/vertshader_phong.glsl", ":/shaders/fragshader_phong.glsl");
    addShader(MainView::GOURAUD, ":/shaders/vertshader_gouraud.glsl", ":/shaders/fragshader_gouraud.glsl");
}

void MainView::addShader(GLuint shader, QString vertexshader, QString fragshader)
{
    shaderPrograms[shader].addShaderFromSourceFile(QOpenGLShader::Vertex, vertexshader);
    shaderPrograms[shader].addShaderFromSourceFile(QOpenGLShader::Fragment, fragshader);

    shaderPrograms[shader].link();

    modelTransformLocation[shader]       = shaderPrograms[shader].uniformLocation("modelTransform");
    perspectiveTransformLocation[shader] = shaderPrograms[shader].uniformLocation("perspectiveTransform");
    normalTransformLocation[shader]      = shaderPrograms[shader].uniformLocation("normalTransform");
    if(shader != MainView::NORMAL){
        lightPositionLocation[shader]        = shaderPrograms[shader].uniformLocation("lightPosition");
        materialIntensityLocation[shader]    = shaderPrograms[shader].uniformLocation("materialIntensity");
        phongExponentLocation[shader]        = shaderPrograms[shader].uniformLocation("phongExponent");
        texSamplerLocation[shader]           = shaderPrograms[shader].uniformLocation("texSampler");
    }
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

    shaderPrograms[currentShadingMode].bind();

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
            glUniform3f(materialIntensityLocation[currentShadingMode], materialIntensity[0], materialIntensity[1], materialIntensity[2]);
            glUniform1i(phongExponentLocation[currentShadingMode], phongExponent);
        }
        glBindVertexArray(shapes.data()[i].vao);
        glDrawArrays(GL_TRIANGLES, 0, shapes.data()[i].numVertices);
    }

    shaderPrograms[currentShadingMode].release();
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

// Update uniforms

void MainView::setMaterialIntensity(float intensity1, float intensity2, float intensity3)
{
    materialIntensity = QVector3D(intensity1,intensity2,intensity3);
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

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

<<<<<<< HEAD
void MainView::loadModel(QString filename, QVector3D translateVector){
=======
void MainView::loadModel(QString filename, QVector3D translateVector, QString texture, float scale, float rotationSpeed){
>>>>>>> master
    Model objectModel(filename);
    Shape object;

    // Set up model
    object.numVertices      = objectModel.getVertices().count();
    object.vertices         = (Vertex *)malloc(sizeof(Vertex)*object.numVertices);
    object.translateVector  = translateVector;
<<<<<<< HEAD
=======
    object.texture          = texture;
    object.scale            = scale;
    object.rotationSpeed    = rotationSpeed;
>>>>>>> master

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
<<<<<<< HEAD
        free(shapes.data()[i].vertices);
    }

    glDeleteTextures(1, &texturePointer);
=======
        glDeleteTextures(1, &shapes.data()[i].texturePointer);
        free(shapes.data()[i].vertices);
    }
>>>>>>> master
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
<<<<<<< HEAD
    glClearColor(0.2f, 0.5f, 0.7f, 0.0f);

    loadModel(":/models/sphere.obj", QVector3D(0, 0, -5));

    perspectiveMatrix.perspective(60.0,width()/height(),1,100);

    glGenTextures(1, &texturePointer);
    loadTexture(":/textures/cat_diff.png", texturePointer);

    createShaderPrograms();

    // Initialise cube buffers
    for(int i=0; i<shapes.length(); i++) {
        glGenBuffers(1, &(shapes.data()[i].vbo));
        glGenVertexArrays(1, &(shapes.data()[i].vao));
=======
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    resizeGL(width(), height());

    loadModel(":/models/sphere.obj", QVector3D(2, 0, -5), ":/textures/earthmap1k.png", 0.2, 0.3);
    loadModel(":/models/sphere.obj", QVector3D(-2, 0, -5), ":/textures/jupiter2_1k.png", 0.4, 0.1);
    loadModel(":/models/sphere.obj", QVector3D(0, 0, -5), ":/textures/sunmap.jpg", 1, 0.05);

    createShaderPrograms();

    // Initialise model buffers
    for(int i=0; i<shapes.length(); i++) {
        glGenBuffers(1, &(shapes.data()[i].vbo));
        glGenVertexArrays(1, &(shapes.data()[i].vao));
        glGenTextures(1, &(shapes.data()[i].texturePointer));
>>>>>>> master
        glBindVertexArray(shapes.data()[i].vao);
        glBindBuffer(GL_ARRAY_BUFFER, shapes.data()[i].vbo);
        glBufferData(GL_ARRAY_BUFFER, shapes.data()[i].numVertices*sizeof(Vertex), shapes.data()[i].vertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(3*sizeof(float)));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(6*sizeof(float)));
<<<<<<< HEAD
    }
}

void MainView::loadTexture(QString file, GLuint texturePtr)
{
    textureImage = imageToBytes(QImage(file));
    glBindTexture(GL_TEXTURE_2D, texturePtr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 512, 1024, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage.data());
=======
        loadTexture(shapes.data()[i], shapes.data()[i].texture);
    }

    timer.start(1000.0 / 60.0);
}

void MainView::loadTexture(Shape shape, QString file)
{
    QImage image(file);
    shape.textureImage = imageToBytes(image);
    glBindTexture(GL_TEXTURE_2D, shape.texturePointer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, shape.textureImage.data());
>>>>>>> master
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
        lightColorLocation[shader]      	 = shaderPrograms[shader].uniformLocation("lightColor");
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
<<<<<<< HEAD
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
            glUniform3fv(lightPositionLocation[currentShadingMode], 1, lightPosition);
			glUniform3fv(lightColorLocation[currentShadingMode], 1, lightColor);
            glUniform3fv(materialIntensityLocation[currentShadingMode], 1, materialIntensity);
            glUniform1i(phongExponentLocation[currentShadingMode], phongExponent);
        }
        glBindVertexArray(shapes.data()[i].vao);
=======
    // Clear the screen before rendering
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(int i=0; i<shapes.length(); i++) {
       shapes.data()[i].rotation += shapes.data()[i].rotationSpeed;
       shapes.data()[i].updateModelMatrix();
    }

    shaderPrograms[currentShadingMode].bind();

    // Fill global uniforms
    glUniformMatrix4fv(perspectiveTransformLocation[currentShadingMode], 1, GL_FALSE, perspectiveMatrix.data());
    if(currentShadingMode != MainView::NORMAL){
        glUniform3fv(lightPositionLocation[currentShadingMode], 1, lightPosition);
        glUniform3fv(lightColorLocation[currentShadingMode], 1, lightColor);
        glUniform3fv(materialIntensityLocation[currentShadingMode], 1, materialIntensity);
        glUniform1i(phongExponentLocation[currentShadingMode], phongExponent);
    }

    // For each shape, bind buffers and texture,
    for(int i=0; i<shapes.length(); i++) {
        glBindVertexArray(shapes.data()[i].vao);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, shapes.data()[i].texturePointer);
        glUniformMatrix4fv(modelTransformLocation[currentShadingMode], 1, GL_FALSE, shapes.data()[i].modelMatrix.data());
        glUniformMatrix3fv(normalTransformLocation[currentShadingMode], 1, GL_FALSE, shapes.data()[i].modelMatrix.normalMatrix().data());
>>>>>>> master
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

<<<<<<< HEAD
    for(int i=0; i<shapes.length(); i++) {
        shapes.data()[i].rotateMatrix(rotateX, rotateY, rotateZ, currentScale/100);
    }
=======
    /*for(int i=0; i<shapes.length(); i++) {
        shapes.data()[i].rotateMatrix(rotateX, rotateY, rotateZ, currentScale/100);
    }*/
>>>>>>> master

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
    materialIntensity[0] = intensity1;
    materialIntensity[1] = intensity2;
    materialIntensity[2] = intensity3;
    update();
}

void MainView::setLightPosition(double x, double y, double z)
{
    lightPosition[0] = x;
    lightPosition[1] = y;
    lightPosition[2] = z;
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

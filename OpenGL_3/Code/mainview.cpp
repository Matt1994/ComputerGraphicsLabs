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

void MainView::CreateShapeFromModel(QString filename, QVector3D position, QString texture, float scale, float rotationSpeed, QVector3D orbitVector, float orbitSpeed){
    Model objectModel(filename);
    Shape object;

    // Set up model
    object.numVertices      = objectModel.getVertices().count();
    object.vertices         = (Vertex *)malloc(sizeof(Vertex)*object.numVertices);
    object.position         = position;
    object.texture          = texture;
    object.rotationSpeed    = rotationSpeed;
    object.orbitVector      = orbitVector;
    object.orbitSpeed       = orbitSpeed;

    // Retrieve model vertex data from model and insert into model struct
    // Data has been unitized when the model was created
    for(int i = 0;i<object.numVertices;i++){
        object.vertices[i].x  = objectModel.getVertices().at(i).x()*scale;
        object.vertices[i].y  = objectModel.getVertices().at(i).y()*scale;
        object.vertices[i].z  = objectModel.getVertices().at(i).z()*scale;
        object.vertices[i].nx = objectModel.getNormals().at(i).x();
        object.vertices[i].ny = objectModel.getNormals().at(i).y();
        object.vertices[i].nz = objectModel.getNormals().at(i).z();
        object.vertices[i].tx = objectModel.getTextureCoords().at(i).x();
        object.vertices[i].ty = objectModel.getTextureCoords().at(i).y();
    }

    object.modelMatrix.translate(object.position);

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
        glDeleteTextures(1, &shapes.data()[i].texturePointer);
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
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    resizeGL(width(), height());

    CreateShapeFromModel(":/models/cat.obj", QVector3D(0, 0, -10), ":/textures/sunmap.jpg", 3, 0.05, QVector3D(0,0,0), 0);
    CreateShapeFromModel(":/models/sphere.obj", QVector3D(0, 0, -10), ":/textures/mars1k.png", 0.3, 0.4, QVector3D(4,0,0), 0.6);
    CreateShapeFromModel(":/models/sphere.obj", QVector3D(0, 0, -10), ":/textures/earthmap1k.png", 0.4, 0.4, QVector3D(8,0,0), 0.3);
    CreateShapeFromModel(":/models/sphere.obj", QVector3D(0, 0, -10), ":/textures/jupiter2_1k.png", 0.6, 0.4, QVector3D(15,0,0), 0.1);

    createShaderPrograms();

    // Initialise model buffers
    for(int i=0; i<shapes.length(); i++) {
        glGenBuffers(1, &(shapes.data()[i].vbo));
        glGenVertexArrays(1, &(shapes.data()[i].vao));
        glGenTextures(1, &(shapes.data()[i].texturePointer));
        glBindVertexArray(shapes.data()[i].vao);
        glBindBuffer(GL_ARRAY_BUFFER, shapes.data()[i].vbo);
        glBufferData(GL_ARRAY_BUFFER, shapes.data()[i].numVertices*sizeof(Vertex), shapes.data()[i].vertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(3*sizeof(float)));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(6*sizeof(float)));
        loadTexture(shapes.data()[i], shapes.data()[i].texture);
    }

    updateViewMatrix();

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
    viewTransformLocation[shader]        = shaderPrograms[shader].uniformLocation("viewTransform");

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
    // Clear the screen before rendering
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(int i=0; i<shapes.length(); i++) {
       shapes.data()[i].updateModelMatrix();
    }

    shaderPrograms[currentShadingMode].bind();

    // Fill global uniforms
    glUniformMatrix4fv(perspectiveTransformLocation[currentShadingMode], 1, GL_FALSE, perspectiveMatrix.data());
    glUniformMatrix4fv(viewTransformLocation[currentShadingMode], 1, GL_FALSE, viewMatrix.data());
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
    perspectiveMatrix.perspective(60.0,(float)newWidth/(float)newHeight,1,300);
}

// --- Public interface

void MainView::setRotation(int rotateX, int rotateY, int rotateZ)
{
    currentRotateX = rotateX;
    currentRotateY = rotateY;
    currentRotateZ = rotateZ;
    updateViewMatrix();
}

void MainView::setZoom(int zoom)
{
    if(zoom >= 0 && zoom <= 100) currentZoom = zoom;
    updateViewMatrix();
}

void MainView::updateViewMatrix()
{
    viewMatrix.setToIdentity();
    viewMatrix.translate(QVector3D(0,0,currentZoom-100-10));
    viewMatrix.rotate(currentRotateX,1,0,0);
    viewMatrix.rotate(currentRotateY,0,1,0);
    viewMatrix.rotate(currentRotateZ,0,0,1);
    viewMatrix.translate(QVector3D(0,0,10));
}

void MainView::setShadingMode(ShadingMode shading)
{
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

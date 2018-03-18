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

    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));}

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
    // Default is GL_LESS
    glDepthFunc(GL_LEQUAL);
    // Set the color of the screen to be black on clear (new frame)
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    resizeGL(width(), height());

    centerPoint = QVector3D(0,0,-5);

    createShapeFromModel(":/models/grid.obj", QVector3D(0,0,-5), 1);

    createShaderPrograms();

    updateViewMatrix();

    timer.start(1000.0 / 60.0);
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
    perspectiveMatrix.setToIdentity();
    perspectiveMatrix.perspective(60.0,(float)newWidth/(float)newHeight,1,300);
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

    time += (0.0167*speed);

    // Update model matrix of each shape
    for(int i=0; i<shapes.length(); i++) {
       shapes.data()[i].updateModelMatrix();
    }

    shaderPrograms[currentShadingMode].bind();

    // Fill global uniforms
    glUniformMatrix4fv(perspectiveTransformLocation[currentShadingMode], 1, GL_FALSE, perspectiveMatrix.data());
    glUniformMatrix4fv(viewTransformLocation[currentShadingMode], 1, GL_FALSE, viewMatrix.data());
    if(currentShadingMode != MainView::WAVE){
        glUniform3fv(lightPositionLocation[currentShadingMode], 1, lightPosition);
        glUniform3fv(lightColorLocation[currentShadingMode], 1, lightColor);
        glUniform3fv(materialIntensityLocation[currentShadingMode], 1, materialIntensity);
        glUniform1i(phongExponentLocation[currentShadingMode], phongExponent);
    }

    glUniform1fv(amplitudeLocation[currentShadingMode], 5, amplitude);
    glUniform1fv(frequencyLocation[currentShadingMode], 5, frequency);
    glUniform1fv(phaseLocation[currentShadingMode], 5, phase);
    glUniform1f(timeLocation[currentShadingMode], time);

    // For each shape, bind buffers and texture,
    for(int i=0; i<shapes.length(); i++) {
        glBindVertexArray(shapes.data()[i].vao);
        glUniformMatrix4fv(modelTransformLocation[currentShadingMode], 1, GL_FALSE, shapes.data()[i].modelMatrix.data());
        glDrawArrays(GL_TRIANGLES, 0, shapes.data()[i].numVertices);
    }

    shaderPrograms[currentShadingMode].release();
}

/**
 * @brief MainView::setRotation
 *
 * Set the current rotation of the scene
 *
 * @param rotateX
 * @param rotateY
 * @param rotateZ
 */

void MainView::setRotation(int rotateX, int rotateY, int rotateZ)
{

    currentRotateX = rotateX;
    currentRotateY = rotateY;
    currentRotateZ = rotateZ;
    updateViewMatrix();
}

/**
 * @brief MainView::setTimeSpeed
 *
 * Set the time speed of the scene
 *
 * @param speed
 */

void MainView::setTimeSpeed(int value)
{
    speed = value;
}


/**
 * @brief MainView::updateViewMatrix
 *
 * Update the view matrix to current zoom and rotation
 *
 */

void MainView::updateViewMatrix()
{
    viewMatrix.setToIdentity();
    viewMatrix.translate(centerPoint);
    viewMatrix.rotate(currentRotateX,1,0,0);
    viewMatrix.rotate(currentRotateY,0,1,0);
    viewMatrix.rotate(currentRotateZ,0,0,1);
    viewMatrix.translate(-centerPoint);
}

/**
 * @brief MainView::setShadingMode
 *
 * Set the current shading
 *
 * @param shading
 *
 */

void MainView::setShadingMode(ShadingMode shading)
{
    currentShadingMode = shading;
}

// Update uniforms

void MainView::setMaterialIntensity(float intensity1, float intensity2, float intensity3)
{
    materialIntensity[0] = intensity1;
    materialIntensity[1] = intensity2;
    materialIntensity[2] = intensity3;
}

void MainView::setLightPosition(double x, double y, double z)
{
    lightPosition[0] = x;
    lightPosition[1] = y;
    lightPosition[2] = z;
}

void MainView::setPhongExponent(int i)
{
    phongExponent = i;
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

/**
 * @brief MainView::createShapeFromModel
 *
 * Create new shape from given model, position and scale
 *
 * @param modelFileName
 * @param position
 * @param scale
 */

void MainView::createShapeFromModel(QString modelFileName, QVector3D position, float scale){
    Model objectModel(modelFileName);
    Shape object;

    // Set up model
    object.numVertices = objectModel.getVertices().count();
    object.position    = position;

    object.modelMatrix.translate(position);

    // Retrieve vertex data from model and insert into shape
    for(int i = 0;i<object.numVertices;i++){
        Vertex v;
        v.setCoords(objectModel.getVertices().at(i)*scale);
        v.setNormalCoords(objectModel.getNormals().at(i));
        v.setTextureCoords(objectModel.getTextureCoords().at(i));
        object.vertices.append(v);
    }

    initializeVBO(&object);
    initializeVAO(&object);

    shapes.append(object);
}

void MainView::initializeVBO(Shape* shape){
   glGenBuffers(1, &(shape->vbo));
   glBindBuffer(GL_ARRAY_BUFFER, shape->vbo);
   glBufferData(GL_ARRAY_BUFFER, shape->numVertices*sizeof(Vertex), shape->vertices.data(), GL_STATIC_DRAW);
}

void MainView::initializeVAO(Shape* shape){
    glGenVertexArrays(1, &(shape->vao));
    glBindVertexArray(shape->vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(3*sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(6*sizeof(float)));
}

void MainView::createShaderPrograms()
{
    addShader(MainView::PHONG, ":/shaders/vertshader_phong.glsl", ":/shaders/fragshader_phong.glsl");
    addShader(MainView::WAVE, ":/shaders/vertshader_wave.glsl", ":/shaders/fragshader_wave.glsl");
}

void MainView::addShader(GLuint shader, QString vertexshader, QString fragshader)
{
    shaderPrograms[shader].addShaderFromSourceFile(QOpenGLShader::Vertex, vertexshader);
    shaderPrograms[shader].addShaderFromSourceFile(QOpenGLShader::Fragment, fragshader);

    shaderPrograms[shader].link();

    modelTransformLocation[shader]       = shaderPrograms[shader].uniformLocation("modelTransform");
    perspectiveTransformLocation[shader] = shaderPrograms[shader].uniformLocation("perspectiveTransform");
    viewTransformLocation[shader]        = shaderPrograms[shader].uniformLocation("viewTransform");

    amplitudeLocation[shader]       = shaderPrograms[shader].uniformLocation("amplitude");
    frequencyLocation[shader]       = shaderPrograms[shader].uniformLocation("frequency");
    phaseLocation[shader]           = shaderPrograms[shader].uniformLocation("phase");
    timeLocation[shader]            = shaderPrograms[shader].uniformLocation("time");

    if(shader != MainView::WAVE){
        lightPositionLocation[shader]        = shaderPrograms[shader].uniformLocation("lightPosition");
        lightColorLocation[shader]      	 = shaderPrograms[shader].uniformLocation("lightColor");
        materialIntensityLocation[shader]    = shaderPrograms[shader].uniformLocation("materialIntensity");
        phongExponentLocation[shader]        = shaderPrograms[shader].uniformLocation("phongExponent");
    }
}

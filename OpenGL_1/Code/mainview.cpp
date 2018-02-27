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

    Model sphereModel(":/models/sphere.obj");

    // initialise to starting value of the scale slider
    currentScale            = 100;

    // Set up cube
    cube.numVertices        = 36;
    cube.vertices           = (Vertex *)malloc(sizeof(Vertex)*cube.numVertices);
    cube.translateVector    = QVector3D(2,0,-6);

    //Cube Front Face
    cube.vertices[0]        = {-1,1,1,1,0,0};
    cube.vertices[1]        = {-1,-1,1,1,1,0};
    cube.vertices[2]        = {1,1,1,1,0,0};

    cube.vertices[3]        = {1,1,1,1,0,0};
    cube.vertices[4]        = {-1,-1,1,1,1,0};
    cube.vertices[5]        = {1,-1,1,0,1,1};

    //Cube Back Face
    cube.vertices[6]        = {1,1,-1,0,0,1};
    cube.vertices[7]        = {1,-1,-1,0,1,0};
    cube.vertices[8]        = {-1,1,-1,1,0,1};

    cube.vertices[9]        = {-1,1,-1,1,0,1};
    cube.vertices[10]       = {1,-1,-1,0,1,0};
    cube.vertices[11]       = {-1,-1,-1,0,1,0};

    //Cube Left Face
    cube.vertices[12]       = {-1,1,-1,1,0,1};
    cube.vertices[13]       = {-1,-1,-1,0,1,0};
    cube.vertices[14]       = {-1,1,1,1,0,0};

    cube.vertices[15]       = {-1,1,1,1,0,0};
    cube.vertices[16]       = {-1,-1,-1,0,1,0};
    cube.vertices[17]       = {-1,-1,1,1,1,0};

    //Cube Right Face
    cube.vertices[18]       = {1,1,1,1,0,0};
    cube.vertices[19]       = {1,-1,1,0,1,1};
    cube.vertices[20]       = {1,1,-1,0,0,1};

    cube.vertices[21]       = {1,1,-1,0,0,1};
    cube.vertices[22]       = {1,-1,1,0,1,1};
    cube.vertices[23]       = {1,-1,-1,0,1,0};

    //Cube Top Face
    cube.vertices[24]       = {-1,1,1,1,0,0};
    cube.vertices[25]       = {1,1,1,1,0,0};
    cube.vertices[26]       = {-1,1,-1,1,0,1};

    cube.vertices[27]       = {1,1,1,1,0,0};
    cube.vertices[28]       = {1,1,-1,0,0,1};
    cube.vertices[29]       = {-1,1,-1,1,0,1};

    //Cube Bottom Face
    cube.vertices[30]       = {1,-1,1,0,1,1};
    cube.vertices[31]       = {-1,-1,1,1,1,0};
    cube.vertices[32]       = {1,-1,-1,0,1,0};

    cube.vertices[33]       = {-1,-1,1,1,1,0};
    cube.vertices[34]       = {-1,-1,-1,0,1,0};
    cube.vertices[35]       = {1,-1,-1,0,1,0};

    // Set up pyramid
    pyramid.numVertices     = 18;
    pyramid.vertices        = (Vertex *)malloc(sizeof(Vertex)*pyramid.numVertices);
    pyramid.translateVector = QVector3D(-2,0,-6);

    //Pyramid Front Face
    pyramid.vertices[0]     = {0,1,0,1,0,0};
    pyramid.vertices[1]     = {-1,-1,1,1,1,0};
    pyramid.vertices[2]     = {1,-1,1,0,1,0};

    //Pyramid Right Face
    pyramid.vertices[3]     = {0,1,0,1,0,0};
    pyramid.vertices[4]     = {1,-1,1,0,1,0};
    pyramid.vertices[5]     = {1,-1,-1,0,1,1};

    //Pyramid Back Face
    pyramid.vertices[6]     = {0,1,0,1,0,0};
    pyramid.vertices[7]     = {1,-1,-1,0,1,1};
    pyramid.vertices[8]     = {-1,-1,-1,0,0,1};

    //Pyramid Left Face
    pyramid.vertices[9]     = {0,1,0,1,0,0};
    pyramid.vertices[10]    = {-1,-1,-1,0,0,1};
    pyramid.vertices[11]    = {-1,-1,1,1,1,0};

    //Pyramid Bottom Face
    pyramid.vertices[12]    = {-1,-1,1,1,1,0};
    pyramid.vertices[13]    = {-1,-1,-1,0,0,1};
    pyramid.vertices[14]    = {1,-1,1,0,1,0};

    pyramid.vertices[15]    = {1,-1,1,0,1,0};
    pyramid.vertices[16]    = {-1,-1,-1,0,0,1};
    pyramid.vertices[17]    = {1,-1,-1,0,1,1};

    // Set up sphere
    sphere.numVertices      = sphereModel.getVertices().count();
    sphere.vertices         = (Vertex *)malloc(sizeof(Vertex)*sphere.numVertices);
    sphere.translateVector  = QVector3D(0,0,-10);

    // Retrieve sphere vertex data from model and insert into sphere struct, randomising colour
    // Vertex locations are scaled down to be in same range as the cube and pyramid
    for(int i = 0;i<sphere.numVertices;i++){
        sphere.vertices[i].x        = sphereModel.getVertices().at(i).x()*0.04;
        sphere.vertices[i].y        = sphereModel.getVertices().at(i).y()*0.04;
        sphere.vertices[i].z        = sphereModel.getVertices().at(i).z()*0.04;
        sphere.vertices[i].red      = (float)rand() / RAND_MAX;
        sphere.vertices[i].blue     = (float)rand() / RAND_MAX;
        sphere.vertices[i].green    = (float)rand() / RAND_MAX;
    }

    // Initialise the transform matrices
    perspectiveMatrix.perspective(60.0,16.0/9.0,1,100);
    cube.modelMatrix.translate(cube.translateVector);
    pyramid.modelMatrix.translate(pyramid.translateVector);
    sphere.modelMatrix.translate(sphere.translateVector);
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

    // Delete the shape buffers
    glDeleteBuffers(1, &cube.vbo);
    glDeleteBuffers(1, &cube.vao);
    glDeleteBuffers(1, &pyramid.vbo);
    glDeleteBuffers(1, &pyramid.vao);
    glDeleteBuffers(1, &sphere.vbo);
    glDeleteBuffers(1, &sphere.vao);

    // Free memory allocated for each shape's vertices
    free(cube.vertices);
    free(pyramid.vertices);
    free(sphere.vertices);
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

    createShaderProgram();

    // Initialise cube buffers
    glGenBuffers(1, &cube.vbo);
    glGenVertexArrays(1, &cube.vao);
    glBindVertexArray(cube.vao);
    glBindBuffer(GL_ARRAY_BUFFER, cube.vbo);
    glBufferData(GL_ARRAY_BUFFER, cube.numVertices*sizeof(Vertex), cube.vertices, GL_STATIC_DRAW);
    setVertexAttribs();

    // Initialise pyramid buffers
    glGenBuffers(1, &pyramid.vbo);
    glGenVertexArrays(1, &pyramid.vao);
    glBindVertexArray(pyramid.vao);
    glBindBuffer(GL_ARRAY_BUFFER, pyramid.vbo);
    glBufferData(GL_ARRAY_BUFFER, pyramid.numVertices*sizeof(Vertex), pyramid.vertices, GL_STATIC_DRAW);
    setVertexAttribs();

    // Initialise sphere buffers
    glGenBuffers(1, &sphere.vbo);
    glGenVertexArrays(1, &sphere.vao);
    glBindVertexArray(sphere.vao);
    glBindBuffer(GL_ARRAY_BUFFER, sphere.vbo);
    glBufferData(GL_ARRAY_BUFFER, sphere.numVertices*sizeof(Vertex), sphere.vertices, GL_STATIC_DRAW);
    setVertexAttribs();
}

void MainView::setVertexAttribs(){
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(3*sizeof(float)));
}

void MainView::createShaderProgram()
{
    // Create shader program
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           ":/shaders/vertshader.glsl");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           ":/shaders/fragshader.glsl");
    shaderProgram.link();

    // Set the locations of the Vertex Shader's uniforms
    modelTransformLocation = shaderProgram.uniformLocation("modelTransform");
    perspectiveTransformLocation = shaderProgram.uniformLocation("perspectiveTransform");

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

    shaderProgram.bind();

    // Fill perspective uniform with the perspective data
    glUniformMatrix4fv(perspectiveTransformLocation, 1, GL_FALSE, perspectiveMatrix.data());

    // For each shape, fill the model uniform with the model date, bind VAO and draw the shape
    glUniformMatrix4fv(modelTransformLocation, 1, GL_FALSE, cube.modelMatrix.data());
    glBindVertexArray(cube.vao);
    glDrawArrays(GL_TRIANGLES, 0, cube.numVertices);

    glUniformMatrix4fv(modelTransformLocation, 1, GL_FALSE, pyramid.modelMatrix.data());
    glBindVertexArray(pyramid.vao);
    glDrawArrays(GL_TRIANGLES, 0, pyramid.numVertices);

    glUniformMatrix4fv(modelTransformLocation, 1, GL_FALSE, sphere.modelMatrix.data());
    glBindVertexArray(sphere.vao);
    glDrawArrays(GL_TRIANGLES, 0, sphere.numVertices);

    shaderProgram.release();
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

    cube.rotateMatrix(rotateX, rotateY, rotateZ, currentScale/100);
    pyramid.rotateMatrix(rotateX, rotateY, rotateZ, currentScale/100);
    sphere.rotateMatrix(rotateX, rotateY, rotateZ, currentScale/100);

    update();
}

void MainView::setScale(int scale)
{
    qDebug() << "Scale changed to " << scale;

    // Calculate the relative change in scale; Keeps the scaling uniform
    float changeInScale = scale/currentScale;

    cube.modelMatrix.scale(changeInScale);
    pyramid.modelMatrix.scale(changeInScale);
    sphere.modelMatrix.scale(changeInScale);

    // Update the current scale
    currentScale        = scale;

    update();
}

void MainView::setShadingMode(ShadingMode shading)
{
    qDebug() << "Changed shading to" << shading;
    Q_UNIMPLEMENTED();
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

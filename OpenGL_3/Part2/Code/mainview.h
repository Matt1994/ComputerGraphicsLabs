#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "model.h"
#include "vertex.h"
#include "shape.h"

#include <QKeyEvent>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLDebugLogger>
#include <QOpenGLShaderProgram>
#include <QTimer>
#include <QMatrix4x4>
#include <QVector3D>
#include <memory>

class MainView : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core {
    Q_OBJECT

    QOpenGLDebugLogger *debugLogger;

    QTimer timer; // timer used for animation

    QOpenGLShaderProgram shaderPrograms[4];

    GLfloat lightPosition[3] = {0.0, 0.0, 10.0},
            lightColor[3] = {1.0, 1.0, 1.0},
            materialIntensity[3] = {0.2, 0.8, 0.5};

    int phongExponent = 16, speed=1;

    GLuint currentShadingMode = 0;

    QVector<Shape> shapes;

    QVector3D centerPoint;

    QMatrix4x4 perspectiveMatrix,
               viewMatrix;

    GLint modelTransformLocation[2],
          perspectiveTransformLocation[2],
          lightPositionLocation[2],
          lightColorLocation[2],
          amplitudeLocation[2],
          frequencyLocation[2],
          phaseLocation[2],
          timeLocation[2],
          materialIntensityLocation[2],
          phongExponentLocation[2],
          viewTransformLocation[2];

    float currentRotateX=0,
          currentRotateY=0,
          currentRotateZ=0;

    float amplitude[5] = {0.01,0.005,0.035,0.01,0.025};
    float frequency[5] = {1,2,3,4,5};
    float phase[5] = {0,0,0.5,1.4,0.7};

    float time = 0;

public:
    enum ShadingMode : GLuint
    {
        PHONG = 0, WAVE
    };

    MainView(QWidget *parent = 0);
    ~MainView();

    // Functions for widget input events
    void setRotation(int rotateX, int rotateY, int rotateZ);
    void setTimeSpeed(int value);
    void updateViewMatrix();
    void setShadingMode(ShadingMode shading);
    void setMaterialIntensity(float intensity1, float intensity2, float intensity3);
    void setLightPosition(double x, double y, double z);
    void setPhongExponent(int i);

    QVector<quint8> imageToBytes(QImage image);

protected:
    void initializeGL();
    void resizeGL(int newWidth, int newHeight);
    void paintGL();

    // Functions for keyboard input events
    void keyPressEvent(QKeyEvent *ev);
    void keyReleaseEvent(QKeyEvent *ev);

    // Function for mouse input events
    void mouseDoubleClickEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void wheelEvent(QWheelEvent *ev);

private slots:
    void onMessageLogged( QOpenGLDebugMessage Message );

private:
    void initializeVBO(Shape* shape);
    void initializeVAO(Shape* shape);
    void createShaderPrograms();
    void addShader(GLuint shader, QString vertexshader, QString fragshader);
    void createShapeFromModel(QString filename, QVector3D translateVector, float scale);
};

#endif // MAINVIEW_H

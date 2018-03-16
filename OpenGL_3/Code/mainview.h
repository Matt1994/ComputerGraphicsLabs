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

    QOpenGLShaderProgram shaderPrograms[3];

    GLfloat lightPosition[3] = {0.0, 0.0, 10.0};
    GLfloat lightColor[3] = {1.0, 1.0, 1.0};
    GLfloat materialIntensity[3] = {0.2, 0.8, 0.5};
    int phongExponent = 16;

    GLuint currentShadingMode = 0;

    QVector<Shape> shapes;

    QMatrix4x4 perspectiveMatrix;
    QMatrix4x4 viewMatrix;

    GLint modelTransformLocation[3];
    GLint perspectiveTransformLocation[3];
    GLint normalTransformLocation[3];
    GLint lightPositionLocation[3];
    GLint lightColorLocation[3];
    GLint materialIntensityLocation[3];
    GLint phongExponentLocation[3];
    GLint texSamplerLocation[3];
    GLint viewTransformLocation[3];

    float currentRotateX=0, currentRotateY=0, currentRotateZ=0, currentZoom=50;

public:
    enum ShadingMode : GLuint
    {
        PHONG = 0, NORMAL, GOURAUD
    };

    MainView(QWidget *parent = 0);
    ~MainView();

    // Functions for widget input events
    void setRotation(int rotateX, int rotateY, int rotateZ);
    void setZoom(int zoom);
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
    void createShaderPrograms();
    void addShader(GLuint shader, QString vertexshader, QString fragshader);
    void loadTexture(Shape shape, QString file);
    void CreateShapeFromModel(QString filename, QVector3D translateVector, QString texture, float scale, float rotationSpeed, QVector3D orbitVector, float orbitSpeed);
};

#endif // MAINVIEW_H

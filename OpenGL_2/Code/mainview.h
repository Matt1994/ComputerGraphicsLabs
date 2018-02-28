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

    QOpenGLShaderProgram shaderProgramNormal;
    QOpenGLShaderProgram shaderProgramPhong;
    QOpenGLShaderProgram shaderProgramGouraud;

    QVector3D lightPosition;
    QVector3D lightColor;
    QVector3D materialColor;
    QVector3D materialIntensity;
    int phongExponent;

    GLuint currentShadingMode;

//    Shape cube;
//    Shape pyramid;
//    Shape model;

    QVector<Shape> shapes;

    QMatrix4x4 perspectiveMatrix;

    GLint modelTransformLocation;
    GLint perspectiveTransformLocation;
    GLint normalTransformLocation;
    GLint lightPositionLocation;
    GLint lightColorLocation;
    GLint materialIntensityLocation;
    GLint materialColorLocation;
    GLint phongExponentLocation;

    QVector<quint8> textureImage;
    GLuint texturePointer;

    float currentScale;

public:
    enum ShadingMode : GLuint
    {
        PHONG = 0, NORMAL, GOURAUD
    };

    MainView(QWidget *parent = 0);
    ~MainView();

    // Functions for widget input events
    void setRotation(int rotateX, int rotateY, int rotateZ);
    void setScale(int scale);
    void setShadingMode(ShadingMode shading);
    void setMaterialColor(float color1, float color2, float color3);
    void setLightPosition(double x, double y, double z);
    void setPhongExponent(int i);

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
    void createShaderProgram();
    void setVertexAttribs();
    void createCube(QVector3D translateVector);
    void createPyramid(QVector3D translateVector);
    void createObjectFromModel(QString filename, QVector3D translateVector);
};

#endif // MAINVIEW_H

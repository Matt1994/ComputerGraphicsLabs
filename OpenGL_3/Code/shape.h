#ifndef SHAPE
#define SHAPE

#include <QOpenGLFunctions_3_3_Core>
#include <QMatrix4x4>
#include <QVector3D>
#include "vertex.h"

struct Shape {
    GLuint vbo;
    GLuint vao;
    QMatrix4x4 modelMatrix;
    QVector3D translateVector;

<<<<<<< HEAD
    Vertex *vertices;
    int numVertices;

    void rotateMatrix(int x, int y, int z, float scale){
        modelMatrix.setToIdentity();
        modelMatrix.translate(translateVector);
        modelMatrix.scale(scale);
        modelMatrix.rotate(x,1,0,0);
        modelMatrix.rotate(y,0,1,0);
        modelMatrix.rotate(z,0,0,1);
=======
    QVector<quint8> textureImage;
    GLuint texturePointer;
    QString texture;

    float scale;
    float rotation = 0;
    float rotationSpeed;

    Vertex *vertices;
    int numVertices;

    void updateModelMatrix(){
        modelMatrix.setToIdentity();
        modelMatrix.translate(translateVector);
        modelMatrix.scale(scale);
        modelMatrix.rotate(rotation,0,1,0);
>>>>>>> master
    }
};

#endif // SHAPE


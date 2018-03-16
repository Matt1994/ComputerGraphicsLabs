#ifndef SHAPE
#define SHAPE

#include <QOpenGLFunctions_3_3_Core>
#include <QMatrix4x4>
#include <QVector3D>
#include "vertex.h"

struct Shape {
    GLuint vbo, vao, texturePointer;
    QMatrix4x4 modelMatrix, orbitMatrix;
    QVector3D position, translateVector, orbitVector;
    QVector<quint8> textureImage;
    QString texture;
    float rotation = 0, orbitAngle = 0, rotationSpeed, orbitSpeed;
    Vertex *vertices;
    int numVertices;

    bool hasChild = false;
    int child;
    QVector3D parent;

    void updateModelMatrix(){
        modelMatrix.setToIdentity();

        rotation += rotationSpeed;
        orbitMatrix.rotate(orbitSpeed,0,1,0);
        translateVector = (orbitMatrix*orbitVector) + position;

        modelMatrix.translate(translateVector);
        modelMatrix.rotate(rotation,0,1,0);
    }


};

#endif // SHAPE


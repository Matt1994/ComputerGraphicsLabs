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
    QMatrix4x4 orbitMatrix;
    QVector3D position;

    QVector3D translateVector;

    QVector<quint8> textureImage;
    GLuint texturePointer;
    QString texture;

    float scale;
    float rotation = 0;
    float orbitAngle = 0;

    float rotationSpeed;
    float orbitSpeed;
    QVector3D orbitVector;

    Vertex *vertices;
    int numVertices;

    void updateModelMatrix(){
        modelMatrix.setToIdentity();
        orbitMatrix.setToIdentity();

        orbitAngle += orbitSpeed;
        orbitMatrix.rotate(orbitAngle,0,1,0);

        translateVector = (orbitMatrix*orbitVector) + position;

        modelMatrix.translate(translateVector);

        rotation += rotationSpeed;
        modelMatrix.rotate(rotation,0,1,0);

        modelMatrix.scale(scale);
    }
};

#endif // SHAPE


#ifndef SHAPE
#define SHAPE

#include <QOpenGLFunctions_3_3_Core>
#include <QMatrix4x4>
#include <QVector3D>
#include "vertex.h"

struct Shape {
    GLuint vbo,
           vao;

    QMatrix4x4 modelMatrix;

    QVector3D position;

    float rotation = 0;

    QVector<Vertex> vertices;

    int numVertices;

    void updateModelMatrix(){
        modelMatrix.setToIdentity();
        modelMatrix.translate(position);
    }
};

#endif // SHAPE


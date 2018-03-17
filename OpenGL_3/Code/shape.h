#ifndef SHAPE
#define SHAPE

#include <QOpenGLFunctions_3_3_Core>
#include <QMatrix4x4>
#include <QVector3D>
#include "vertex.h"

struct Shape {
    GLuint vbo,
           vao,
           texturePointer;

    QMatrix4x4 modelMatrix,
               orbitMatrix;

    QVector3D oldPosition,
              newPosition,
              parent;

    QVector<quint8> textureImage;

    float rotation = 0,
          orbitAngle = 0,
          orbitRadius,
          rotationSpeed,
          orbitSpeed;

    QVector<Vertex> vertices;

    int numVertices,
        child;

    bool hasChild = false;

    void updateModelMatrix(){
        modelMatrix.setToIdentity();

        orbitMatrix.rotate(orbitSpeed,0,1,0);
        newPosition = oldPosition + (orbitMatrix*QVector3D(0,0,orbitRadius));
        rotation   += rotationSpeed;

        modelMatrix.translate(newPosition);
        modelMatrix.rotate(rotation,0,1,0);
    }

    void setPosition(QVector3D new_pos){
        oldPosition = new_pos;
    }

    void setChild(int childIdx){
        hasChild = true;
        child = childIdx;
    }
};

#endif // SHAPE


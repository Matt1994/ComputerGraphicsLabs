#ifndef VERTEX
#define VERTEX

#include <QVector3D>
#include <QVector2D>

struct Vertex {
    float x;
    float y;
    float z;
    float nx;
    float ny;
    float nz;
    float tx;
    float ty;

    void setCoords(QVector3D coords){
        x = coords.x();
        y = coords.y();
        z = coords.z();
    }

    void setNormalCoords(QVector3D coords){
        nx = coords.x();
        ny = coords.y();
        nz = coords.z();
    }

    void setTextureCoords(QVector2D coords){
        tx = coords.x();
        ty = coords.y();
    }
};

#endif // VERTEX


#ifndef QUAD_H_
#define QUAD_H_

#include "../object.h"

class Quad: public Object
{
    public:
        Quad(Point const &p1, Point const &p2, Point const &p3, Point const &p4);

        virtual Hit intersect(Ray const &ray);
        
        virtual Point getTexCoords(float x, float y, float z);

        Point const point1;
        Point const point2;
        Point const point3;
        Point const point4;
};

#endif

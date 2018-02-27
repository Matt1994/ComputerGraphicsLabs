#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "../object.h"

class Triangle: public Object
{
    public:
        Triangle(Point const &p1, Point const &p2, Point const &p3);

        virtual Hit intersect(Ray const &ray);

        Point const point1;
        Point const point2;
        Point const point3;
};

#endif

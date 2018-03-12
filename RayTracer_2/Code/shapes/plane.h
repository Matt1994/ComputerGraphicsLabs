#ifndef PLANE_H_
#define PLANE_H_

#include "../object.h"

class Plane: public Object
{
    public:
        Plane(Point const &point, Vector const &d1, Vector const &d2);

        virtual Hit intersect(Ray const &ray);
        
        virtual Point getTexCoords(float x, float y, float z);

		Point  const point;
        Vector const direction1;
        Vector const direction2;
};

#endif

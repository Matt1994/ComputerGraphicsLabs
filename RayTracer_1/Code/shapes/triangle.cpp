#include "triangle.h"

#include <cmath>

Hit Triangle::intersect(Ray const &ray)
{
	/* Implementation of the Möller-Trumbore algorithm */
	
	float det, u, v, t;
	
	Vector p1p2 = point2 - point1;
	Vector p1p3 = point3 - point1;
	Vector pvec = ray.D.cross(p1p3);
	Vector tvec = ray.O - point1;
	Vector qvec = tvec.cross(p1p2);
	
	Vector N = (p1p3).cross(p1p2).normalized();
	
	det = p1p2.dot(pvec);
	
	if(det == 0){
		return Hit::NO_HIT();
	}
	
	u = tvec.dot(pvec)/det;
	v = ray.D.dot(qvec)/det;
	t = p1p3.dot(qvec)/det;
	
	if( u < 0 || 
		u > 1 || 
		v < 0 || 
		u + v > 1 ||
		N.dot(ray.D) == 0
	){
		return Hit::NO_HIT();
	}
    
    return Hit(t,N);
}

Triangle::Triangle(Point const &p1, Point const &p2, Point const &p3)
:
	point1(p1),
	point2(p2),
	point3(p3)
{}

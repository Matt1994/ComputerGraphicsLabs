#include "plane.h"

#include <iostream>
#include <cmath>

using namespace std;

Hit Plane::intersect(Ray const &ray)
{
	/* Calculate normal to the plane */
	Vector N = direction1.cross(direction2).normalized();
	
	/* Calculate intersection point */
	float D = N.dot(point);
	
	if(N.dot(ray.D) == 0){
		return Hit::NO_HIT();
	}
	
	double t = -(N.dot(ray.O) + D)/N.dot(ray.D);
	
	/* If ray is parallel to the plane, there is no intersection */
	if(N.dot(ray.D) == 0){
		return Hit::NO_HIT();
	}
	
	return Hit(t,N);
}

Plane::Plane(Point const &point, Vector const &d1, Vector const &d2)
:
	point(point),
	direction1(d1),
	direction2(d2)
{}

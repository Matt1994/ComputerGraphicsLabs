#include "sphere.h"

#include <cmath>
#include <iostream>

using namespace std;

Hit Sphere::intersect(Ray const &ray)
{
    /****************************************************
    * RT1.1: INTERSECTION CALCULATION
    *
    * Given: ray, position, r
    * Sought: intersects? if true: *t
    *
    * Insert calculation of ray/sphere intersection here.
    *
    * You have the sphere's center (C) and radius (r) as well as
    * the ray's origin (ray.O) and direction (ray.D).
    *
    * If the ray does not intersect the sphere, return false.
    * Otherwise, return true and place the distance of the
    * intersection point from the ray origin in *t (see example).
    ****************************************************/

    // place holder for actual intersection calculation

    /*Vector OC = (position - ray.O).normalized();
    if (OC.dot(ray.D) < 0.999) {
        return Hit::NO_HIT();
    }*/
    double t;
    
    float a = 1;
    float b = (2*(ray.O - position)).dot(ray.D);
    float c = ((ray.O - position).dot(ray.O - position)) - (r*r);
    
    float disc = (b*b) - (4*a*c);
    
    if(disc < 0){
		return Hit::NO_HIT();
	} else {
		t = (-b - sqrt(disc))/(2*a);
		if(t < 0){
			t = (-b + sqrt(disc))/(2*a);
		}
	}

    /****************************************************
    * RT1.2: NORMAL CALCULATION
    *
    * Given: t, C, r
    * Sought: N
    *
    * Insert calculation of the sphere's normal at the intersection point.
    ****************************************************/

    Vector N  = ((ray.O + (t*ray.D)) - position).normalized();

    return Hit(t,N);
}

Sphere::Sphere(Point const &pos, double radius)
:
    position(pos),
    r(radius)
{}

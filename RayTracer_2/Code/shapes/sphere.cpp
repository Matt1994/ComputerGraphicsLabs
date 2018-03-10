#include "sphere.h"

#include <cmath>
#include <iostream>

using namespace std;

Hit Sphere::intersect(Ray const &ray)
{
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
			if(t < 0){
				return Hit::NO_HIT();
			}
		}
	}

    Vector N  = ((ray.O + (t*ray.D)) - position).normalized();

    return Hit(t,N);
}

Sphere::Sphere(Point const &pos, double radius)
:
    position(pos),
    r(radius)
{}

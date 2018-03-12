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

Point Sphere::getTexCoords(float x, float y, float z){
	Point point_on_sphere(x,y,z);
	Point rel = point_on_sphere - position;
	double phi = atan2(rel.y, rel.x);
	if (phi < 0) phi += 2*M_PI;
	
	float u = phi / (2*M_PI);
	float v = (M_PI - (acos(-rel.z / r))) / M_PI;

	return Point(u,v,0);
}

Sphere::Sphere(Point const &pos, double radius)
:
    position(pos),
    r(radius)
{}

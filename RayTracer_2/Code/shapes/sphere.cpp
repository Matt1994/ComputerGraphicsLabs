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
	Point p(x,y,z);
	Vector i = (p - position).normalized();
	float u = acos(i.z/sqrt((i.x*i.x)+(i.y*i.y)+(i.z*i.z)))/(2*M_PI);
	float v = (atan2(i.y,i.z)+M_PI)/(2*M_PI);
	cout << u << " " << v << endl;
	return Point(u,v,0);
}

Sphere::Sphere(Point const &pos, double radius)
:
    position(pos),
    r(radius)
{}

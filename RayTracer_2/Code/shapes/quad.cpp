#include "triangle.h"
#include "quad.h"

#include <cmath>
#include <iostream>

using namespace std;

Hit Quad::intersect(Ray const &ray)
{
	/* Create two triangles from the quad, and calculate the intersect from those */
		
	Triangle t1(point1,point2,point3);
	Triangle t2(point1,point3,point4);
	
	float t = nanf("");
	
	Vector N = (point4 - point1).cross(point2 - point1).normalized();
	
	Hit hit = t1.intersect(ray);
	
	if(hit.t > 0){
		t = hit.t;
	} else {
		hit = t2.intersect(ray);
		if(hit.t > 0){
			t = hit.t;
		}
	}
	
	return Hit(t,N);
	
}

Point Quad::getTexCoords(float x, float y, float z){
	return Point(x,y,0);
}

Quad::Quad(Point const &p1, Point const &p2, Point const &p3, Point const &p4)
:
	point1(p1),
	point2(p2),
	point3(p3),
	point4(p4)
{}

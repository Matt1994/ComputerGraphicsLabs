#include "scene.h"

#include "hit.h"
#include "image.h"
#include "material.h"
#include "ray.h"

#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

Color Scene::trace(Ray const &ray)
{
    // Find hit object and distance
    Hit min_hit(numeric_limits<double>::infinity(), Vector());
    ObjectPtr obj = nullptr;
    for (unsigned idx = 0; idx != objects.size(); ++idx)
    {
        Hit hit(objects[idx]->intersect(ray));
        if (hit.t < min_hit.t)
        {
            min_hit = hit;
            obj = objects[idx];
        }
    }

    // No hit? Return background color.
    if (!obj) return Color(0.0, 0.0, 0.0);

    Material material = obj->material;          //the hit objects material
    Point hit = ray.at(min_hit.t);                 //the hit point
    Vector N = min_hit.N;                          //the normal at hit point
    Vector V = -ray.D;                             //the view vector

    /****************************************************
    * This is where you should insert the color
    * calculation (Phong model).
    *
    * Given: material, hit, N, V, lights[]
    * Sought: color
    *
    * Hints: (see triple.h)
    *        Triple.dot(Vector) dot product
    *        Vector + Vector    vector sum
    *        Vector - Vector    vector difference
    *        Point - Point      yields vector
    *        Vector.normalize() normalizes vector, returns length
    *        double * Color     scales each color component (r,g,b)
    *        Color * Color      dito
    *        pow(a,b)           a to the power of b
    ****************************************************/
    
    Color color, color_diffuse, color_ambient, color_spec;
    
    /* Set up ambient color */
    
    color_ambient = material.color * material.ka;
    
    /* Sum the total of the diffuse and and specular of all lights */
    
    Hit new_min_hit(numeric_limits<double>::infinity(), Vector());
    Point newOrigin = ray.at(min_hit.t);
    
	for(uint i = 0;i<lights.size();i++){
		if(shadows){
			Vector newDir = (lights[i]->position - newOrigin).normalized();
			Ray new_ray(newOrigin, newDir);
			ObjectPtr new_obj = nullptr;
		
			for (unsigned idx = 0; idx != objects.size(); ++idx){
				if(objects[idx] != obj){
					Hit new_hit(objects[idx]->intersect(new_ray));
					if(new_hit.t > 0)
					{
						new_obj = objects[idx];
					}
				}
			}
		
			if(!new_obj) {
				Vector L 		 = (lights[i]->position - hit).normalized();
				Vector R 		 = ((2*(N.dot(L))*N) - L).normalized();
				color_diffuse 	+= max(0.0,(L.dot(N))) * material.color * lights[i]->color * material.kd;
				color_spec		+= pow(max(0.0,R.dot(V)),material.n) * lights[i]->color * material.ks;
			}
		} else {
			Vector L 		 = (lights[i]->position - hit).normalized();
			Vector R 		 = ((2*(N.dot(L))*N) - L).normalized();
			color_diffuse 	+= max(0.0,(L.dot(N))) * material.color * lights[i]->color * material.kd;
			color_spec		+= pow(max(0.0,R.dot(V)),material.n) * lights[i]->color * material.ks;
		}
	}
	
	/* Combine the three into one single color */
	
	color = color_diffuse + color_ambient + color_spec;
	
    return color;
}

void Scene::render(Image &img)
{
    unsigned w = img.width();
    unsigned h = img.height();
    for (unsigned y = 0; y < h; ++y)
    {
        for (unsigned x = 0; x < w; ++x)
        {
            Point pixel(x + 0.5, h - 1 - y + 0.5, 0);
            Ray ray(eye, (pixel - eye).normalized());
            Color col = trace(ray);
            col.clamp();
            img(x, y) = col;
        }
    }
}

// --- Misc functions ----------------------------------------------------------

void Scene::addObject(ObjectPtr obj)
{
    objects.push_back(obj);
}

void Scene::addLight(Light const &light)
{
    lights.push_back(LightPtr(new Light(light)));
}

void Scene::setEye(Triple const &position)
{
    eye = position;
}

unsigned Scene::getNumObject()
{
    return objects.size();
}

unsigned Scene::getNumLights()
{
    return lights.size();
}

void Scene::setShadows(bool b){
	shadows = b;
}

bool Scene::getShadows(){
	return shadows;
}

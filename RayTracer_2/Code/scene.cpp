#include "scene.h"

#include "hit.h"
#include "image.h"
#include "material.h"
#include "ray.h"

#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

Color Scene::trace(Ray const &ray, int depth)
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
    Point hit = ray.at(min_hit.t);              //the hit point
    Vector N = min_hit.N;                       //the normal at hit point
    Vector V = -ray.D;                          //the view vector
    
    Color color;
    
    /* Set up ambient color */
    
    color = material.color * material.ka;
    
    /* Sum the total of the diffuse and and specular of all lights */
 
    Point newOrigin = ray.at(min_hit.t);
    
	for(uint i = 0;i<lights.size();i++){
		Vector L      = (lights[i]->position - hit).normalized();
        Vector R      = ((2*(N.dot(L))*N) - L).normalized();
        bool inshadow = false;
		
		if(shadows){
			Vector newDir = (lights[i]->position - newOrigin).normalized();
			Ray new_ray(newOrigin + (N*0.001), newDir);
			ObjectPtr new_obj = nullptr;
		
			for(unsigned idx = 0; idx != objects.size(); ++idx){
				Hit new_hit(objects[idx]->intersect(new_ray));
				if(new_hit.t > 0)
				{
					inshadow = true;
					break;
				}
			}
		}
		
		if(!inshadow){
			color += max(0.0,(L.dot(N))) * material.color * lights[i]->color * material.kd;
			color += pow(max(0.0,R.dot(V)),material.n) * lights[i]->color * material.ks;
		}
	}
	
	if(depth < getMaxDepth()){
		if (material.ks){
			Vector eyeReflect = ((2*(N.dot(V))*N) - V).normalized();
			Ray new_ray(hit + (N*0.01), eyeReflect);
			color += trace(new_ray, depth+1) * material.ks;
		}
	}

	/* Combine the three into one single color */
	
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
            Color col = trace(ray,0);
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

void Scene::setMaxDepth(int d) {
    maxdepth = d;
}

int Scene::getMaxDepth() {
    return maxdepth;
}

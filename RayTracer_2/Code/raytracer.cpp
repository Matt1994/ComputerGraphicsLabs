#include "raytracer.h"

#include "image.h"
#include "light.h"
#include "material.h"
#include "triple.h"

#include <string>

// =============================================================================
// -- Include all your shapes here ---------------------------------------------
// =============================================================================

#include "shapes/sphere.h"
#include "shapes/plane.h"
#include "shapes/triangle.h"
#include "shapes/quad.h"
#include "objloader.h"

// =============================================================================
// -- End of shape includes ----------------------------------------------------
// =============================================================================

#include "json/json.h"

#include <exception>
#include <fstream>
#include <iostream>

using namespace std;        // no std:: required
using json = nlohmann::json;

bool Raytracer::parseObjectNode(json const &node)
{
    ObjectPtr obj = nullptr;

// =============================================================================
// -- Determine type and parse object parametrers ------------------------------
// =============================================================================

    if (node["type"] == "sphere")
    {
        Point pos(node["position"]);
        double radius = node["radius"];
        obj = ObjectPtr(new Sphere(pos, radius));
    }
    else if (node["type"] == "plane")
    {
		Point   p(node["p"]);
        Vector d1(node["d1"]);
        Vector d2(node["d2"]);
        obj = ObjectPtr(new Plane(p,d1,d2));
    }
    else if (node["type"] == "triangle")
    {
		Point point1(node["point1"]);
		Point point2(node["point2"]);
		Point point3(node["point3"]);
        obj = ObjectPtr(new Triangle(point1,point2,point3));
    }
    else if (node["type"] == "quad")
    {
		Point point1(node["point1"]);
		Point point2(node["point2"]);
		Point point3(node["point3"]);
		Point point4(node["point4"]);
        obj = ObjectPtr(new Quad(point1,point2,point3,point4));
    }
    else if (node["type"] == "mesh")
    {
		string str = node["model"];
		Point pos(node["position"]);
		int scale = node["scale"];
		OBJLoader objloader(str);
		objloader.unitize();
		
		vector<Vertex> data = objloader.vertex_data();
		
        for(uint i = 0;i<objloader.numTriangles()*3;i+=3){
			Point p1((data.at(i).x * scale) + pos.x, (data.at(i).y * scale) + pos.y, (data.at(i).z * scale) + pos.z);
			Point p2((data.at(i+1).x * scale) + pos.x, (data.at(i+1).y * scale) + pos.y, (data.at(i+1).z * scale) + pos.z);
			Point p3((data.at(i+2).x * scale) + pos.x, (data.at(i+2).y * scale) + pos.y, (data.at(i+2).z * scale) + pos.z);
			obj = ObjectPtr(new Triangle(p1,p2,p3));
			if (!obj) return false;
			obj->material = parseMaterialNode(node["material"]);
			scene.addObject(obj);
		}
		return true;
    }
    else
    {
        cerr << "Unknown object type: " << node["type"] << ".\n";
    }

// =============================================================================
// -- End of object reading ----------------------------------------------------
// =============================================================================

    if (!obj)
        return false;

    // Parse material and add object to the scene
    obj->material = parseMaterialNode(node["material"]);
	
	// If object has a texture, load it, and indicate that this has been set
	if(node["material"].count("texture")){
		obj->texture = parseTexture(node["material"]);
		obj->hasTexture = true;
	} else {
		obj->hasTexture = false;
	}
	
    scene.addObject(obj);
    return true;
}

Image Raytracer::parseTexture(json const &node) const
{
	string s = node.at("texture");
	return Image("../Scenes/" + s);
}

Light Raytracer::parseLightNode(json const &node) const
{
    Point pos(node["position"]);
    Color col(node["color"]);
    return Light(pos, col);
}

Material Raytracer::parseMaterialNode(json const &node) const
{
	Color color;
	// Not all shapes will now have a color set. If none, then set it to white
    if(node.count("color")){
		color = Color(node["color"]);
	} else {
		color = Color(0.0,0.0,0.0);
	}
    double ka = node["ka"];
    double kd = node["kd"];
    double ks = node["ks"];
    double n  = node["n"];
    return Material(color, ka, kd, ks, n);
}

bool Raytracer::readScene(string const &ifname)
try
{
    // Read and parse input json file
    ifstream infile(ifname);
    if (!infile) throw runtime_error("Could not open input file for reading.");
    json jsonscene;
    infile >> jsonscene;

// =============================================================================
// -- Read your scene data in this section -------------------------------------
// =============================================================================

    Point eye(jsonscene["Eye"]);
    scene.setEye(eye);

	scene_width = 400;
	scene_height = 400;
	scene.setShadows(false);
    scene.setMaxDepth(0);
    scene.setSuperSampleLevel(1);

	if(jsonscene["ImageSize"] != nullptr){
		scene_width = jsonscene["ImageSize"][0];
		scene_height = jsonscene["ImageSize"][1];	
	}
	
	if(jsonscene["Shadows"] != nullptr){
		scene.setShadows(jsonscene["Shadows"]);
	}

    if(jsonscene["MaxRecursionDepth"] != nullptr) {
        scene.setMaxDepth(jsonscene["MaxRecursionDepth"]);
    }
    
    if(jsonscene["SuperSamplingFactor"] != nullptr) {
        scene.setSuperSampleLevel(jsonscene["SuperSamplingFactor"]);
    }

    for (auto const &lightNode : jsonscene["Lights"])
        scene.addLight(parseLightNode(lightNode));

    unsigned objCount = 0;
    for (auto const &objectNode : jsonscene["Objects"])
        if (parseObjectNode(objectNode))
            ++objCount;

    cout << "Parsed " << objCount << " objects.\n";

// =============================================================================
// -- End of scene data reading ------------------------------------------------
// =============================================================================

    return true;
}
catch (exception const &ex)
{
    cerr << ex.what() << '\n';
    return false;
}

void Raytracer::renderToFile(string const &ofname)
{
    Image img(scene_width, scene_height);
    cout << "Tracing...\n";
    scene.render(img);
    cout << "Writing image to " << ofname << "...\n";
    img.write_png(ofname);
    cout << "Done.\n";
}

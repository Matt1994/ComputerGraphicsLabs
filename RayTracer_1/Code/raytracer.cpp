#include "raytracer.h"

#include "image.h"
#include "light.h"
#include "material.h"
#include "triple.h"

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
		OBJLoader objloader(str);
		
        for(uint i = 0;i<objloader.numTriangles()*3;i+=3){
			vector<Vertex> data = objloader.vertex_data();
			Point p1(data.at(i).x,data.at(i).y,data.at(i).z);
			p1 *=3;
			Point p2(data.at(i+1).x,data.at(i+1).y,data.at(i+1).z);
			p2 *=3;
			Point p3(data.at(i+2).x,data.at(i+2).y,data.at(i+2).z);
			p3 *=3;
			obj = ObjectPtr(new Triangle(p1,p2,p3));
			cout << p1 << " " << p2 << " " << p3 << endl;
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
    scene.addObject(obj);
    return true;
}

Light Raytracer::parseLightNode(json const &node) const
{
    Point pos(node["position"]);
    Color col(node["color"]);
    return Light(pos, col);
}

Material Raytracer::parseMaterialNode(json const &node) const
{
    Color color(node["color"]);
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

    // TODO: add your other configuration settings here

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
    // TODO: the size may be a settings in your file
    Image img(400, 400);
    cout << "Tracing...\n";
    scene.render(img);
    cout << "Writing image to " << ofname << "...\n";
    img.write_png(ofname);
    cout << "Done.\n";
}

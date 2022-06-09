#ifndef SIMPLE_RAY_TRACER_OBJFILE_H
#define SIMPLE_RAY_TRACER_OBJFILE_H

#include <string>
#include <fstream>
#include "scene/Object.h"
#include "scene/Scene.h"
#include "surface/Triangle.h"

class OBJFile {

private:

    std::ifstream fin;

    std::vector<Vector3f> vs;

    std::vector<Vector3f> uvs;

    std::vector<Vector3f> ns;

    void locateObject(const std::string & objName);

    void loadVertexInfo();

    void loadTriangularFaces(Object * object, Material * material);

public:

    explicit OBJFile(const std::string & fileName);

    Object * loadObject(const std::string & objName, Material * material);

    ~OBJFile();

};

#endif //SIMPLE_RAY_TRACER_OBJFILE_H

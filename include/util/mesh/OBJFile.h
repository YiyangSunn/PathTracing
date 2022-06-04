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

    std::vector<Vector3d> vs;

    std::vector<Vector3d> uvs;

    std::vector<Vector3d> ns;

    void locateObject(const std::string & objName);

    void loadVertexInfo();

    void loadTriangularFaces(Object * object, Material * material);

public:

    explicit OBJFile(const std::string & fileName);

    Object * loadObject(const std::string & objName, Material * material);

    ~OBJFile();

};

#endif //SIMPLE_RAY_TRACER_OBJFILE_H

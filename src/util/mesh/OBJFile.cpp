#include "util/mesh/OBJFile.h"

OBJFile::OBJFile(const std::string & fileName) {
    fin.open(fileName, std::ios_base::in);
    if (!fin.is_open()) {
        throw std::runtime_error("could not open file");
    }
    loadVertexInfo();
}

Object * OBJFile::loadObject(const std::string & objName, Material * material) {
    Object * object = new Object();
    locateObject(objName);
    loadTriangularFaces(object, material);
    return object;
}

OBJFile::~OBJFile() {
    if (fin.is_open()) {
        fin.close();
    }
}

void OBJFile::locateObject(const std::string & objName) {
    // 从头开始找
    fin.clear();
    fin.seekg(0, std::ios_base::beg);
    std::string type;
    std::string name;
    while (fin >> type) {
        if (type == "o") {
            fin >> name;
            if (name == objName) {
                break;
            }
        } else {
            std::getline(fin, name);
        }
    }
}

void OBJFile::loadVertexInfo() {
    fin.clear();
    fin.seekg(0, std::ios_base::beg);
    std::string type;
    while (fin >> type) {
        if (type == "v") {
            // 顶点
            float x, y, z;
            fin >> x >> y >> z;
            vs.emplace_back(x, y, z);
        } else if (type == "vt") {
            // 贴图
            float u, v;
            fin >> u >> v;
            uvs.emplace_back(u, v, 0);
        } else if (type == "vn") {
            // 法线
            float x, y, z;
            fin >> x >> y >> z;
            ns.emplace_back(x, y, z);
        } else {
            // 忽略此行
            std::getline(fin, type);
        }
    }
}

void OBJFile::loadTriangularFaces(Object * object, Material * material) {
    std::string tag;
    while (fin >> tag && tag != "f");
    while (tag == "f") {
        char slash;
        int vi[3], vti[3], vni[3];
        for (int k = 0; k < 3; ++k) {
            fin >> vi[k] >> slash >> vti[k] >> slash >> vni[k];
        }
        object->addSurface(new Triangle(
                vs[vi[0] - 1], vs[vi[1] - 1], vs[vi[2] - 1],
                ns[vni[0] - 1], ns[vni[1] - 1], ns[vni[2] - 1],
                uvs[vti[0] - 1], uvs[vti[1] - 1], uvs[vti[2] - 1],
                object, material
        ));
        if (!(fin >> tag)) {
            break;
        }
    }
}

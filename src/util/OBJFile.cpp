#include "util/OBJFile.h"

OBJFile::OBJFile(const std::string & fileName) {
    fin.open(fileName, std::ios_base::in);
    if (!fin.is_open()) {
        throw std::runtime_error("could not open file");
    }
    loadVertexInfo();
}

Object * OBJFile::loadObject(const std::string & objName, Material * material) {
    auto * object = new Object();
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
            vts.emplace_back(u, v, 0);
        } else if (type == "vn") {
            // 法线
            float x, y, z;
            fin >> x >> y >> z;
            vns.emplace_back(x, y, z);
        } else {
            // 忽略此行
            std::getline(fin, type);
        }
    }
}

void OBJFile::loadTriangularFaces(Object * object, Material * material) {
    std::string tag;
    while (fin >> tag && tag != "f");
    while (tag != "o") {
        if (tag == "f") {
            char slash;
            Vector3f v[3], vn[3], vt[3];
            for (int k = 0; k < 3; ++k) {
                // 顶点坐标
                int idx = 0;
                fin >> idx >> slash;
                v[k] = vs[idx - 1];
                // UV 坐标
                idx = 0;
                fin >> idx;
                if (idx != 0) {
                    fin >> slash;
                    vt[k] = vts[idx - 1];
                } else {
                    fin.clear();
                    fin >> slash;
                }
                // 法线坐标
                fin >> idx;
                vn[k] = vns[idx - 1];
            }
            object->addSurface(new Triangle(
                    v[0], v[1], v[2],
                    vn[0], vn[1], vn[2],
                    vt[0], vt[1], vt[2],
                    object, material
            ));
        }
        if (!(fin >> tag)) {
            break;
        }
    }
}

#include <cfloat>
#include "object/native/TriangularPyramid.h"

TriangularPyramid::TriangularPyramid(const Vector3d & p1, const Vector3d & p2, const Vector3d & p3, const Vector3d & p4,
                                     Material * material) {
    // note the order of vertices should not be written carelessly
    // the normal direction of the triangle depends on vertex order
    // and we should always ensure the normal vector points to the
    // outside.
    sides[0] = new Triangle(p2, p1, p3, material);
    sides[1] = new Triangle(p1, p2, p4, material);
    sides[2] = new Triangle(p3, p1, p4, material);
    sides[3] = new Triangle(p2, p3, p4, material);
    p[0] = p1;
    p[1] = p2;
    p[2] = p3;
    p[3] = p4;
}

bool TriangularPyramid::hit(const Ray & rin, float tMin, float tMax, HitRecord * hitRec) {
    float t = FLT_MAX;
    HitRecord hrec;
    bool found = false;
    for (Triangle * triangle : sides) {
        if (triangle->hit(rin, tMin, tMax, &hrec)) {
            if (hrec.t < t) {
                t = hrec.t;
                *hitRec = hrec;
                found = true;
            }
        }
    }
    return found;
}

Box TriangularPyramid::getBoundingBox() {
    Vector3d bottomLeft(FLT_MAX, FLT_MAX, FLT_MAX);
    Vector3d topRight(FLT_MIN, FLT_MIN, FLT_MIN);
    for (auto & vertex : p) {
        for (int j = 0; j < 3; ++j) {
            bottomLeft[j] = std::min(bottomLeft[j], vertex[j]);
            topRight[j] = std::max(topRight[j], vertex[j]);
        }
    }
    return {bottomLeft, topRight};
}

const Triangle & TriangularPyramid::operator[](int index) const {
    return *sides[index];
}

Triangle & TriangularPyramid::operator[](int index) {
    return *sides[index];
}

TriangularPyramid & TriangularPyramid::operator=(const TriangularPyramid & tp) {
    if (this != &tp) {
        for (int i = 0; i < 4; ++i) {
            delete sides[i];
            sides[i] = new Triangle(*tp.sides[i]);
        }
    }
    return *this;
}

TriangularPyramid::~TriangularPyramid() {
    for (Triangle * side : sides) {
        delete side;
    }
}

std::ostream & operator<<(std::ostream & out, const TriangularPyramid & tp) {
    out << "TriangularPyramid{sides[0]=" << tp[0] << ",sides[1]=" << tp[1] << ",sides[2]=" << tp[2] << ",sides[3]=" << tp[3] << "}";
    return out;
}

#include <cfloat>
#include "object/native/Rectangle.h"

Rectangle::Rectangle(const Vector3d & c, const Vector3d & a, const Vector3d & b,
                     Material * material) {
    this->c = c;
    this->a = a;
    this->b = b;
    this->material = material;
}

bool Rectangle::hit(const Ray & rin, float tMin, float tMax, HitRecord * hitRec) {
    Vector3d o = rin.getOrigin();
    Vector3d d = rin.getDirection();
    // first hit with the plane
    Vector3d n = a.cross(b).normalize();
    float left = d.dot(n);
    float right = n.dot(c - o);
    if (left != 0) {
        float t = right / left;
        if (t > tMin && t < tMax) {
            // check p with the rectangle
            Vector3d p = o + t * d;
            Vector3d v = p - c;
            if (v[0] < std::min(std::min(a[0], b[0]), 0.f) - 1e-5 ||
                v[0] > std::max(std::max(a[0], b[0]), 0.f) + 1e-5) {
                return false;
            }
            if (v[1] < std::min(std::min(a[1], b[1]), 0.f) - 1e-5 ||
                v[1] > std::max(std::max(a[1], b[1]), 0.f) + 1e-5) {
                return false;
            }
            if (v[2] < std::min(std::min(a[2], b[2]), 0.f) - 1e-5 ||
                v[2] > std::max(std::max(a[2], b[2]), 0.f) + 1e-5) {
                return false;
            }
            // valid p
            hitRec->t = t;
            hitRec->p = p;
            hitRec->n = n;
            hitRec->material = material;
            return true;
        }
    }
    return false;
}

Box Rectangle::getBoundingBox() {
    Vector3d p1 = c + a;
    Vector3d p2 = c + b;
    float xMin = std::min(std::min(c[0], p1[0]), p2[0]);
    float yMin = std::min(std::min(c[1], p1[1]), p2[1]);
    float zMin = std::min(std::min(c[2], p1[2]), p2[2]);
    float xMax = std::max(std::max(c[0], p1[0]), p2[0]);
    float yMax = std::max(std::max(c[1], p1[1]), p2[1]);
    float zMax = std::max(std::max(c[2], p1[2]), p2[2]);
    return {xMin, yMin, zMin, xMax, yMax, zMax};
}

Vector3d Rectangle::getA() const {
    return a;
}

Vector3d Rectangle::getB() const {
    return b;
}

Vector3d Rectangle::getC() const {
    return c;
}

std::ostream & operator<<(std::ostream & out, const Rectangle & rect) {
    out << "Rectangle{c=" << rect.getC() << ",a=" << rect.getA() << ",b=" << rect.getB() << "}";
    return out;
}

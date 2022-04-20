#include <cfloat>
#include "object/native/Rectangle.h"

Rectangle::Rectangle(const Vector3d & c, const Vector3d & a, const Vector3d & b,
                     Material * material) : Hittable(material) {
    this->c = c;
    this->a = a;
    this->b = b;
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
            // check p within the rectangle
            Vector3d p = o + t * d;
            Vector3d v = p - c;
            float vda = v.dot(a);
            float vdb = v.dot(b);
            if (vda <= 0 || vdb <= 0) {
                return false;
            } else {
                float aLen = a.getLength();
                if (vda / aLen >= aLen) {
                    return false;
                } else {
                    float bLen = b.getLength();
                    if (vdb / bLen >= bLen) {
                        return false;
                    }
                }
            }
            // valid p
            hitRec->t = t;
            hitRec->p = p;
            hitRec->n = n;
            hitRec->obj = this;
            return true;
        }
    }
    return false;
}

Box Rectangle::getBoundingBox() {
    Vector3d p1 = c + a;
    Vector3d p2 = c + b;
    Vector3d p3 = p1 + b;
    float xMin = std::min(std::min(c[0], p1[0]), std::min(p2[0], p3[0]));
    float yMin = std::min(std::min(c[1], p1[1]), std::min(p2[1], p3[1]));
    float zMin = std::min(std::min(c[2], p1[2]), std::min(p2[2], p3[2]));
    float xMax = std::max(std::max(c[0], p1[0]), std::min(p2[0], p3[0]));
    float yMax = std::max(std::max(c[1], p1[1]), std::min(p2[1], p3[1]));
    float zMax = std::max(std::max(c[2], p1[2]), std::min(p2[2], p3[2]));
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

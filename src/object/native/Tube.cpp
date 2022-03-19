#include <cmath>
#include "object/native/Tube.h"

Tube::Tube(const Vector3d & center, const Vector3d & orientation, float radius, float height, Material * material) {
    c = center;
    o = orientation.getNormalized();
    r = radius;
    h = height;
    this->material = material;
}

Vector3d Tube::getCenter() const {
    return c;
}

Vector3d Tube::getOrientation() const {
    return o;
}

float Tube::getRadius() const {
    return r;
}

float Tube::getHeight() const {
    return h;
}

bool Tube::hit(const Ray & rin, float tMin, float tMax, HitRecord * hitRec) {
    Vector3d ro = rin.getOrigin();
    Vector3d rd = rin.getDirection();

    // intermediate results
    Vector3d roc = (ro - c);
    float o2 = o.dot(o);
    float rd2 = rd.dot(rd);
    float roc2 = roc.dot(roc);
    float rocRd = roc.dot(rd);

    // another group of intermediate results
    float roo = ro.dot(o);
    float rdo = rd.dot(o);
    float co = c.dot(o);
    float rooCo = roo - co;

    // solve the equation a * t^2 + b * t + c = 0
    float a = rd2 - rdo * rdo;
    float b = 2 * (rocRd - rdo * rooCo);
    float e = roc2 - rooCo * rooCo - r * r;
    float delta = b * b - 4 * a * e;
    if (delta <= 0) {
        return false;
    }

    // square root
    float root = sqrtf(delta);
    // half height
    float hh = h / 2;
    // whether find the solution
    bool found = false;
    // check the first solution
    float t = (-b - root) / (2 * a);
    // store for use
    float s = 0.f;
    // check t between tMin ~ tMax
    if (t > tMin && t < tMax) {
        // check p within the surface
        s = roo + t * rdo - co;
        if (s > -hh && s < hh) {
            found = true;
        }
    }

    if (!found) {
        // check the second solution
        t = (-b + root) / (2 * a);
        if (t > tMin && t < tMax) {
            s = roo + t * rdo - co;
            if (s > -hh && s < hh) {
                found = true;
            }
        }
    }

    if (found) {
        hitRec->t = t;
        hitRec->p = ro + t * rd;
        hitRec->n = (hitRec->p - (s * o + c)) / r;
        hitRec->material = material;
        return true;
    }

    return false;
}

// not a tight box
Box Tube::getBoundingBox() {
    float halfSize = sqrtf(h * h + r * r);
    return {c - halfSize * Vector3d(1, 1, 1), c + halfSize * Vector3d(1, 1, 1)};
}

std::ostream & operator<<(std::ostream & out, const Tube & tube) {
    out << "Tube{center=" << tube.getCenter() << ",orientation=" << tube.getOrientation() << ",radius=" << tube.getRadius() << ",height=" << tube.getHeight() << "}";
    return out;
}

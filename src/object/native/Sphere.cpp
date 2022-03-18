#include <cmath>

#include "object/native/Sphere.h"

Sphere::Sphere(float x, float y, float z, float r, Material * material) {
    c = {x, y, z};
    this->r = r;
    this->material = material;
}

Sphere::Sphere(const Vector3d & c, float r, Material * material) {
    this->c = c;
    this->r = r;
    this->material = material;
}

Vector3d Sphere::getCenter() const {
    return c;
}

float Sphere::getRadius() const {
    return r;
}

// we'll solve the equation (o + t * d - c) * (o + t * d - c) = r^2
bool Sphere::hit(const Ray & ray, float tMin, float tMax, HitRecord * hitRec) {
    Vector3d o = ray.getOrigin();
    Vector3d d = ray.getDirection();
    Vector3d v = o - c;
    // that is, a * t^2 + b * t + e = 0
    float a = d.dot(d);
    float b = 2 * d.dot(v);
    float e = v.dot(v) - r * r;
    float delta = b * b - 4 * a * e;
    // no hit
    if (delta <= 0) {
        return false;
    }

    // check the solutions
    float t = -1;
    float t1 = (-b - std::sqrt(delta)) / (2 * a);
    if (t1 > tMin && t1 < tMax) {
        t = t1;
    } else {
        float t2 = (-b + std::sqrt(delta)) / (2 * a);
        if (t2 > tMin && t2 < tMax) {
            t = t2;
        }
    }

    if (t > 0) {
        hitRec->t = t;
        hitRec->p = o + t * d;
        // note may be hit from the inside here
        hitRec->n = (hitRec->p - c).normalize();
        hitRec->material = material;
        return true;
    }

    return false;
}

Box Sphere::getBoundingBox() {
    return {c[0] - r, c[1] - r, c[2] - r, c[0] + r, c[1] + r, c[2] + r};
}

std::ostream & operator<<(std::ostream & out, const Sphere & s) {
    out << "Sphere{center=" << s.getCenter() << ",radius=" << s.getRadius() << "}";
    return out;
}

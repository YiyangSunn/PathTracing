#include "object/native/Disk.h"

Disk::Disk(const Vector3d & center, const Vector3d & orientation, float radius, Material * material) {
    c = center;
    o = orientation.getNormalized();
    r = radius;
    this->material = material;
}

// note center c is on the disk plane, and orientation o is perpendicular to
// that, so for arbitrary point p on the plane we have o.dot(p - c) = 0, wh-
// ich is equivalent to o.dot(p) = o.dot(c). note again that p is on the ray
// so we have p = rin.origin + t * rin.direction, where t is the parameter
bool Disk::hit(const Ray & rin, float tMin, float tMax, HitRecord * hitRec) {
    // first try intersecting with the plane
    Vector3d ro = rin.getOrigin();
    Vector3d rd = rin.getDirection();
    // write as a * t = b
    float a = o.dot(rd);
    float b = o.dot(c - ro);
    if (a != 0) {
        float t = b / a;
        // check t between tMin and tMax
        if (t > tMin && t < tMax) {
            Vector3d p = ro + t * rd;
            // check p within the disk
            Vector3d v = p - c;
            if (v.dot(v) < r * r) {
                hitRec->t = t;
                hitRec->p = p;
                hitRec->n = o;
                hitRec->material = material;
                return true;
            }
        }
    }
    return false;
}

// we do not need a tight box here, since it involves complicate computation
Box Disk::getBoundingBox() {
    return {c[0] - r, c[1] - r, c[2] - r, c[0] + r, c[1] + r, c[2] + r};
}

Vector3d Disk::getCenter() const {
    return c;
}

Vector3d Disk::getOrientation() const {
    return o;
}

float Disk::getRadius() const {
    return r;
}

std::ostream & operator<<(std::ostream & out, const Disk & disk) {
    out << "Disk{center=" << disk.getCenter() << ",orientation=" << disk.getOrientation() << ",radius=" << disk.getRadius() << "}";
    return out;
}

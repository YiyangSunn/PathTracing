#include <cmath>
#include "object/native/Disk.h"
#include "util/math/Random.h"

Disk::Disk(const Vector3d & center, const Vector3d & orientation, float radius, Material * material) : Hittable(material) {
    c = center;
    o = orientation.getNormalized();
    r = radius;
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
                hitRec->obj = this;
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

//Vector3d Disk::samplePointOnSurface() const {
//    // first sample a random direction on xy plane
//    Vector3d d = Random::randomInUnitDisk();
//    // then find the correct z value so that d.dot(o) = 0
//    if (o[2] == 0) {
//        // could be arbitrary value
//        d[2] = 1;
//    } else {
//        // make d on the disk plane
//        d[2] = (-d[0] * o[0] - d[1] * o[1]) / o[2];
//    }
//    // suppose that we'll sample point p, note that d now is on the plane,
//    // so we can set p - c = t * d, and use(p - c).dot(p - c) = r^2 we get
//    // t^2 * d.dot(d) = r ^ 2
//    float t = sqrtf(r * r / d.dot(d));
//    return t * d + c;
//}

std::ostream & operator<<(std::ostream & out, const Disk & disk) {
    out << "Disk{center=" << disk.getCenter() << ",orientation=" << disk.getOrientation() << ",radius=" << disk.getRadius() << "}";
    return out;
}

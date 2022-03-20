#include "object/native/Triangle.h"

Triangle::Triangle(const Vector3d & p1, const Vector3d & p2, const Vector3d & p3, Material * material) {
    p[0] = p1;
    p[1] = p2;
    p[2] = p3;
    this->material = material;
}

const Vector3d & Triangle::operator[](int index) const {
    return p[index];
}

Vector3d & Triangle::operator[](int index) {
    return p[index];
}

bool Triangle::hit(const Ray & rin, float tMin, float tMax, HitRecord * hitRec) {
    Vector3d o = rin.getOrigin();
    Vector3d d = rin.getDirection();
    Vector3d a = p[1] - p[0];
    Vector3d b = p[2] - p[0];
    Vector3d n = a.cross(b).normalize();
    float right = n.dot(p[0] - o);
    float left = n.dot(d);
    if (left != 0) {
        float t = right / left;
        if (t > tMin && t < tMax) {
            // check if v within the triangle
            Vector3d v = o + t * d;
            Vector3d c = v - p[0];
            // solve the equation c = xa + yb, which is
            // c[0] = xa[0] + yb[0]
            // c[1] = xa[1] + yb[1]
            // c[2] = xa[2] + yb[2]
            // note there is a redundant equation here. In fact, we'll refuse
            // the hit if the solution is unstable
            bool found = false;
            float det = a[0] * b[1] - a[1] * b[0];
            if (std::abs(det) > 3e-5) {
                float y = (c[1] * a[0] - c[0] * a[1]) / det;
                if (y <= 0 || y >= 1) {
                    return false;
                }
                float x = (c[0] * b[1] - c[1] * b[0]) / det;
                if (x <= 0 || x + y >= 1) {
                    return false;
                }
                found = true;
            }
            if (!found) {
                det = a[0] * b[2] - a[2] * b[0];
                if (std::abs(det) > 3e-5) {
                    float y = (c[2] * a[0] - c[0] * a[2]) / det;
                    if (y <= 0 || y >= 1) {
                        return false;
                    }
                    float x = (c[0] * b[2] - c[2] * b[0]) / det;
                    if (x <= 0 || x + y >= 1) {
                        return false;
                    }
                    found = true;
                }
            }
            if (!found) {
                det = a[1] * b[2] - a[2] * b[1];
                if (std::abs(det) > 3e-5) {
                    float y = (c[2] * a[1] - c[1] * a[2]) / det;
                    if (y <= 0 || y >= 1) {
                        return false;
                    }
                    float x = (c[1] * b[2] - c[2] * b[1]) / det;
                    if (x <= 0 || x + y >= 1) {
                        return false;
                    }
                    found = true;
                }
            }
            if (found) {
                hitRec->t = t;
                hitRec->p = v;
                hitRec->n = n;
                hitRec->material = material;
                return true;
            }
        }
    }
    return false;
}

Box Triangle::getBoundingBox() {
    float xMin = std::min(std::min(p[0][0], p[1][0]), p[2][0]);
    float yMin = std::min(std::min(p[0][1], p[1][1]), p[2][1]);
    float zMin = std::min(std::min(p[0][2], p[1][2]), p[2][2]);
    float xMax = std::max(std::max(p[0][0], p[1][0]), p[2][0]);
    float yMax = std::max(std::max(p[0][1], p[1][1]), p[2][1]);
    float zMax = std::max(std::max(p[0][2], p[1][2]), p[2][2]);
    return {xMin, yMin, zMin, xMax, yMax, zMax};
}

std::ostream & operator<<(std::ostream & out, const Triangle & t) {
    out << "Triangle{p1=" << t[0] << ",p2=" << t[1] << ",p3=" << t[2] << "}";
    return out;
}

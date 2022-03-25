#include "object/mesh/MeshTriangle.h"

MeshTriangle::MeshTriangle(const MeshPoint & mp1, const MeshPoint & mp2, const MeshPoint & mp3, Material * material) {
    v[0] = mp1;
    v[1] = mp2;
    v[2] = mp3;
    this->material = material;
}

bool MeshTriangle::hit(const Ray & rin, float tMin, float tMax, HitRecord * hitRec) {
    const Vector3d o = rin.getOrigin();
    const Vector3d d = rin.getDirection();
    Vector3d E1 = v[1].p - v[0].p;
    Vector3d E2 = v[2].p - v[0].p;
    Vector3d T = o - v[0].p;
    Vector3d P = d.cross(E2);
    Vector3d Q = T.cross(E1);
    float PE1 = P.dot(E1);
    if (std::abs(PE1) > 3e-5) {
        float t = Q.dot(E2) / PE1;
        if (t <= tMin || t >= tMax) {
            return false;
        }
        float x = P.dot(T) / PE1;
        if (x < 0 || x > 1) {
            return false;
        }
        float y = Q.dot(d) / PE1;
        if (y < 0 || x + y > 1) {
            return false;
        }
        hitRec->t = t;
        hitRec->p = o + t * d;
        hitRec->material = material;
        hitRec->n = (1 - x - y) * v[0].n + x * v[1].n + y * v[2].n;
        return true;
    }
    return false;
}

Box MeshTriangle::getBoundingBox() {
    float xMin = std::min(std::min(v[0].p[0], v[1].p[0]), v[2].p[0]);
    float yMin = std::min(std::min(v[0].p[1], v[1].p[1]), v[2].p[1]);
    float zMin = std::min(std::min(v[0].p[2], v[1].p[2]), v[2].p[2]);
    float xMax = std::max(std::max(v[0].p[0], v[1].p[0]), v[2].p[0]);
    float yMax = std::max(std::max(v[0].p[1], v[1].p[1]), v[2].p[1]);
    float zMax = std::max(std::max(v[0].p[2], v[1].p[2]), v[2].p[2]);
    return {xMin, yMin, zMin, xMax, yMax, zMax};
}

MeshPoint MeshTriangle::operator[](int index) const {
    return v[index];
}

MeshPoint & MeshTriangle::operator[](int index) {
    return v[index];
}

std::ostream & operator<<(std::ostream & out, const MeshPoint & mp) {
    out << "MeshPoint{p=" << mp.p << ",n=" << mp.n << "}";
    return out;
}

std::ostream & operator<<(std::ostream & out, const MeshTriangle & mt) {
    out << "MeshTriangle{v0=" << mt[0] << ",v1=" << mt[1] << ",v2=" << mt[2] << "}";
    return out;
}

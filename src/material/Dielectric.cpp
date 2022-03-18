#include <cmath>
#include "material/Dielectric.h"

Dielectric::Dielectric() {
    refIdxInside = 1.5f;
    refIdxOutSide = 1.f;
    albedo = {1.f, 1.f, 1.f};
}

Dielectric::Dielectric(float refIdxInside, float refIdxOutside) {
    this->refIdxInside = refIdxInside;
    this->refIdxOutSide = refIdxOutside;
    this->albedo = {1, 1, 1};
}

Dielectric::Dielectric(float refIdxInside, const Vector3d & albedo, float refIdxOutside) {
    this->refIdxInside = refIdxInside;
    this->albedo = albedo;
    this->refIdxOutSide = refIdxOutside;
}

float Dielectric::getRefIdxInside() const {
    return refIdxInside;
}

float Dielectric::getRefIdxOutside() const {
    return refIdxOutSide;
}

Vector3d Dielectric::getAlbedo() const {
    return albedo;
}

Vector3d Dielectric::getAttenuation() {
    return albedo;
}

// assume that light always enters medium 2 from medium 1, then
// rf1 is the refractive index of medium 1, rf2 is that of medium 2
// the normal vector n always points toward medium 1
bool Dielectric::scatter(const Vector3d & din, const Vector3d & pos, const Vector3d & noVec, Vector3d * dout) {
    bool inside = (noVec.dot(din) >= 0);
    Vector3d n = (inside ? -noVec : noVec);
    float rf1 = (inside ? refIdxInside : refIdxOutSide);
    float rf2 = (inside ? refIdxOutSide : refIdxInside);
    float rfRatio = rf1 / rf2;
    float cos1 = -(n.dot(din));
    float delta = 1 - rfRatio * rfRatio * (1 - cos1 * cos1);

    float reflectProb;
    // total internal reflection
    if (delta <= 0) {
        reflectProb = 1.001f;
    } else {
        float r0 = (rf1 - rf2) / (rf1 + rf2);
        r0 *= r0;
        // schlick formula
        reflectProb = r0 + (1 - r0) * powf(1 - cos1, 5);
    }

    if (drand48() <= reflectProb) {
        // choose to reflect
        *dout = din + 2 * cos1 * n;
    } else {
        // choose to refract
        float cos2 = sqrtf(delta);
        *dout = -n * cos2 + (rfRatio * (din + cos1 * n));
    }

    return true;
}

std::ostream & operator<<(std::ostream & out, const Dielectric & mat) {
    out << "Dielectric{refIdxInside=" << mat.getRefIdxInside() << ",refIdxOutside=" << mat.getRefIdxOutside() << ",albedo=" << mat.getAlbedo() << "}";
    return out;
}

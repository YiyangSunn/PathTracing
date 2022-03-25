#include "material/Lambertian.h"
#include "util/math/Random.h"

Lambertian::Lambertian(const Vector3d & albedo) {
    this->albedo = albedo;
}

Vector3d Lambertian::getAlbedo() const {
    return albedo;
}

void Lambertian::setAlbedo(const Vector3d & albedo) {
    this->albedo = albedo;
}

// reflect randomly to approximate diffuse
bool Lambertian::scatter(const Vector3d & din, const Vector3d & pos, const Vector3d & noVec, Vector3d * dout, Vector3d * attenuation) {
    Vector3d n = (noVec.dot(din) >= 0 ? -noVec : noVec);
    *dout = Random::randomInUnitSphere() + n;
    dout->normalize();
    *attenuation = albedo;
    return true;
}

// no emitting
Vector3d Lambertian::emit(float u, float v, const Vector3d & p) {
    return {0, 0, 0};
}

std::ostream & operator<<(std::ostream & out, const Lambertian & lambertian) {
    out << "Lambertian{albedo=" << lambertian.getAlbedo() << "}";
    return out;
}

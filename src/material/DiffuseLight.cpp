#include "material/DiffuseLight.h"

DiffuseLight::DiffuseLight(const Vector3d & albedo) {
    this->albedo = albedo;
}

Vector3d DiffuseLight::getAlbedo() const {
    return albedo;
}

bool DiffuseLight::scatter(const Vector3d & din, const Vector3d & pos, const Vector3d & noVec, Vector3d * dout,
                           Vector3d * attenuation) {
    return false;
}

Vector3d DiffuseLight::emit(float u, float v, const Vector3d & p) {
    return albedo;
}

std::ostream & operator<<(std::ostream & out, const DiffuseLight & light) {
    out << "DiffuseLight{albedo=" << light.getAlbedo() << "}";
    return out;
}

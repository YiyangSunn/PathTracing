#include "material/Metal.h"
#include "util/math/Random.h"

Metal::Metal() {
    fuzzy = 0;
    albedo = {0, 0, 0};
}

Metal::Metal(const Vector3d & albedo, float fuzzy) {
    this->albedo = albedo;
    this->fuzzy = fuzzy;
}

Vector3d Metal::getAlbedo() const {
    return albedo;
}

float Metal::getFuzzy() const {
    return fuzzy;
}

bool Metal::scatter(const Vector3d & din, const Vector3d & pos, const Vector3d & noVec, Vector3d * dout, Vector3d * attenuation) {
    Vector3d n = (noVec.dot(din) >= 0 ? -noVec : noVec);
    float h = -(n.dot(din));
    *dout = din + 2 * h * n;
    if (fuzzy > 1e-5) {
        *dout += h * 0.99f * fuzzy * Random::randomInUnitSphere();
        (*dout).normalize();
    }
    *attenuation = albedo;
    return true;
}

// no emitting
Vector3d Metal::emit(float u, float v, const Vector3d & p) {
    return {0, 0, 0};
}

std::ostream & operator<<(std::ostream & out, const Metal & metal) {
    out << "Metal{albedo=" << metal.getAlbedo() << ",fuzzy=" << metal.getFuzzy() << "}";
    return out;
}

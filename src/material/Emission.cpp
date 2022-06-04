#include "material/Emission.h"

Emission::Emission(Texture * texture): Material(texture) {

}

Vector3d Emission::getBRDF(const Vector3d & wi, const Vector3d & wo, const HitResult & hitResult) {
    throw std::logic_error("getBRDF should not be invoked on light");
}

Vector3d Emission::sampleBRDF(const Vector3d & wo, float * pdf, const HitResult & hitResult) {
    throw std::logic_error("sampleBRDF should not be invoked on light");
}

float Emission::getPdf(const Vector3d & wi, const Vector3d & wo, const HitResult & hitResult) {
    throw std::logic_error("getPdf should not be invoked on light");
}

bool Emission::isEmitting() {
    return true;
}

Vector3d Emission::getEmitting(const Vector3d & wi, const HitResult & hitResult) {
    return texture->getValue(hitResult.u, hitResult.v, hitResult.p);
}

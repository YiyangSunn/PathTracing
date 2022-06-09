#include <stdexcept>
#include "material/Emission.h"

Emission::Emission(Texture * texture): Material(texture) {

}

Vector3f Emission::getBRDF(const Vector3f & wi, const Vector3f & wo, const HitResult & hitResult) {
    throw std::logic_error("getBRDF should not be invoked on light");
}

Vector3f Emission::sampleBRDF(const Vector3f & wo, float * pdf, const HitResult & hitResult) {
    throw std::logic_error("sampleBRDF should not be invoked on light");
}

float Emission::getPdf(const Vector3f & wi, const Vector3f & wo, const HitResult & hitResult) {
    throw std::logic_error("getPdf should not be invoked on light");
}

bool Emission::isEmitting() {
    return true;
}

Vector3f Emission::getEmitting(const Vector3f & wi, const HitResult & hitResult) {
    return texture->getValue(hitResult.u, hitResult.v, hitResult.p);
}

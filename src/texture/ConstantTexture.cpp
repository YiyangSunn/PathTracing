#include "texture/ConstantTexture.h"

ConstantTexture::ConstantTexture(const Vector3f & albedo) {
    this->albedo = albedo;
}

Vector3f ConstantTexture::getValue(float u, float v, const Vector3f & p) {
    return albedo;
}

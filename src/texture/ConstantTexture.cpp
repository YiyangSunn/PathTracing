#include "texture/ConstantTexture.h"

ConstantTexture::ConstantTexture(const Vector3d & albedo) {
    this->albedo = albedo;
}

Vector3d ConstantTexture::getValue(float u, float v, const Vector3d & p) {
    return albedo;
}

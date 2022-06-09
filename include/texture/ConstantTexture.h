#ifndef SIMPLE_RAY_TRACER_CONSTANTTEXTURE_H
#define SIMPLE_RAY_TRACER_CONSTANTTEXTURE_H

#include "Texture.h"

class ConstantTexture: public Texture {

private:

    Vector3f albedo;

public:

    explicit ConstantTexture(const Vector3f & albedo);

    Vector3f getValue(float u, float v, const Vector3f & p) override;

    virtual ~ConstantTexture() = default;

};

#endif //SIMPLE_RAY_TRACER_CONSTANTTEXTURE_H

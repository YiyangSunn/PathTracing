#ifndef SIMPLE_RAY_TRACER_CONSTANTTEXTURE_H
#define SIMPLE_RAY_TRACER_CONSTANTTEXTURE_H

#include "Texture.h"

class ConstantTexture: public Texture {

private:

    Vector3d albedo;

public:

    explicit ConstantTexture(const Vector3d & albedo);

    Vector3d getValue(float u, float v, const Vector3d & p) override;

    virtual ~ConstantTexture() = default;

};

#endif //SIMPLE_RAY_TRACER_CONSTANTTEXTURE_H

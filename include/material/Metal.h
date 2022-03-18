#ifndef SIMPLE_RAY_TRACER_METAL_H
#define SIMPLE_RAY_TRACER_METAL_H

#include "Material.h"

class Metal: public Material {

private:

    // parameter that adjusts the fuzziness of the metal surface
    // should between 0 ~ 1
    float fuzzy;

    Vector3d albedo;

public:

    Metal();

    explicit Metal(const Vector3d & albedo, float fuzzy = 0);

    bool scatter(const Vector3d & din, const Vector3d & pos, const Vector3d & noVec, Vector3d * dout) override;

    Vector3d getAlbedo() const;

    float getFuzzy() const;

    Vector3d getAttenuation() override;

    ~Metal() override = default;

};

std::ostream & operator<<(std::ostream & out, const Metal & metal);

#endif //SIMPLE_RAY_TRACER_METAL_H

#ifndef SIMPLE_RAY_TRACER_SPHERE_H
#define SIMPLE_RAY_TRACER_SPHERE_H

#include "object/Hittable.h"

class Sphere: public Hittable {

private:

    // center of the sphere
    Vector3d c;

    // radius of the sphere
    float r;

    // material of the sphere
    Material * material;

public:

    Sphere(const Vector3d & c, float r, Material * material);

    Sphere(float x, float y, float z, float r, Material * material);

    Vector3d getCenter() const;

    float getRadius() const;

    bool hit(const Ray & ray, float tMin, float tMax, HitRecord * hitRec) override;

    Box getBoundingBox() override;

    ~Sphere() override = default;

};

std::ostream & operator<<(std::ostream & out, const Sphere & s);

#endif //SIMPLE_RAY_TRACER_SPHERE_H

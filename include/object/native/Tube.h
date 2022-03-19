#ifndef SIMPLE_RAY_TRACER_TUBE_H
#define SIMPLE_RAY_TRACER_TUBE_H

#include "object/Hittable.h"

// cylindrical surface
class Tube: public Hittable {

private:

    // center of the tube
    Vector3d c;

    // orientation of the tube
    Vector3d o;

    // radius of the tube
    float r;

    // height of the tube
    float h;

    // material of the tube
    Material * material;

public:

    Tube(const Vector3d & center, const Vector3d & orientation, float radius, float height, Material * material);

    Vector3d getCenter() const;

    Vector3d getOrientation() const;

    float getRadius() const;

    float getHeight() const;

    bool hit(const Ray & rin, float tMin, float tMax, HitRecord * hitRec) override;

    Box getBoundingBox() override;

    ~Tube() override = default;

};

std::ostream & operator<<(std::ostream & out, const Tube & tube);

#endif //SIMPLE_RAY_TRACER_TUBE_H

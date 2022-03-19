#ifndef SIMPLE_RAY_TRACER_CYLINDER_H
#define SIMPLE_RAY_TRACER_CYLINDER_H

#include "Tube.h"
#include "Disk.h"

// modeled as a tube with two disks
class Cylinder: public Hittable {

private:

    // a tube
    Tube * tube;

    // two disks
    Disk * disks[2]{};

public:

    Cylinder(const Vector3d & center, const Vector3d & orientation, float radius, float height, Material * material);

    Vector3d getCenter() const;

    Vector3d getOrientation() const;

    float getRadius() const;

    float getHeight() const;

    bool hit(const Ray & rin, float tMin, float tMax, HitRecord * hitRec) override;

    Box getBoundingBox() override;

    ~Cylinder() override;

};

std::ostream & operator<<(std::ostream & out, const Cylinder & cylinder);

#endif //SIMPLE_RAY_TRACER_CYLINDER_H

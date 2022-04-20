#ifndef SIMPLE_RAY_TRACER_DISKLIGHTZ_H
#define SIMPLE_RAY_TRACER_DISKLIGHTZ_H

#include "Light.h"
#include "object/native/Disk.h"

class DiskLightZ: public Light {

protected:

    Disk * disk;

public:

    DiskLightZ(const Vector3d & center, float radius, Material * material);

    bool hit(const Ray & rin, float tMin, float tMax, HitRecord * hitRec) override;

    Box getBoundingBox() override;

    ~DiskLightZ() override;

};

#endif //SIMPLE_RAY_TRACER_DISKLIGHTZ_H

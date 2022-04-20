#ifndef SIMPLE_RAY_TRACER_UNIFORMDISKLIGHTZ_H
#define SIMPLE_RAY_TRACER_UNIFORMDISKLIGHTZ_H

#include "object/native/Disk.h"
#include "DiskLightZ.h"

class UniformDiskLightZ: public DiskLightZ {

public:

    UniformDiskLightZ(const Vector3d & center, float radius, Material * material);

    Vector3d getSample() override;

    float getPdf() override;

};

#endif //SIMPLE_RAY_TRACER_UNIFORMDISKLIGHTZ_H

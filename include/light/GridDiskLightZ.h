#ifndef SIMPLE_RAY_TRACER_GRIDDISKLIGHTZ_H
#define SIMPLE_RAY_TRACER_GRIDDISKLIGHTZ_H

#include <vector>
#include "object/native/Disk.h"
#include "DiskLightZ.h"

class GridDiskLightZ: public DiskLightZ {

private:

    float interval;

    std::vector<Vector3d> samples;

public:

    GridDiskLightZ(const Vector3d & center, float radius, Material * material, float interval);

    Vector3d getSample() override;

    float getPdf() override;

};

#endif //SIMPLE_RAY_TRACER_GRIDDISKLIGHTZ_H

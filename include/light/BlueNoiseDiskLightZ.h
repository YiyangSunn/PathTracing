#ifndef SIMPLE_RAY_TRACER_BLUENOISEDISKLIGHTZ_H
#define SIMPLE_RAY_TRACER_BLUENOISEDISKLIGHTZ_H

#include <vector>
#include "object/native/Disk.h"
#include "DiskLightZ.h"

class BlueNoiseDiskLightZ: public DiskLightZ {

private:

    std::vector<Vector3d> samples;

    void prepareSamples(const Vector3d & center, float radius, float minR);

public:

    BlueNoiseDiskLightZ(const Vector3d & center, float radius, Material * material, int count);

    Vector3d getSample() override;

    float getPdf() override;

};

#endif //SIMPLE_RAY_TRACER_BLUENOISEDISKLIGHTZ_H

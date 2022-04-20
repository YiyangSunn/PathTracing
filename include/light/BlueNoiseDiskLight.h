#ifndef SIMPLE_RAY_TRACER_BLUENOISEDISKLIGHT_H
#define SIMPLE_RAY_TRACER_BLUENOISEDISKLIGHT_H

#include "object/native/Disk.h"
#include "DiskLightZ.h"

class BlueNoiseDiskLight: public DiskLightZ {

public:

    BlueNoiseDiskLight(const Vector3d & center, float radius, Material * material);

    Vector3d getSample() override;

    float getPdf() override;

};

#endif //SIMPLE_RAY_TRACER_BLUENOISEDISKLIGHT_H

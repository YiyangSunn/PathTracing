#include "BlueNoiseDiskLight.h"

BlueNoiseDiskLight::BlueNoiseDiskLight(const Vector3d & center, float radius, Material * material)
    : DiskLightZ(center, radius, material) {

}

Vector3d BlueNoiseDiskLight::getSample() {
    return {};
}

float BlueNoiseDiskLight::getPdf() {
    float r = disk->getRadius();
    return 0.318309f / (r * r);
}

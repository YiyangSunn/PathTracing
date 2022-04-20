#include "light/UniformDiskLightZ.h"
#include "util/math/Random.h"

UniformDiskLightZ::UniformDiskLightZ(const Vector3d & center, float radius, Material * material)
    : DiskLightZ(center, radius, material) {

}

Vector3d UniformDiskLightZ::getSample() {
    float r = disk->getRadius();
    Vector3d c = disk->getCenter();
    return c + Random::randomInUnitDisk() * r;
}

float UniformDiskLightZ::getPdf() {
    float r = disk->getRadius();
    // 1 / (\pi * r^2)
    return 0.318309f / (r * r);
}

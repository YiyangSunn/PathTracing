#include "light/GridDiskLightZ.h"
#include <random>

GridDiskLightZ::GridDiskLightZ(const Vector3d & center, float radius, Material * material, float interval)
    : DiskLightZ(center, radius, material) {
    // 格点之间的间隔
    this->interval = interval;
    // 提前生成所有格点
    float x = -radius;
    while (x <= radius) {
        float y = -radius;
        while (y <= radius) {
            if (x * x + y * y <= radius * radius) {
                samples.push_back(Vector3d(x, y, 0) + center);
            }
            y += interval;
        }
        x += interval;
    }
}

Vector3d GridDiskLightZ::getSample() {
    int idx = (int) (drand48() * samples.size());
    return samples[idx];
}

float GridDiskLightZ::getPdf() {
    return 1;
}

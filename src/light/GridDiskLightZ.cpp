#include "light/GridDiskLightZ.h"
#include <random>

GridDiskLightZ::GridDiskLightZ(const Vector3d & center, float radius, Material * material, int count)
    : DiskLightZ(center, radius, material) {
    auto interval = (float) (3.0 / std::sqrt(count));
    // 输出采样点
    FILE * fp = fopen("grid_samples.txt", "w");
    fprintf(fp, "%f\n", 2 * radius);
    // 提前生成所有格点
    float x = -radius;
    while (x <= radius) {
        float y = -radius;
        while (y <= radius) {
            fprintf(fp, "%f %f\n", x + radius, y + radius);
            if (x * x + y * y <= radius * radius) {
                samples.push_back(Vector3d(x, y, 0) + center);
            }
            y += interval;
        }
        x += interval;
    }
    fclose(fp);
}

Vector3d GridDiskLightZ::getSample() {
    int idx = (int) (drand48() * (int) samples.size());
    return samples[idx];
}

float GridDiskLightZ::getPdf() {
    float r = disk->getRadius();
    return 0.318309f / (r * r);
}

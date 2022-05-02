#include "light/UniformDiskLightZ.h"
#include "util/math/Random.h"

UniformDiskLightZ::UniformDiskLightZ(const Vector3d & center, float radius, Material * material, int count)
    : DiskLightZ(center, radius, material) {
    // 把采样点输出到文件
    FILE * fp = fopen("uniform_samples.txt", "w");
    fprintf(fp, "%f\n", 2 * radius);
    while (count--) {
        Vector3d c = disk->getCenter();
        Vector3d p = Random::randomInUnitDisk() * radius;
        fprintf(fp, "%f %f\n", p[0] + radius, p[1] + radius);
        samples.push_back(c + p);
    }
    fclose(fp);
}

Vector3d UniformDiskLightZ::getSample() {
    int idx = (int) (drand48() * (int) samples.size());
    return samples[idx];
}

float UniformDiskLightZ::getPdf() {
    float r = disk->getRadius();
    return 0.318309f / (r * r); // 1 / (\pi * r^2)
}

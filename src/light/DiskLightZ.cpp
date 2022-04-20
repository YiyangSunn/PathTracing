#include "light/DiskLightZ.h"

DiskLightZ::DiskLightZ(const Vector3d & center, float radius, Material * material) : Light(material) {
    disk = new Disk(center, {0, 0, 1}, radius, material);
}

bool DiskLightZ::hit(const Ray & rin, float tMin, float tMax, HitRecord * hitRec) {
    bool isHit = disk->hit(rin, tMin, tMax, hitRec);
    if (isHit) {
        hitRec->obj = this;
    }
    return isHit;
}

Box DiskLightZ::getBoundingBox() {
    return disk->getBoundingBox();
}

DiskLightZ::~DiskLightZ() {
    delete disk;
}

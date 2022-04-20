#ifndef SIMPLE_RAY_TRACER_DISK_H
#define SIMPLE_RAY_TRACER_DISK_H

#include "object/Hittable.h"

class Disk: public Hittable {

private:

    // center of the disk
    Vector3d c;

    // orientation of the dist
    Vector3d o;

    // radius of the disk
    float r;

public:

    // orientation also used as the normal vector pointing from inside to outside
    Disk(const Vector3d & center, const Vector3d & orientation, float radius, Material * material);

    Vector3d getCenter() const;

    Vector3d getOrientation() const;

    float getRadius() const;

    bool hit(const Ray & rin, float tMin, float tMax, HitRecord * hitRec) override;

    Box getBoundingBox() override;

    ~Disk() override = default;

};

std::ostream & operator<<(std::ostream & out, const Disk & disk);

#endif //SIMPLE_RAY_TRACER_DISK_H

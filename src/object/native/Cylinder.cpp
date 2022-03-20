#include "object/native/Cylinder.h"

Cylinder::Cylinder(const Vector3d & center, const Vector3d & orientation, float radius, float height,
                   Material * material) {
    Vector3d o = orientation.getNormalized();
    float hh = height / 2;
    this->tube = new Tube(center, orientation, radius, height, material);
    this->disks[0] = new Disk(center + hh * o, o, radius, material);
    // note the direction of normal vector
    this->disks[1] = new Disk(center - hh * o, -o, radius, material);
}

Vector3d Cylinder::getCenter() const {
    return tube->getCenter();
}

Vector3d Cylinder::getOrientation() const {
    return tube->getOrientation();
}

float Cylinder::getRadius() const {
    return tube->getRadius();
}

float Cylinder::getHeight() const {
    return tube->getHeight();
}

bool Cylinder::hit(const Ray & rin, float tMin, float tMax, HitRecord * hitRec) {
    bool found = false;
    float t = tMax;
    HitRecord hrec;
    // check if hit the tube
    if (tube->hit(rin, tMin, tMax, &hrec)) {
        if (hrec.t < t) {
            t = hrec.t;
            *hitRec = hrec;
            found = true;
        }
    }
    // check if hit the disks
    for (Hittable * disk : disks) {
        if (disk->hit(rin, tMin, tMax, &hrec)) {
            if (hrec.t < t) {
                t = hrec.t;
                *hitRec = hrec;
                found = true;
            }
        }
    }
    return found;
}

Box Cylinder::getBoundingBox() {
    return tube->getBoundingBox();
}

Cylinder & Cylinder::operator=(const Cylinder & cylinder) {
    if (&cylinder != this) {
        delete tube;
        delete disks[0];
        delete disks[1];
        tube = new Tube(*cylinder.tube);
        disks[0] = new Disk(*cylinder.disks[0]);
        disks[1] = new Disk(*cylinder.disks[1]);
    }
    return *this;
}

Cylinder::~Cylinder() {
    delete tube;
    tube = nullptr;
    delete disks[0];
    disks[0] = nullptr;
    delete disks[1];
    disks[1] = nullptr;
}

std::ostream & operator<<(std::ostream & out, const Cylinder & cylinder) {
    out << "Cylinder{center=" << cylinder.getCenter() << ",orientation=" << cylinder.getOrientation() << ",radius=" << cylinder.getRadius() << ",height=" << cylinder.getHeight() << "}";
    return out;
}

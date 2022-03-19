#include "util/model/Ray.h"

Ray::Ray(const Vector3d & origin, const Vector3d & direction) {
    this->origin = origin;
    this->direction = direction.getNormalized();
}

Vector3d Ray::getOrigin() const {
    return origin;
}

Vector3d Ray::getDirection() const {
    return direction;
}

void Ray::setOrigin(const Vector3d & origin) {
    this->origin = origin;
}

void Ray::setDirection(const Vector3d & direction) {
    this->direction = direction;
}

std::ostream & operator<<(std::ostream & out, const Ray & r) {
    out << "Ray{origin=" << r.getOrigin() << ",direction=" << r.getDirection() << "}";
    return out;
}

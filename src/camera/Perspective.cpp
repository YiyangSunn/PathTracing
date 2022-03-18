#include "camera/Perspective.h"

Perspective::Perspective(const Vector3d & pos, const Vector3d & view, const Vector3d & up, float dist,
                         float width, float height) {
    e = pos;
    w = -view.getNormalized();
    u = up.cross(w).normalize();
    v = w.cross(u).normalize();
    d = dist;
    this->width = width;
    this->height = height;
}

Ray Perspective::getRay(float x, float y) {
    // note the direction should not have e involved
    Vector3d rd = - d * w + (x - 0.5f) * width * u + (y - 0.5f) * height * v;
    return {e, rd.normalize()};
}

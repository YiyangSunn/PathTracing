#include "camera/AbstractCamera.h"

AbstractCamera::AbstractCamera(const Vector3f & pos, const Vector3f & view, const Vector3f & up, float dist, float width,
                               float height) {
    e = pos;
    w = -view.normalized();
    u = up.cross(w).normalize();
    v = w.cross(u).normalize();
    d = dist;
    this->width = width;
    this->height = height;
}

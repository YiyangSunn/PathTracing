#include "camera/AbstractCamera.h"

AbstractCamera::AbstractCamera(const Vector3d & pos, const Vector3d & view, const Vector3d & up, float dist, float width,
                               float height) {
    e = pos;
    w = -view.getNormalized();
    u = up.cross(w).normalize();
    v = w.cross(u).normalize();
    d = dist;
    this->width = width;
    this->height = height;
}

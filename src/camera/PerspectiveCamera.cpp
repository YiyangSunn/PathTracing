#include "camera/PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(const Vector3f & pos, const Vector3f & tar, const Vector3f & up, float dist,
                                     float width, float height): AbstractCamera(pos, tar, up, dist, width, height) {

}

Ray PerspectiveCamera::getRay(float x, float y) {
    // note the direction should not have e involved
    Vector3f d = - dist * w + (x - 0.5f) * width * u + (y - 0.5f) * height * v;
    return {e, d.normalize()};
}

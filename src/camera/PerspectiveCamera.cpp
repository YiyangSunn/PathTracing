#include "camera/PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(const Vector3d & pos, const Vector3d & view, const Vector3d & up, float dist,
                                     float width, float height): AbstractCamera(pos, view, up, dist, width, height) {

}

Ray PerspectiveCamera::getRay(float x, float y) {
    // note the direction should not have e involved
    Vector3d rd = - d * w + (x - 0.5f) * width * u + (y - 0.5f) * height * v;
    return {e, rd};
}

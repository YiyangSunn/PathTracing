#include "camera/Perspective.h"
#include "test_helper.h"

int main() {
    Vector3d pos(1.1, 1.1, 1.1);
    Vector3d view(1, 0, 0);
    Vector3d up(0, 1, 0);
    float dist = 10;
    float width = 200;
    float height = 100;
    Camera * camera = new Perspective(pos, view, up, dist, width, height);
    Ray r = camera->getRay(0.5f, 0.5f);
    assert_vector3d_equal(r.getOrigin(), pos);
    assert_vector3d_equal(r.getDirection(), {1, 0, 0});
    r = camera->getRay(0.f, 0.f);
    assert_vector3d_equal(r.getDirection(), Vector3d(10, -50, -100).normalize());
    delete camera;
    return 0;
}

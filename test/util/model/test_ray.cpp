#include "util/model/Ray.h"
#include "test_helper.h"

int main() {
    Vector3d direction = Vector3d(2, 2, 2).normalize();
    Ray r({2, 2, 2}, direction);
    assert_vector3d_equal(r.getOrigin(), {2, 2, 2});
    assert_float_equal(r.getDirection().getLength(), 1.f);
    assert_vector3d_equal(r.getDirection().cross({-2, -2, -2}), {0, 0, 0});

    r.setOrigin({1.1, 1.1, 1.1});
    direction = Vector3d(-1, 3, -4).normalize();
    r.setDirection(direction);
    assert_vector3d_equal(r.getOrigin(), {1.1, 1.1, 1.1});
    assert_vector3d_equal(r.getDirection(), direction);
    return 0;
}

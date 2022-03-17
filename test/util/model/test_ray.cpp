#include "util/model/Ray.h"
#include "test_helper.h"

int main() {
    Ray r({2, 2, 2}, {-2, -2, -2});
    assert_vector3d_equal(r.getOrigin(), {2, 2, 2});
    assert_float_equal(r.getDirection().getLength(), 1.f);
    assert_vector3d_equal(r.getDirection().cross({-2, -2, -2}), {0, 0, 0});
    return 0;
}

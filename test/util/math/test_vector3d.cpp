#include "util/math/Vector3d.h"
#include "test_helper.h"

int main() {
    Vector3d a(1, 0, 0);
    assert_vector3d_equal(a, {1, 0, 0});
    assert_float_equal(a.getLength(), 1);
    a[1] = 2;
    assert_float_equal(a[0], 1);
    assert_float_equal(a[1], 2);
    assert_float_equal(a[2], 0);

    Vector3d b(3, 4, 5);
    Vector3d c = b.getNormalized();
    assert_float_equal(c.getLength(), 1);
    assert_vector3d_equal(b, {3, 4, 5});
    b.normalize();
    assert_float_equal(b.getLength(), 1);

    b = {2, 3, 4};
    c = {4, 5, 6};
    assert_vector3d_equal(b - c, {-2, -2, -2});
    assert_vector3d_equal(b + c, {6, 8, 10});
    assert_vector3d_equal(b * c, {8, 15, 24});
    assert_vector3d_equal(b / c, {0.5, 3.f / 5, 4.f / 6});
    assert_float_equal(b.dot(c), 8 + 15 + 24);
    assert_vector3d_equal(b.cross(c), {-2, 4, -2});
    assert_vector3d_equal(b * 2, {4, 6, 8});
    assert_vector3d_equal(c / 2, {2, 2.5f, 3});
    assert_vector3d_equal(b + 1, {3, 4, 5});
    assert_vector3d_equal(c - 1, {3, 4, 5});
    assert_vector3d_equal(b + c, c + b);
    assert_vector3d_equal(b + 2, 2 + b);
    assert_vector3d_equal(b * 2, 2 * b);
    assert_vector3d_equal(b * c, c * b);
    assert_vector3d_equal(b - c, -(c - b));
    assert_vector3d_equal(b, +b);

    return 0;
}

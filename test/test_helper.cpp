#include <cassert>

#include "test_helper.h"

#define abs std::abs

void assert_float_equal(float f1, float f2) {
    assert(abs(f1 - f2) < 1e-3);
}

void assert_vector3d_equal(const Vector3d & vec1, const Vector3d & vec2) {
    assert(abs(vec1[0] -vec2[0]) + abs(vec1[1] - vec2[1]) + abs(vec1[2] - vec2[2]) < 1e-3);
}

void assert_box_equal(const Box & b1, const Box & b2) {
    assert_vector3d_equal(b1.getBottomLeft(), b2.getBottomLeft());
    assert_vector3d_equal(b1.getTopRight(), b2.getTopRight());
}

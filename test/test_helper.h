#ifndef SIMPLE_RAY_TRACER_TEST_HELPER_H
#define SIMPLE_RAY_TRACER_TEST_HELPER_H

#include "util/math/Vector3d.h"
#include "util/model/Box.h"

void assert_float_equal(float f1, float f2);

void assert_vector3d_equal(const Vector3d & vec1, const Vector3d & vec2);

void assert_box_equal(const Box & b1, const Box & b2);

#endif //SIMPLE_RAY_TRACER_TEST_HELPER_H

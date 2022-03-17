#include <cassert>
#include <cfloat>
#include "util/model/Box.h"
#include "test_helper.h"
#include "util/math/Random.h"

int main() {
    Box b1(0, 0, 0, 2, 2, 2);
    assert_vector3d_equal(b1.getBottomLeft(), {0, 0, 0});
    assert_vector3d_equal(b1.getTopRight(), {2, 2, 2});
    assert_float_equal(b1.getXMin(), 0);
    assert_float_equal(b1.getYMin(), 0);
    assert_float_equal(b1.getZMin(), 0);
    assert_float_equal(b1.getXMax(), 2);
    assert_float_equal(b1.getYMax(), 2);
    assert_float_equal(b1.getZMax(), 2);

    b1 = Box({0, 0, 0}, {2, 2, 2});
    assert_vector3d_equal(b1.getBottomLeft(), {0, 0, 0});
    assert_vector3d_equal(b1.getTopRight(), {2, 2, 2});
    assert_float_equal(b1.getXMin(), 0);
    assert_float_equal(b1.getYMin(), 0);
    assert_float_equal(b1.getZMin(), 0);
    assert_float_equal(b1.getXMax(), 2);
    assert_float_equal(b1.getYMax(), 2);
    assert_float_equal(b1.getZMax(), 2);

    assert(b1.intersect({{1, 0, 1}, {0, 1, 0}}, 1e-3, FLT_MAX));
    assert(b1.intersect({{0, 0, 0}, {1, 1, 1}}, 1e-3, FLT_MAX));
    assert(b1.intersect({{4, 0, 0}, {1.5 - 4, 1.5, 1.5}}, 1e-3, FLT_MAX));
    assert(b1.intersect({{4, 0, 4}, {1.5 - 4, 1.5, 1.5 - 4}}, 1e-3, FLT_MAX));
    assert(b1.intersect({{0, 4, 2}, {1.5, 1.5 - 4, 1.5 - 2}}, 1e-3, FLT_MAX));
    assert(b1.intersect({{0, 0, -3}, {0.5, 0.5, 3.5}}, 1e-3, FLT_MAX));
    assert(b1.intersect({{4, 0, 0}, {-4, 0, 4}}, 1e-3, FLT_MAX));
    assert(b1.intersect({{0, 2, 0}, {2, 0, 2}}, 1e-3, FLT_MAX));
    assert(!b1.intersect({{3, 0, 0}, {0, 1, 0}}, 1e-3, FLT_MAX));
    assert(!b1.intersect({{-0.5, -0.5, -0.5}, {-1, -1, -1}}, 1e-3, FLT_MAX));
    assert(!b1.intersect({{4, 0, 0}, {0, 0, 4}}, 1e-3, FLT_MAX));
    assert(!b1.intersect({{0, 2, 0}, {2, 2, 2}}, 1e-3, FLT_MAX));
    assert(!b1.intersect({{0.5, 0.5, -0.5}, {0, 0, -1}}, 1e-3, FLT_MAX));

    for (int i = 0; i < 100; ++i) {
        float x = (float)drand48() * 100.f;
        float y = (float)drand48() * 100.f;
        float z = (float)drand48() * 100.f;
        float u = (float)drand48() * 1.9f;
        float v = (float)drand48() * 1.9f;
        float w = (float)drand48() * 1.9f;
        assert(b1.intersect({{x, y, z}, {u - x, v - y, w - z}}, 1e-3, FLT_MAX));
    }

    Vector3d center(1, 1, 1);
    float radius = 2.f;
    for (int i = 0; i < 100; ++i) {
        Vector3d v = Random::randomInUnitSphere().normalize();
        Vector3d o = center + v * radius;
        auto x = (float) drand48();
        auto y = (float) drand48();
        auto z = (0.f - v[0] * x - v[1] * y) / v[2];
        assert_float_equal(v.dot({x, y, z}), 0.f);
        assert_float_equal((o - center).getLength(), radius);
        assert(!b1.intersect({o, {x, y, z}}, 1e-3, FLT_MAX));
    }

    return 0;
}

#include <cfloat>
#include <cassert>
#include <iostream>
#include "object/HittableList.h"
#include "material/Lambertian.h"
#include "object/native/Sphere.h"
#include "material/Metal.h"
#include "object/native/Cylinder.h"
#include "material/Dielectric.h"
#include "object/native/TriangularPyramid.h"
#include "object/BVHTree.h"
#include "../test_helper.h"

Vector3d randomVector();

int main() {
    // put some random objects
    std::vector<Material *> mats;
    std::vector<Hittable *> objs;
    for (int i = 0; i < 30; ++i) {
        mats.push_back(new Lambertian({0.2, 0.2, 0.2}));
        objs.push_back(new Sphere(randomVector().normalize() * 8, 1, mats.back()));
        mats.push_back(new Metal({0.2, 0.2, 0.2}));
        objs.push_back(new Cylinder(randomVector().normalize() * 8, randomVector().normalize(), 1, 3.0, mats.back()));
        mats.push_back(new Dielectric(1.5));
        objs.push_back(new TriangularPyramid(randomVector().normalize() * 2, randomVector().normalize() * 2,
                                             randomVector().normalize() * 2, randomVector().normalize() * 2, mats.back()));
    }

    // create a HittableList for comparison
    HittableList list(objs);

    // create a BVHTree for testing
    BVHTree tree(&objs);

    // generate random rays
    for (int i = 0; i < 600; ++i) {
        Vector3d o = randomVector() * 3;
        Vector3d d = randomVector().normalize();
        Ray r(o, d);
        HitRecord h1, h2;
        bool hit1 = list.hit(r, 1e-3, FLT_MAX, &h1);
        assert(tree.getBoundingBox().contain(h1.p));
        bool hit2 = tree.hit(r, 1e-3, FLT_MAX, &h2);
        assert(!(hit1 ^ hit2));
        if (hit1) {
            assert_float_equal(h1.t, h2.t);
            assert_vector3d_equal(h1.p, h2.p);
            assert_vector3d_equal(h1.n, h2.n);
            assert(h1.material == h2.material);
        }
    }

    // free memory
    for (Material * m: mats) {
        delete m;
    }
    for (Hittable * h: objs) {
        delete h;
    }
    mats.clear();
    objs.clear();

    return 0;
}

Vector3d randomVector() {
    return {(float) (2.f * drand48() - 1.f), (float) (2.f * drand48() - 1.f), (float) (2.f * drand48() - 1.f)};
}

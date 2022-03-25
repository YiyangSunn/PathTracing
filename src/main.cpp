#include <iostream>
#include <vector>
#include <cmath>
#include "material/Material.h"
#include "object/Hittable.h"
#include "material/Lambertian.h"
#include "object/native/Disk.h"
#include "render/RayTracer.h"
#include "camera/Perspective.h"
#include "object/HittableList.h"
#include "util/image/ImageUtil.h"
#include "material/Dielectric.h"
#include "object/native/Tube.h"
#include "object/native/Cylinder.h"
#include "object/native/Triangle.h"
#include "object/native/TriangularPyramid.h"
#include "object/native/Rectangle.h"
#include "object/native/Sphere.h"
#include "material/Metal.h"
#include "material/DiffuseLight.h"
#include "object/mesh/MeshUtil.h"
#include "object/BVHTree.h"

Hittable * random_sphere(const Vector3d & center, float radius, Material * material);

Hittable * random_cylinder(const Vector3d & center, float radius, float height, Material * material, bool horizontal = false);

Hittable * random_triangular_pyramid(const Vector3d & center, Material * material);

Material * random_lambertian();

Material * random_metal();

Material * random_dielectric();

Material * random_diffuse_light();

int main() {
    std::vector<Material *> mats;
    std::vector<Hittable *> objs;
//
    mats.push_back(new Lambertian({0.5, 0.5, 0.5}));
//    mats.push_back(new Dielectric(1.5));
    Vector3d c(-1000, 0, 1000);
    Vector3d a(2000, 0, 0);
    Vector3d b(0, 0, -2000);
    objs.push_back(new Rectangle(c, a, b, mats.back()));
//
//    mats.push_back(new Lambertian({0.2, 0.5, 0.4}));
//    Vector3d center(0, 0.4, 0);
//    objs.push_back(random_sphere(center, 0.4f, mats.back()));
//
//    mats.push_back(random_diffuse_light());
//    Vector3d disk_position(0, 1, 0);
//    objs.push_back(new Disk(disk_position, {0, -1, 0}, 0.4, mats.back()));

    mats.push_back(new Dielectric(1.5));
    if (!MeshUtil::loadPureModelFromObj("../resource/decanter_with_wine.obj", &objs, mats.back())) {
        std::cout << "fail to load .obj file\n" << std::flush;
    }
    std::cout << objs.size() << " objects in total\n" << std::flush;

    Vector3d target(0, 18, 0);
    Vector3d position(0, 30, 50);
    Renderer * renderer = new RayTracer(50, 200, 5);
    Camera * camera = new Perspective(position, target - position, {0, 1, 0}, 8, 10, 5);
    Hittable * scene = new BVHTree(&objs);
    auto * im = new ImageBuffer(400, 200);

    renderer->render(camera, scene, im);
    ImageUtil::gammaCorrection(im, 2);
    ImageUtil::writePPM6(*im, "img0.ppm");

    delete im;
    delete scene;
    delete camera;
    delete renderer;

    for (Material * mat: mats) {
        delete mat;
    }
    mats.clear();
    for (Hittable * obj: objs) {
        delete obj;
    }
    objs.clear();

    return 0;
}

Material * random_lambertian() {
    return new Lambertian({(float) drand48() * (float) drand48(), (float) drand48() * (float) drand48(),(float) drand48() * (float) drand48()});
}

Material * random_metal() {
    return new Metal({0.5f * (float) (1 + drand48()), 0.5f * (float) (1 + drand48()), 0.5f * (float) (1 + drand48())},0.5f * (float) drand48());
}

Material * random_dielectric() {
    return new Dielectric(1.4f + 0.3f * (float) drand48());
}

Material * random_diffuse_light() {
    return new DiffuseLight({4, 4, 4});
}

Hittable * random_sphere(const Vector3d & center, float radius, Material * material) {
    return new Sphere(center, radius, material);
}

Hittable * random_cylinder(const Vector3d & center, float radius, float height, Material * material, bool horizontal) {
    auto p = (float) drand48();
    if (p < 0.6 || horizontal) {
        // horizontal cylinder
        return new Cylinder(center, {0, 0, 1}, radius, height, material);
    }
    // vertical cylinder
    Vector3d c(center[0], height / 2, center[2]);
    return new Cylinder(c, {0, 1, 0}, radius, height, material);
}

Vector3d xzRotate120(const Vector3d & vec) {
    Vector3d v(vec);
    v[0] = -0.5f * vec[0] - 0.866025f * vec[2];
    v[2] = 0.866025f * vec[0] - 0.5f * vec[2];
    return v;
}

// generate regular tetrahedron
Hittable * random_triangular_pyramid(const Vector3d & center, Material * material) {
    float h = center[1] / 2;
    float r = sqrtf(2) * h;
    float x = (float) drand48() * (float) drand48() * 2 - 0.99f;
    float y = sqrtf(1 - x * x);
    Vector3d p1(center[0] + 2 * r * x, center[1], center[2] + 2 * r * y);
    Vector3d p2 = xzRotate120(p1 - center) + center;
    Vector3d p3 = xzRotate120(p2 - center) + center;
    p1[1] = p2[1] = p3[1] = 0;
    Vector3d p4(center[0], 4 * h, center[2]);
    return new TriangularPyramid(p1, p2, p3, p4, material);
}

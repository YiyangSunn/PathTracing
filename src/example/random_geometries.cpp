#include <cmath>
#include <iostream>
#include <getopt.h>
#include "render/Renderer.h"
#include "render/RayTracer.h"
#include "object/HittableList.h"
#include "camera/Perspective.h"
#include "util/image/ImageUtil.h"
#include "object/native/Sphere.h"
#include "material/Lambertian.h"
#include "material/Metal.h"
#include "material/Dielectric.h"
#include "camera/DefocusBlur.h"
#include "object/native/Rectangle.h"
#include "object/native/Cylinder.h"
#include "object/native/TriangularPyramid.h"
#include "object/BVHTree.h"

Hittable * random_sphere(const Vector3d & center, float radius, Material * material);

Hittable * random_cylinder(const Vector3d & center, float radius, float height, Material * material, bool horizontal = false);

Hittable * random_triangular_pyramid(const Vector3d & center, Material * material);

Material * random_lambertian();

Material * random_metal();

Material * random_dielectric();

bool conllide(const std::vector<Box> & boxes, const Box & box);

// render an image with lots of random spheres
int main(int argc, char * argv[]) {
    // default parameters
    int width = 300;
    int height = 200;
    int threadCount = 5;
    int samplePerPixel = 30;
    int maxDepth = 50;
    std::string outputFile = "img.ppm";

    // get input args
    const char * opts = ":w:h:s:t:d:o:";
    int c = 0;
    while ((c = getopt(argc, argv, opts)) != EOF) {
        switch (c) {
            case 'w':
                width = std::stoi(optarg);
                break;
            case 'h':
                height = std::stoi(optarg);
                break;
            case 's':
                samplePerPixel = std::stoi(optarg);
                break;
            case 't':
                threadCount = std::stoi(optarg);
                break;
            case 'd':
                maxDepth = std::stoi(optarg);
                break;
            case 'o':
                outputFile = optarg;
                break;
            default:
                break;
        }
    }

    std::cout << "start generating scene..." << std::flush;

    std::vector<Material *> mats;
    std::vector<Hittable *> objs;
    std::vector<Box> boxes;

    // the bottom plane
    mats.push_back(new Lambertian({0.5, 0.5, 0.5}));
    Vector3d center(-500, 0, 500);
    Vector3d a(1000, 0, 0);
    Vector3d b(0, 0, -1000);
    objs.push_back(new Rectangle(center, a, b, mats.back()));

    // the big cylinder
    mats.push_back(new Lambertian({0.4, 0.2, 0.1}));
    objs.push_back(random_cylinder({-4, 1, 0}, 1.0, 3, mats.back(), true));
    boxes.push_back(objs.back()->getBoundingBox());
    // the big triangular pyramid
    mats.push_back(new Dielectric(1.5));
    objs.push_back(random_triangular_pyramid({0, 1, 0}, mats.back()));
    boxes.push_back(objs.back()->getBoundingBox());
    // the big sphere
    mats.push_back(new Metal({0.7, 0.6, 0.5}, 0));
    objs.push_back(random_sphere({4, 1, 0}, 1.0, mats.back()));
    boxes.push_back(objs.back()->getBoundingBox());

    for (int i = 0; i < 596; ++i) {
        bool ok = false;
        do {
            Vector3d center(13 * ((float) drand48() * 2 - 1.f), 0.2,(float) 13 * ((float) drand48() * 2 - 1.f));
            auto p = (float) drand48();
            if (p < 0.4) {
                // sphere
                p = (float) drand48();
                if (p < 0.7) {
                    mats.push_back(random_lambertian());
                } else if (p < 0.9) {
                    mats.push_back(random_metal());
                } else {
                    mats.push_back(random_dielectric());
                }
                objs.push_back(random_sphere(center, 0.2, mats.back()));
            } else if (p < 0.7) {
                // cylinder
                p = (float) drand48();
                if (p < 0.6) {
                    mats.push_back(random_lambertian());
                } else if (p < 0.80) {
                    mats.push_back(random_metal());
                } else {
                    mats.push_back(random_dielectric());
                }
                objs.push_back(random_cylinder(center, 0.2, 0.32, mats.back()));
            } else {
                // triangular pyramid
                p = (float) drand48();
                if (p < 0.6) {
                    mats.push_back(random_lambertian());
                } else if (p < 0.8) {
                    mats.push_back(random_metal());
                } else {
                    mats.push_back(random_dielectric());
                }
                objs.push_back(random_triangular_pyramid(center, mats.back()));
            }
            if (conllide(boxes, objs.back()->getBoundingBox())) {
                delete mats.back();
                delete objs.back();
                mats.pop_back();
                objs.pop_back();
            } else {
                boxes.push_back(objs.back()->getBoundingBox());
                ok = true;
            }
        } while (!ok);
    }

    std::cout << "ok\nstart rendering " << objs.size() << " objects..." << std::flush;

    Hittable * scene = new BVHTree(&objs);
//    Hittable * scene = new HittableList(objs);
//    Camera * camera = new DefocusBlur({13, 2.1, 3}, {-13, -2.1, -3}, {0, 1, 0}, 8, 5.7, 3.8, 0.1);
    Camera * camera = new Perspective({13, 2.1, 3}, {-13, -2.1, -3}, {0, 1, 0}, 8, 5.7, 3.8);
    Renderer * renderer = new RayTracer(maxDepth, samplePerPixel, threadCount);
    auto * im = new ImageBuffer(width, height);

    renderer->render(camera, scene, im);
    ImageUtil::gammaCorrection(im, 2);
    ImageUtil::writePPM(*im, outputFile, 6);

    std::cout << "ok" << std::endl << std::flush;

    delete im;
    delete renderer;
    delete camera;
    delete scene;

    for (Hittable * obj: objs) {
        delete obj;
    }
    objs.clear();
    for (Material * mat : mats) {
        delete mat;
    }
    mats.clear();

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

// use a naive and inexact implementation
bool conllide(const std::vector<Box> & boxes, const Box & box) {
    for (auto & b: boxes) {
        Vector3d p1 = b.getCenter();
        Vector3d p2 = box.getCenter();
        float d1 = (p1 - b.getBottomLeft()).getLength();
        float d2 = (p2 - box.getBottomLeft()).getLength();
        if (d1 + d2 >= (p1 - p2).getLength()) {
            return true;
        }
    }
    return false;
}

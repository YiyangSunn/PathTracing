#include <iostream>
#include <vector>
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

int main() {
    std::vector<Material *> mats;
    std::vector<Hittable *> objs;

    mats.push_back(new Lambertian({0.3, 0.2, 0.5}));
//    mats.push_back(new Dielectric(1.5));
    objs.push_back(new TriangularPyramid({1.5, -0.5, -1.5}, {-1.5, -0.5, -1.5}, {0, 2, -1.5}, {0, 0, 0.5}, mats.back()));

    Vector3d target(0, 0.1, -0.5);
    Vector3d position(0, 0.8, -3);
    Renderer * renderer = new RayTracer(10, 80, 2);
    Camera * camera = new Perspective(position, target - position, {0, 1, 0}, 1, 4, 2);
    Hittable * scene = new HittableList(objs);
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

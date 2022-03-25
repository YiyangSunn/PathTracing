#include <vector>
#include <iostream>
#include <getopt.h>
#include "material/Lambertian.h"
#include "object/mesh/MeshUtil.h"
#include "material/Dielectric.h"
#include "material/DiffuseLight.h"
#include "object/BVHTree.h"
#include "camera/Perspective.h"
#include "render/RayTracer.h"
#include "util/image/ImageUtil.h"
#include "material/Metal.h"

int main(int argc, char * argv[]) {
    // default parameters
    int width = 300;
    int height = 180;
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

    std::vector<Material *> mats;
    std::vector<Hittable *> objs;

    mats.push_back(new Lambertian({0.9, 0.9, 0.9}));
    if (!MeshUtil::loadPureModelFromObj("../resource/metal_and_glass/wall.obj", &objs, mats.back())) {
        std::cout << "fail to load .obj file." << std::flush;
    }

    mats.push_back(new Dielectric(1.5, {1, 0.843137, 0}, 1.5));
    if (!MeshUtil::loadPureModelFromObj("../resource/metal_and_glass/deco.obj", &objs, mats.back())) {
        std::cout << "fail to load .obj file." << std::flush;
    }

    mats.push_back(new Dielectric(1.5));
    if (!MeshUtil::loadPureModelFromObj("../resource/metal_and_glass/sphere.obj", &objs, mats.back())) {
        std::cout << "fail to load .obj file." << std::flush;
    }

    mats.push_back(new Dielectric(1.5));
    if (!MeshUtil::loadPureModelFromObj("../resource/metal_and_glass/cylinder.obj", &objs, mats.back())) {
        std::cout << "fail to load .obj file." << std::flush;
    }

    mats.push_back(new Dielectric(1.5, {0.019608, 0.803922, 0.980392}, 1.5));
    if (!MeshUtil::loadPureModelFromObj("../resource/metal_and_glass/whale.obj", &objs, mats.back())) {
        std::cout << "fail to load .obj file." << std::flush;
    }

    mats.push_back(new Dielectric(1.5, {0.898039, 0.070588, 0.988235}, 1));
    if (!MeshUtil::loadPureModelFromObj("../resource/metal_and_glass/cone.obj", &objs, mats.back())) {
        std::cout << "fail to load .obj file." << std::flush;
    }

    mats.push_back(new Metal({0.749020, 0.749020, 0.749020}, 0));
    if (!MeshUtil::loadPureModelFromObj("../resource/metal_and_glass/coin.obj", &objs, mats.back())) {
        std::cout << "fail to load .obj file." << std::flush;
    }

    // light
    mats.push_back(new DiffuseLight({3, 3, 3}));
    if (!MeshUtil::loadPureModelFromObj("../resource/metal_and_glass/light.obj", &objs, mats.back())) {
        std::cout << "fail to load .obj file." << std::flush;
    }

    Hittable * scene = new BVHTree(&objs);
    Vector3d cameraPosition(7.35889, 5, 6.92579);
    Vector3d cameraTarget(0, 0, 0);
    Camera * camera = new Perspective(cameraPosition, cameraTarget - cameraPosition, {0, 1, 0}, 7.1, 5, 3);
    Renderer * renderer = new RayTracer(maxDepth, samplePerPixel, threadCount);
    ImageBuffer * im = new ImageBuffer(width, height);

    renderer->render(camera, scene, im);

    ImageUtil::gammaCorrection(im, 2);
    ImageUtil::writePPM6(*im, outputFile);

    delete im;
    delete renderer;
    delete camera;
    delete scene;

    for (Hittable * h: objs) {
        delete h;
    }
    objs.clear();
    for (Material * m: mats) {
        delete m;
    }
    mats.clear();

    return 0;
}

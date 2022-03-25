#include <vector>
#include <iostream>
#include <getopt.h>

#include "material/Material.h"
#include "object/Hittable.h"
#include "object/mesh/MeshUtil.h"
#include "object/BVHTree.h"
#include "camera/Perspective.h"
#include "render/RayTracer.h"
#include "util/image/ImageUtil.h"
#include "material/Lambertian.h"
#include "object/native/Rectangle.h"
#include "material/DiffuseLight.h"
#include "object/native/Sphere.h"
#include "material/Dielectric.h"

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
                std::cout << optarg << std::endl;
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
    if (!MeshUtil::loadPureModelFromObj("../resource/bottle_on_table/wall.obj", &objs, mats.back())) {
        std::cout << "fail to load .obj file." << std::flush;
    }

    mats.push_back(new Lambertian({1.0, 0.90588, 0.72941}));
    if (!MeshUtil::loadPureModelFromObj("../resource/bottle_on_table/table.obj", &objs, mats.back())) {
        std::cout << "fail to load .obj file." << std::flush;
    }

    mats.push_back(new Dielectric(1.5));
    if (!MeshUtil::loadPureModelFromObj("../resource/bottle_on_table/bottle.obj", &objs, mats.back())) {
        std::cout << "fail to load .obj file." << std::flush;
    }

    // light
    mats.push_back(new DiffuseLight({4, 4, 4}));
    if (!MeshUtil::loadPureModelFromObj("../resource/bottle_on_table/light.obj", &objs, mats.back())) {
        std::cout << "fail to load .obj file." << std::flush;
    }

    Hittable * scene = new BVHTree(&objs);
    Vector3d cameraPosition(-11.13, 4.7, -3.7);
    Vector3d cameraTarget(-1.8, 1.2, 0);
    Camera * camera = new Perspective(cameraPosition, cameraTarget - cameraPosition, {0, 1, 0}, 6, 5, 3);
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

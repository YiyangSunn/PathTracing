#include <vector>
#include <getopt.h>
#include "material/Material.h"
#include "object/Hittable.h"
#include "material/Lambertian.h"
#include "object/native/Rectangle.h"
#include "material/DiffuseLight.h"
#include "object/native/Disk.h"
#include "object/BVHTree.h"
#include "camera/Camera.h"
#include "camera/Perspective.h"
#include "render/Renderer.h"
#include "render/RayTracer.h"
#include "util/image/ImageUtil.h"
#include "object/native/Cylinder.h"
#include "material/Metal.h"
#include "object/native/Sphere.h"
#include "material/Dielectric.h"
#include "object/native/TriangularPyramid.h"

int main(int argc, char * argv[]) {
    // default parameters
    int width = 300;
    int height = 300;
    int threadCount = 5;
    int samplePerPixel = 50;
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

    // bottom plane
    mats.push_back(new Lambertian({0.9, 0.9, 0.9}));
    objs.push_back(new Rectangle({-5, 0, 0}, {10, 0, 0}, {0, 0, -5}, mats.back()));
    // back plane
    mats.push_back(new Lambertian({0.9, 0.9, 0.9}));
    objs.push_back(new Rectangle({-5, 0, -5}, {10, 0, 0}, {0, 10, 0}, mats.back()));
    // left plane
    mats.push_back(new Lambertian({0, 0.9, 0}));
    objs.push_back(new Rectangle({-5, 0, -5}, {0, 0, 5}, {0, 10, 0}, mats.back()));
    // right plane
    mats.push_back(new Lambertian({0.9, 0, 0}));
    objs.push_back(new Rectangle({5, 0, -5}, {0, 0, 5}, {0, 10, 0}, mats.back()));
    // top plane
    mats.push_back(new Lambertian({0.9, 0.9, 0.9}));
    objs.push_back(new Rectangle({-5, 10, 0}, {10, 0, 0}, {0, 0, -5}, mats.back()));
    // light
    mats.push_back(new DiffuseLight({4, 4, 4}));
    objs.push_back(new Disk({0, 9.99, -2.5}, {0, -1, 0}, 1.5, mats.back()));
    // cylinder
    mats.push_back(new Lambertian({0.4, 0.2, 0.1}));
    objs.push_back(new Cylinder({-2.5, 3.5, -3}, {0, 1, 0}, 1.5, 7, mats.back()));
    // sphere
    mats.push_back(new Metal({0.7, 0.6, 0.5}));
    objs.push_back(new Sphere({1.0, 2, -3.5}, 1.8, mats.back()));
    // triangular pyramid
    mats.push_back(new Dielectric(1.5));
    objs.push_back(new TriangularPyramid({1.0, 0, -0.5}, {4.5, 0, -1.}, {2.8, 0, -1.8}, {2.5, 5, -1.1}, mats.back()));

    Hittable * scene = new BVHTree(&objs);
    Camera * camera = new Perspective({0, 5, 12}, {0, 0, -1}, {0, 1, 0}, 3.5, 3, 3);
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

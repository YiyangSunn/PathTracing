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

// render an image with lots of random spheres
int main() {
    std::vector<Material *> mats;
    std::vector<Hittable *> objs;

    mats.push_back(new Lambertian({0.5, 0.5, 0.5}));
    objs.push_back(new Sphere({0, -1000, 0}, 1000, mats[0]));

    for (int i = -11; i < 11; ++i) {
        for (int j = -11; j < 11; ++j) {
            Vector3d center((float) i + 0.9f * (float) drand48(), 0.2, (float) j + 0.9f * (float) drand48());
            if ((center - Vector3d(4, 0.2, 0)).getLength() > 0.9) {
                auto p = (float) drand48();
                if (p < 0.6) {
                    mats.push_back(new Lambertian({(float) drand48() * (float) drand48(), (float) drand48() * (float) drand48(), (float) drand48() * (float) drand48()}));
                    objs.push_back(new Sphere(center, 0.2, mats.back()));
                } else if (p < 0.85) {
                    mats.push_back(new Metal({0.5f * (float) (1 + drand48()), 0.5f * (float) (1 + drand48()), 0.5f * (float) (1 + drand48())}, 0.5f * (float) drand48()));
                    objs.push_back(new Sphere(center, 0.2, mats.back()));
                } else {
                    mats.push_back(new Dielectric(1.5));
                    objs.push_back(new Sphere(center, 0.2, mats.back()));
                }
            }
        }
    }

    mats.push_back(new Dielectric(1.5));
    objs.push_back(new Sphere({0, 1, 0}, 1.0, mats.back()));
    mats.push_back(new Lambertian({0.4, 0.2, 0.1}));
    objs.push_back(new Sphere({-4, 1, 0}, 1.0, mats.back()));
    mats.push_back(new Metal({0.7, 0.6, 0.5}, 0));
    objs.push_back(new Sphere({4, 1, 0}, 1.0, mats.back()));

    Hittable * scene = new HittableList(objs);
    Camera * camera = new DefocusBlur({13, 2, 3}, {-13, -2, -3}, {0, 1, 0}, 10, 5.7, 3.8, 0.1);
    Renderer * renderer = new RayTracer(50, 50, 5);
    auto * im = new ImageBuffer(240, 160);

    renderer->render(camera, scene, im);
    ImageUtil::gammaCorrection(im, 2);
    ImageUtil::writePPM(*im, "img0.ppm", 6);

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

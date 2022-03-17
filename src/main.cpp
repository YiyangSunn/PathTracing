#include "render/Renderer.h"
#include "render/RayTracer.h"
#include "object/HittableList.h"
#include "camera/Perspective.h"
#include "util/image/ImageUtil.h"
#include "object/native/Sphere.h"
#include "material/Lambertian.h"

int main() {
    std::vector<Material *> mats;
    mats.push_back(new Lambertian({0.5, 0.5, 0.5}));
    mats.push_back(new Lambertian({0.5, 0.5, 0.5}));

    std::vector<Hittable *> objs;
    objs.push_back(new Sphere({0, 0, -1}, 0.5, mats[0]));
    objs.push_back(new Sphere({0, -100.5, -1}, 100, mats[1]));

    Hittable * scene = new HittableList(objs);
    Camera * camera = new Perspective({0, 0, 0}, {0, 0, -1}, {0, 1, 0}, 1, 4, 2);
    Renderer * renderer = new RayTracer(camera, scene, 10, 50);
    auto * im = new ImageBuffer(400, 200);

    renderer->render(im);
    ImageUtil::writePPM(*im, "img0.ppm", 3);

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

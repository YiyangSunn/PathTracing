#include "util/accelerator/BVH.h"
#include "scene/Scene.h"
#include "util/mesh/OBJFile.h"
#include "texture/ConstantTexture.h"
#include "material/Emission.h"
#include "material/Lambertian.h"
#include "camera/PerspectiveCamera.h"
#include "util/image/ImageBuffer.h"
#include "render/PathTracer.h"
#include "util/image/ImageUtil.h"
#include "render/LightSampler.h"
#include "render/BRDFSampler.h"
#include "render/MISampler.h"
#include "material/TorranceSparrow.h"

int main() {
    HitResolver * resolver = new BVH();
    Scene * scene = new Scene(resolver);
    OBJFile * file = new OBJFile("../resources/cube.obj");

    Vector3d f0(1.0f, 0.71f, 0.29f);
    Material * mat_1 = new TorranceSparrow(f0, 0.5, nullptr);
    Object * cube = file->loadObject("Cube", mat_1);
    scene->addObject(cube);

    Texture * texture_2 = new ConstantTexture({1.f, 1.f, 1.f});
    Material * mat_2 = new Lambertian(texture_2);
    Object * plane = file->loadObject("Plane", mat_2);
    scene->addObject(plane);

    Texture * texture_3 = new ConstantTexture({3, 3, 3});
    Material * mat_3 = new Emission(texture_3);
    Object * light = file->loadObject("light_Plane.001", mat_3);
    scene->addLight(light);

    scene->build();

    Vector3d pos(6.8245f, -6.9258f, 5.1106f);
    Vector3d tar(0, 0, 0);
    Vector3d up(0, 0, 1);
    Camera * camera = new PerspectiveCamera(pos, tar - pos, up, 5.5, 3.2, 1.8);

    ImageBuffer * im = new ImageBuffer(480, 270);
    Renderer * renderer = new PathTracer(500, 5, 5);
    renderer->render(camera, scene, im);

    ImageUtil::gammaCorrection(im, 2.2);
    ImageUtil::writePPM(*im, "cube_ts_new_path.ppm", 6);

    return 0;
}

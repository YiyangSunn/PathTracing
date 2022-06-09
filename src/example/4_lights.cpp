#include "util/mesh/OBJFile.h"
#include "material/Emission.h"
#include "texture/ConstantTexture.h"
#include "util/accelerator/BVH.h"
#include "material/Lambertian.h"
#include "camera/Camera.h"
#include "camera/PerspectiveCamera.h"
#include "util/image/ImageBuffer.h"
#include "render/Renderer.h"
#include "render/PathTracer.h"
#include "util/image/ImageUtil.h"
#include "render/LightSampler.h"
#include "render/BRDFSampler.h"
#include "render/MISampler.h"
#include "material/TorranceSparrow.h"

int main() {
    HitResolver * resolver = new BVH();
    Scene * scene = new Scene(resolver);
    OBJFile * file = new OBJFile("../resource/4_lights.obj");

    Texture * texture_1 = new ConstantTexture({1.f, 0.219f, 0.563f});
    Material * mat_1 = new Emission(texture_1);
    Object * light_1 = file->loadObject("light_1_Circle.001", mat_1);
    scene->addLight(light_1);

    Texture * texture_2 = new ConstantTexture({1.f, 0.679f, 0.025f});
    Material * mat_2 = new Emission(texture_2);
    Object * light_2 = file->loadObject("light_2_Plane.006", mat_2);
    scene->addLight(light_2);

    Texture * texture_3 = new ConstantTexture({0.347f, 1.f, 0.325f});
    Material * mat_3 = new Emission(texture_3);
    Object * light_3 = file->loadObject("light_3_Circle.003", mat_3);
    scene->addLight(light_3);

    Texture * texture_4 = new ConstantTexture({0.228f, 1.f, 0.979f});
    Material * mat_4 = new Emission(texture_4);
    Object * light_4 = file->loadObject("light_4_Circle.002", mat_4);
    scene->addLight(light_4);

    Texture * texture_5 = new ConstantTexture({1.f, 1.f, 1.f});
    Material * mat_5 = new Emission(texture_5);
    Object * light_5 = file->loadObject("light_5_Plane", mat_5);
    scene->addLight(light_5);

    Vector3f wall_albedo(1.f, 1.f, 1.f);

    Vector3f f0(0.16f, 0.16f, 0.16f);

    Texture * texture_6 = new ConstantTexture(wall_albedo);
    Material * mat_6 = new Lambertian(texture_6);
    Object * wall_1 = file->loadObject("wall_1_Plane.010", mat_6);
    scene->addObject(wall_1);

    Texture * texture_7 = new ConstantTexture(wall_albedo);
    Material * mat_7 = new Lambertian(texture_7);
    Object * wall_2 = file->loadObject("wall_2_Plane.011", mat_7);
    scene->addObject(wall_2);

    Texture * texture_8 = new ConstantTexture(wall_albedo);
    Material * mat_8 = new Lambertian(texture_8);
    Object * wall_3 = file->loadObject("wall_3_Plane.012", mat_8);
    scene->addObject(wall_3);

    Texture * texture_9 = new ConstantTexture(wall_albedo);
    Material * mat_9 = new Lambertian(texture_9);
    Object * wall_4 = file->loadObject("wall_4_Plane.013", mat_9);
    scene->addObject(wall_4);

    Texture * texture_10 = new ConstantTexture(wall_albedo);
    Material * mat_10 = new Lambertian(texture_10);
    Object * wall_5 = file->loadObject("wall_5_Plane.014", mat_10);
    scene->addObject(wall_5);

    Texture * texture_11 = new ConstantTexture(wall_albedo);
    Material * mat_11 = new Lambertian(texture_11);
    Object * wall_6 = file->loadObject("wall_6_Plane.003", mat_11);
    scene->addObject(wall_6);

    Material * mat_12 = new TorranceSparrow(f0, 0.1, nullptr);
    Object * board_1 = file->loadObject("board_1_Plane.015", mat_12);
    scene->addObject(board_1);

    Material * mat_13 = new TorranceSparrow(f0, 0.12, nullptr);
    Object * board_2 = file->loadObject("board_2_Plane.016", mat_13);
    scene->addObject(board_2);

    Material * mat_14 = new TorranceSparrow(f0, 0.14, nullptr);
    Object * board_3 = file->loadObject("board_3_Plane.001", mat_14);
    scene->addObject(board_3);

    Material * mat_15 = new TorranceSparrow(f0, 0.16, nullptr);
    Object * board_4 = file->loadObject("board_4_Plane.002", mat_15);
    scene->addObject(board_4);

    scene->build();

    Vector3f pos(-0.091733f, 10.f, 6.92956f);
    Vector3f tar(-0.1003f, 0, 4.6748f);
    Vector3f up(0, 0, 1);
    Camera * camera = new PerspectiveCamera(pos, tar - pos, up, 5.8, 3, 3);

    ImageBuffer * im = new ImageBuffer(100, 100);
    Renderer * renderer = new PathTracer(64, 8, 5);
//    Renderer * renderer = new BRDFSampler(1000, 5);
    renderer->render(camera, scene, im);

    ImageUtil::gammaCorrection(im, 2.2f);
    ImageUtil::writePPM(*im, "4_lights_path_mis_cos_weighted_64.ppm", 6);

    return 0;
}

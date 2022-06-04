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
    OBJFile * file = new OBJFile("../resources/sphere.obj");

    Vector3d f0(1.0f, 0.71f, 0.29f);
    Material * mat_1 = new TorranceSparrow(f0, 0.5, nullptr);
    Object * sphere = file->loadObject("Sphere", mat_1);
    scene->addObject(sphere);

    Vector3d wall_albedo(0.8, 0.8, 0.8);

    Texture * texture_2 = new ConstantTexture(wall_albedo);
    Material * mat_2 = new Lambertian(texture_2);
    Object * wall_1 = file->loadObject("wall_1_Plane.001", mat_2);
    scene->addObject(wall_1);

    Texture * texture_3 = new ConstantTexture(wall_albedo);
    Material * mat_3 = new Lambertian(texture_3);
    Object * wall_2 = file->loadObject("wall_2_Plane.002", mat_3);
    scene->addObject(wall_2);

    Texture * texture_4 = new ConstantTexture(wall_albedo);
    Material * mat_4 = new Lambertian(texture_4);
    Object * wall_3 = file->loadObject("wall_3_Plane.003", mat_4);
    scene->addObject(wall_3);

    Texture * texture_5 = new ConstantTexture(wall_albedo);
    Material * mat_5 = new Lambertian(texture_5);
    Object * wall_4 = file->loadObject("wall_4_Plane.004", mat_5);
    scene->addObject(wall_4);

    Texture * texture_6 = new ConstantTexture(wall_albedo);
    Material * mat_6 = new Lambertian(texture_6);
    Object * wall_5 = file->loadObject("wall_5_Plane.005", mat_6);
    scene->addObject(wall_5);

    Texture * texture_7 = new ConstantTexture(wall_albedo);
    Material * mat_7 = new Lambertian(texture_7);
    Object * wall_6 = file->loadObject("wall_6_Plane", mat_7);
    scene->addObject(wall_6);

    Vector3d intensity(1.f, 1.f, 1.f);

    Texture * texture_8 = new ConstantTexture(intensity);
    Material * mat_8 = new Emission(texture_8);
    Object * light_1 = file->loadObject("light_1_Plane.006", mat_8);
    scene->addLight(light_1);

    Texture * texture_9 = new ConstantTexture(intensity);
    Material * mat_9 = new Emission(texture_9);
    Object * light_2 = file->loadObject("light_2_Plane.007", mat_9);
    scene->addLight(light_2);

    Texture * texture_10 = new ConstantTexture(intensity);
    Material * mat_10 = new Emission(texture_10);
    Object * light_3 = file->loadObject("light_3_Plane.008", mat_10);
    scene->addLight(light_3);

    Texture * texture_11 = new ConstantTexture(intensity);
    Material * mat_11 = new Emission(texture_11);
    Object * light_4 = file->loadObject("light_4_Plane.009", mat_11);
    scene->addLight(light_4);

    scene->build();

    Vector3d pos(0, -6.9258f, 0);
    Vector3d tar(0, 0, 0);
    Vector3d up(0, 0, 1);
    Camera * camera = new PerspectiveCamera(pos, tar - pos, up, 2.6, 3.2, 3.2);

    ImageBuffer * im = new ImageBuffer(180, 180);
//    Renderer * renderer = new PathTracer(128, 4,5);
//    Renderer * renderer = new LightSampler(128, 5);
    Renderer * renderer = new BRDFSampler(128, 5);
    renderer->render(camera, scene, im);

    ImageUtil::gammaCorrection(im, 2.2);
    ImageUtil::writePPM(*im, "sphere_path_brdf.ppm", 6);

    return 0;
}

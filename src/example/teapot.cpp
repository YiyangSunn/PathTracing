#include "util/BVH.h"
#include "scene/Scene.h"
#include "util/OBJFile.h"
#include "texture/ConstantTexture.h"
#include "material/Lambertian.h"
#include "material/Emission.h"
#include "material/GlossyBRDF.h"
#include "camera/PerspectiveCamera.h"
#include "util/ImageBuffer.h"
#include "render/PathTracer.h"
#include "util/ImageUtil.h"

int main() {
    HitResolver * resolver = new BVH();
    Scene * scene = new Scene(resolver);
    OBJFile * file = new OBJFile("../resource/teapot.obj");

    Texture * texture_1 = new ConstantTexture({0.8, 0.8, 0.8});
    Material * mat_1 = new Lambertian(texture_1);
    Object * wall = file->loadObject("wall_Plane.006", mat_1);
    scene->addObject(wall);

    Texture * texture_2 = new ConstantTexture({0.262, 0.130, 0.078});
    Material * mat_2 = new Lambertian(texture_2);
    Object * floor = file->loadObject("floor_Plane.001", mat_2);
    scene->addObject(floor);

    Texture * texture_3 = new ConstantTexture({0.8, 0.8, 0.8});
    Material * mat_3 = new Lambertian(texture_3);
    Object * saucer = file->loadObject("saucer_saucer_Circle", mat_3);
    scene->addObject(saucer);

    Texture * texture_4 = new ConstantTexture({10, 10, 10});
    Material * mat_4 = new Emission(texture_4);
    Object * light = file->loadObject("light_Sphere", mat_4);
    scene->addLight(light);

    float roughness = 0.3;

    Material * mat_5 = new GlossyBRDF({1, 0.687, 0.283}, roughness, nullptr);
    Object * spoon = file->loadObject("spoon_spoon_mesh_Sphere.001", mat_5);
    scene->addObject(spoon);

    Material * mat_6 = new GlossyBRDF({0.552, 0.565, 0.565}, roughness, nullptr);
    Object * teapot = file->loadObject("Teapot", mat_6);
    scene->addObject(teapot);

    Material * mat_7 = new GlossyBRDF({0.930, 0.905, 0.807}, roughness, nullptr);
    Object * cup = file->loadObject("cup_cup_Cylinder", mat_7);
    scene->addObject(cup);

    scene->build();

    Vector3f pos(7.353, -0.12418, 6.7735);
    Vector3f tar(1.3442, 0.04966, 1.7319);
    Vector3f up(0, 0, 1);
    Camera * camera = new PerspectiveCamera(pos, tar, up, 3, 3.2, 1.8);

    ImageBuffer * im = new ImageBuffer(160, 90);
    Renderer * renderer = new PathTracer(64, 10,5);
    renderer->render(camera, scene, im);

    ImageUtil::gammaCorrection(im, 2.2);
    ImageUtil::writePPM(*im, "teapot_without_mis.ppm", 6);

    return 0;
}

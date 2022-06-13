#include "util/BVH.h"
#include "scene/Scene.h"
#include "util/OBJFile.h"
#include "texture/ConstantTexture.h"
#include "material/Lambertian.h"
#include "material/GlossyBRDF.h"
#include "material/Emission.h"
#include "camera/PerspectiveCamera.h"
#include "util/ImageBuffer.h"
#include "render/LightSampler.h"
#include "util/ImageUtil.h"
#include "render/BRDFSampler.h"
#include "render/MISampler.h"

int main() {
    HitResolver * resolver = new BVH();
    Scene * scene = new Scene(resolver);
    scene->setBackground({0.053, 0.053, 0.053});
    OBJFile * file = new OBJFile("../resource/mis.obj");

    Texture * texture_1 = new ConstantTexture({0.16, 0.16, 0.16});
    Material * mat_1 = new Lambertian(texture_1);
    Object * wall = file->loadObject("wall_Plane.004", mat_1);
    scene->addObject(wall);

    float roughness = 0.05;

    Material * mat_2 = new GlossyBRDF({0.8, 0.8, 0.8}, roughness, nullptr);
    Object * floor_1 = file->loadObject("floor_1_Plane", mat_2);
    scene->addObject(floor_1);

    Material * mat_3 = new GlossyBRDF({0.8, 0.8, 0.8}, 1 - roughness, nullptr);
    Object * floor_2 = file->loadObject("floor_2_Plane.001", mat_3);
    scene->addObject(floor_2);

    Texture * texture_2 = new ConstantTexture(10 * Vector3f(0.002, 0.604, 1));
    Material * mat_4 = new Emission(texture_2);
    Object * light_1 = file->loadObject("light_1_Circle", mat_4);
    scene->addLight(light_1);

    Texture * texture_3 = new ConstantTexture(100 * Vector3f(1, 0.113, 0.022));
    Material * mat_5 = new Emission(texture_3);
    Object * light_2 = file->loadObject("light_2_Circle.001", mat_5);
    scene->addLight(light_2);

    scene->build();

    Vector3f pos(0, -8.6131, 2.2931);
    Vector3f tar(0, -6.2566, 1.7982);
    Vector3f up(0, 0, 1);
    Camera * camera = new PerspectiveCamera(pos, tar, up, 7, 6, 6);

    ImageBuffer * im = new ImageBuffer(600, 600);
//    Renderer * renderer = new LightSampler(64, 5);
//    Renderer * renderer = new BRDFSampler(64, 5);
    Renderer * renderer = new MISampler(64, 5);
    renderer->render(camera, scene, im);

    ImageUtil::gammaCorrection(im, 2.2);
//    ImageUtil::writePPM(*im, "mis_light.ppm", 6);
//    ImageUtil::writePPM(*im, "mis_brdf.ppm", 6);
    ImageUtil::writePPM(*im, "mis_mis.ppm", 6);

    return 0;
}

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
#include "render/LightSampler.h"
#include "render/BRDFSampler.h"
#include "render/MISampler.h"

int main() {
    HitResolver * resolver = new BVH();
    Scene * scene = new Scene(resolver);
    scene->setBackground({0.053, 0.053, 0.053});
    OBJFile * file = new OBJFile("../resource/poke.obj");

    Texture * texture_1 = new ConstantTexture({0.8, 0.8, 0.8});
    Material * mat_1 = new Lambertian(texture_1);
    Object * floor = file->loadObject("floor_Plane", mat_1);
    scene->addObject(floor);

    Texture * texture_2 = new ConstantTexture({0.16, 0.16, 0.16});
    Material * mat_2 = new Lambertian(texture_2);
//    mat_2->setEnableMIS(true);
    Object * lamp_shell = file->loadObject("lamp_shell_Cylinder.004_Cylinder.005", mat_2);
    scene->addObject(lamp_shell);

    Texture * texture_3 = new ConstantTexture({0.03, 0.03, 0.03});
    Material * mat_3 = new Lambertian(texture_3);
    Object * lamp_line = file->loadObject("lamp_line_BezierCurve", mat_3);
    scene->addObject(lamp_line);

    Texture * texture_4 = new ConstantTexture({0.8, 0.8, 0.8});
    Material * mat_4 = new Lambertian(texture_4);
    Object * lamp_button = file->loadObject("lamp_button_Cube_Cube.001", mat_4);
    scene->addObject(lamp_button);

    Texture * texture_5 = new ConstantTexture({10, 10, 10});
    Material * mat_5 = new Emission(texture_5);
    Object * light = file->loadObject("light_Sphere.002", mat_5);
    scene->addLight(light);

    Texture * texture_6 = new ConstantTexture(100 * Vector3f(0, 0.973, 1));
    Material * mat_6 = new Emission(texture_6);
    Object * light_ring = file->loadObject("light_ring_light_ring_Sphere.001", mat_6);
    scene->addLight(light_ring);

    float roughness = 0.1;

    Material * mat_7 = new GlossyBRDF({0.533, 0.533, 0.539}, roughness, nullptr);
//    mat_7->setEnableMIS(true);
    Object * bottom = file->loadObject("bottom_bottom_Sphere.006", mat_7);
    scene->addObject(bottom);

    Material * mat_8 = new GlossyBRDF({0.546, 0.030, 0.026}, roughness, nullptr);
//    mat_8->setEnableMIS(true);
    Object * top = file->loadObject("top_top_Sphere.005", mat_8);
    scene->addObject(top);

    Material * mat_9 = new GlossyBRDF({0.184, 0.188, 0.202}, 0.5, nullptr);
//    mat_9->setEnableMIS(true);
    Object * button = file->loadObject("button_button_Sphere.002", mat_9);
    scene->addObject(button);

    Material * mat_10 = new GlossyBRDF({0.105, 0.125, 0.120}, 0.5, nullptr);
//    mat_10->setEnableMIS(true);
    Object * ribbon = file->loadObject("ribbon_ribbon_Sphere.004", mat_10);
    scene->addObject(ribbon);

    scene->build();

    Vector3f pos(0.10523, -4.1174, 1.9983);
    Vector3f tar(-1.0515, 0.496, 0.75624);
    Vector3f up(0, 0, 1);
    Camera * camera = new PerspectiveCamera(pos, tar, up, 8, 6, 6);

    ImageBuffer * im = new ImageBuffer(200, 200);
//    Renderer * renderer = new PathTracer(128, 10,5, FLT_MAX);
    Renderer * renderer = new LightSampler(256, 5);
//    Renderer * renderer = new BRDFSampler(1024, 5);
//    Renderer * renderer = new MISampler(128, 5);
    renderer->render(camera, scene, im);

    ImageUtil::gammaCorrection(im, 2.2);
    ImageUtil::writePPM(*im, "poke_light.ppm", 6);

    return 0;
}

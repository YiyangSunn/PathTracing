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
    OBJFile * file = new OBJFile("../resource/bmps.obj");

    Texture * texture_1 = new ConstantTexture({0.8, 0.8, 0.8});
    Material * mat_1 = new Lambertian(texture_1);
    Object * wall = file->loadObject("wall_Plane.005", mat_1);
    scene->addObject(wall);

    Texture * texture_2 = new ConstantTexture({0.08, 0.08, 0.08});
    Material * mat_2 = new Lambertian(texture_2);
    Object * floor = file->loadObject("floor_Plane.003", mat_2);
    scene->addObject(floor);

    Texture * texture_3 = new ConstantTexture({10, 10, 10});
    Material * mat_3 = new Emission(texture_3);
    Object * light = file->loadObject("light_Circle", mat_3);
    scene->addLight(light);

    Material * mat_4 = new GlossyBRDF({0.913, 0.922, 0.922}, 0.5, nullptr);
    Object * base = file->loadObject("base_Base.001_Base", mat_4);
    scene->addObject(base);

    Material * mat_5 = new GlossyBRDF({0.913, 0.922, 0.922}, 0.5, nullptr);
    Object * body = file->loadObject("body_CoreSolidMaterial", mat_5);
    scene->addObject(body);

    Material * mat_6 = new GlossyBRDF({0.597, 0.153, 0.082}, 0.8, nullptr);
//    mat_6->setEnableMIS(true);
    Object * shell = file->loadObject("shell_SolidModel", mat_6);
    scene->addObject(shell);

    Material * mat_7 = new GlossyBRDF({1, 0.71, 0.29}, 0.3, nullptr);
    mat_7->setEnableMIS(true);
    Object * ball = file->loadObject("ball_SolidModel.001", mat_7);
    scene->addObject(ball);

    scene->build();

    Vector3f pos(10.681, -22.177, 22.014);
    Vector3f tar(1.6934, -3.0412, 7.35);
    Vector3f up(0, 0, 1);
    Camera * camera = new PerspectiveCamera(pos, tar, up, 10, 6, 5);

    ImageBuffer * im = new ImageBuffer(150, 125);
    Renderer * renderer = new PathTracer(128, 10,5, FLT_MAX);
    renderer->render(camera, scene, im);

    ImageUtil::gammaCorrection(im, 2.2);
    ImageUtil::writePPM(*im, "bmps_new_mis.ppm", 6);

    return 0;
}

#include "util/HitResolver.h"
#include "util/BVH.h"
#include "scene/Scene.h"
#include "util/OBJFile.h"
#include "camera/PerspectiveCamera.h"
#include "util/ImageBuffer.h"
#include "render/PathTracer.h"
#include "util/ImageUtil.h"
#include "texture/Texture.h"
#include "texture/ConstantTexture.h"
#include "material/Lambertian.h"
#include "material/Emission.h"
#include "Configuration.h"
#include "render/RendererFactory.h"

int main(int argc, char * argv[]) {
    Configuration * conf = (new Configuration())
            ->setDefaultWidth(200)
            ->setDefaultHeight(200)
            ->setDefaultSamplePerPixel(64)
            ->setDefaultMaxDepth(10)
            ->setDefaultThreadCount(5)
            ->setDefaultIntegrator("path")
            ->setDefaultOutputFile("../image/street.ppm")
            ->parseArgs(argc, argv);

    HitResolver * resolver = new BVH();
    Scene * scene = new Scene(resolver);
    OBJFile * file = new OBJFile("../resource/street.obj");

    Texture * texture_1 = new ConstantTexture({0.8, 0.8, 0.8});
    Material * mat_1 = new Lambertian(texture_1);
    Object * ground = file->loadObject("ground_Plane", mat_1);
    scene->addObject(ground);

    Texture * texture_2 = new ConstantTexture({0.534, 0.209, 0.007});
    Material * mat_2 = new Lambertian(texture_2);
    Object * bench = file->loadObject("bench_bench_face_Cube.008", mat_2);
    scene->addObject(bench);

    Texture * texture_3 = new ConstantTexture({0.022, 0.022, 0.022});
    Material * mat_3 = new Lambertian(texture_3);
    Object * bench_leg = file->loadObject("bench_leg_bench_leg_Cube.004", mat_3);
    scene->addObject(bench_leg);

    Texture * texture_4 = new ConstantTexture({0.114, 0.610, 0.694});
    Material * mat_4 = new Lambertian(texture_4);
    Object * mug = file->loadObject("mug_Cylinder.004", mat_4);
    scene->addObject(mug);

    Texture * texture_5 = new ConstantTexture({0, 0.236, 0.004});
    Material * mat_5 = new Lambertian(texture_5);
    Object * stem = file->loadObject("stem_stem_Cylinder", mat_5);
    scene->addObject(stem);

    Texture * texture_6 = new ConstantTexture({0.799, 0.371, 0.008});
    Material * mat_6 = new Lambertian(texture_6);
    Object * lantern = file->loadObject("lantern_lantern_Sphere", mat_6);
    scene->addObject(lantern);

    Texture * texture_7 = new ConstantTexture({0.080, 0.033, 0.020});
    Material * mat_7 = new Lambertian(texture_7);
    Object * lamp = file->loadObject("lamp_lamp_Cylinder.002", mat_7);
    scene->addObject(lamp);

    Texture * texture_8 = new ConstantTexture({100, 100, 100});
    Material * mat_8 = new Emission(texture_8);
    Object * lamp_light = file->loadObject("light_lamp_Cylinder.001", mat_8);
    scene->addLight(lamp_light);

    Texture * texture_9 = new ConstantTexture({10, 10, 10});
    Material * mat_9 = new Emission(texture_9);
    Object * lantern_light = file->loadObject("lantern_light_lantern_light_Sphere.001", mat_9);
    scene->addLight(lantern_light);

    scene->build();

    Vector3f pos(2.0904, -14.575f, 7.3328f);
    Vector3f tar(2.8903f, 20.4f, 2.2106f);
    Vector3f up(0, 0, 1);
    Camera * camera = new PerspectiveCamera(pos, tar, up, 3.6, 3.2, 3.2);

    ImageBuffer * im = new ImageBuffer(conf->getWidth(), conf->getHeight());
    Renderer * renderer = RendererFactory::getInstance(*conf);
    renderer->render(camera, scene, im);

    ImageUtil::gammaCorrection(im, 2.2);
    ImageUtil::writePPM(*im, conf->getOutputFile(), 6);

    return 0;
}

#include "util/BVH.h"
#include "scene/Scene.h"
#include "util/OBJFile.h"
#include "texture/ConstantTexture.h"
#include "material/Lambertian.h"
#include "material/Emission.h"
#include "camera/PerspectiveCamera.h"
#include "util/ImageBuffer.h"
#include "render/PathTracer.h"
#include "util/ImageUtil.h"
#include "Configuration.h"
#include "render/RendererFactory.h"

int main (int argc, char * argv[]) {
    Configuration * conf = (new Configuration())
            ->setDefaultWidth(480)
            ->setDefaultHeight(270)
            ->setDefaultSamplePerPixel(128)
            ->setDefaultMaxDepth(10)
            ->setDefaultThreadCount(5)
            ->setDefaultIntegrator("path")
            ->setDefaultOutputFile("../image/desk.ppm")
            ->parseArgs(argc, argv);

    HitResolver * resolver = new BVH();
    Scene * scene = new Scene(resolver);
    OBJFile * file = new OBJFile("../resource/desk.obj");

    Texture * texture_1 = new ConstantTexture({0.162, 1, 0.004});
    Material * mat_1 = new Lambertian(texture_1);
    Object * wall = file->loadObject("wall_Plane.011", mat_1);
    scene->addObject(wall);

    Texture * texture_2 = new ConstantTexture({0.008, 0.799, 0.485});
    Material * mat_2 = new Lambertian(texture_2);
    Object * blanket = file->loadObject("blanket_Plane.006", mat_2);
    scene->addObject(blanket);

    Texture * texture_3 = new ConstantTexture({0.008, 0.799, 0.485});
    Material * mat_3 = new Lambertian(texture_3);
    Object * chair = file->loadObject("chair_Plane", mat_3);
    scene->addObject(chair);

    Texture * texture_4 = new ConstantTexture({0.799, 0.361, 0.008});
    Material * mat_4 = new Lambertian(texture_4);
    Object * chair_back = file->loadObject("chair_back_Plane.003", mat_4);
    scene->addObject(chair_back);

    Texture * texture_5 = new ConstantTexture({0.799, 0.361, 0.008});
    Material * mat_5 = new Lambertian(texture_5);
    Object * chair_leg = file->loadObject("chair_leg_Plane.001", mat_5);
    scene->addObject(chair_leg);

    Texture * texture_6 = new ConstantTexture({0.799, 0.361, 0.008});
    Material * mat_6 = new Lambertian(texture_6);
    Object * chair_connector = file->loadObject("chair_connector_Plane.002", mat_6);
    scene->addObject(chair_connector);

    Texture * texture_7 = new ConstantTexture({0.799, 0.361, 0.008});
    Material * mat_7 = new Lambertian(texture_7);
    Object * desk = file->loadObject("desk_Plane.004", mat_7);
    scene->addObject(desk);

    Texture * texture_8 = new ConstantTexture({0.799, 0.361, 0.008});
    Material * mat_8 = new Lambertian(texture_8);
    Object * desk_leg = file->loadObject("desk_leg_Plane.005", mat_8);
    scene->addObject(desk_leg);

    Texture * texture_9 = new ConstantTexture({1, 0.225, 0.283});
    Material * mat_9 = new Lambertian(texture_9);
    Object * floor = file->loadObject("floor_Plane.007", mat_9);
    scene->addObject(floor);

    Texture * texture_10 = new ConstantTexture({0.022, 0.022, 0.022});
    Material * mat_10 = new Lambertian(texture_10);
    Object * light_frame = file->loadObject("light_frame_Plane.015", mat_10);
    scene->addObject(light_frame);

    Texture * texture_11 = new ConstantTexture({20, 20, 20});
    Material * mat_11 = new Emission(texture_11);
    Object * light = file->loadObject("light_Plane.016", mat_11);
    scene->addLight(light);

    scene->build();

    Vector3f pos(6.1977, -14.469, 5.7637);
    Vector3f tar(-7.7976, 6.5378, 0.38026);
    Vector3f up(0, 0, 1);
    Camera * camera = new PerspectiveCamera(pos, tar, up, 4.16, 3.2, 1.8);

    ImageBuffer * im = new ImageBuffer(conf->getWidth(), conf->getHeight());
    Renderer * renderer = RendererFactory::getInstance(*conf);
    renderer->render(camera, scene, im);

    ImageUtil::gammaCorrection(im, 2.2);
    ImageUtil::writePPM(*im, conf->getOutputFile(), 6);

    return 0;
}

#include "util/BVH.h"
#include "scene/Scene.h"
#include "util/OBJFile.h"
#include "texture/ImageTexture.h"
#include "material/Lambertian.h"
#include "texture/ConstantTexture.h"
#include "material/Emission.h"
#include "material/GlossyBRDF.h"
#include "camera/PerspectiveCamera.h"
#include "render/PathTracer.h"
#include "Configuration.h"
#include "render/RendererFactory.h"

int main(int argc, char * argv[]) {
    Configuration * conf = (new Configuration())
            ->setDefaultWidth(320)
            ->setDefaultHeight(180)
            ->setDefaultSamplePerPixel(128)
            ->setDefaultMaxDepth(10)
            ->setDefaultThreadCount(5)
            ->setDefaultIntegrator("path")
            ->setDefaultOutputFile("../image/Higokumaru.ppm")
            ->parseArgs(argc, argv);

    HitResolver * resolver = new BVH();
    Scene * scene = new Scene(resolver);
    scene->setBackground({1.5, 1.5, 1.5});
    OBJFile * file = new OBJFile("../resource/Higokumaru/Higokumaru.obj");

    Texture * texture_1 = new ImageTexture("../resource/Higokumaru/Higo_Body.ppm");
    Material * mat_1 = new Lambertian(texture_1);
    Object * body = file->loadObject("body_Plane.039", mat_1);
    scene->addObject(body);

    Texture * texture_2 = new ImageTexture("../resource/Higokumaru/Higo_Hair.ppm");
    Material * mat_2 = new Lambertian(texture_2);
    Object * hair = file->loadObject("hair_Plane.040", mat_2);
    scene->addObject(hair);

    Texture * texture_3 = new ImageTexture("../resource/Higokumaru/Higo_Clothes.ppm");
    Material * mat_3 = new Lambertian(texture_3);
    Object * clothe = file->loadObject("clothe_Plane.006", mat_3);
    scene->addObject(clothe);

    Texture * texture_4 = new ImageTexture("../resource/Higokumaru/Higo_Clothes.ppm");
    Material * mat_4 = new GlossyBRDF(0.4, texture_4);
    Object * deco = file->loadObject("deco_Plane.007", mat_4);
    scene->addObject(deco);

    Texture * texture_5 = new ImageTexture("../resource/Higokumaru/Higo_Fire.ppm");
    Material * mat_5 = new Lambertian(texture_5);
    Object * fire = file->loadObject("fire_Plane.042", mat_5);
    scene->addObject(fire);

    Texture * texture_6 = new ImageTexture("../resource/Higokumaru/env.ppm");
    Material * mat_6 = new Lambertian(texture_6);
    Object * env = file->loadObject("env_Sphere.002", mat_6);
    scene->addObject(env);

    scene->build();

    Vector3f pos(0.15888, -32.332, 17.231);
    Vector3f tar(0.15888, -22.695, 14.56);
    Vector3f up(0, 0, 1);
    Camera * camera = new PerspectiveCamera(pos, tar, up, 3.7, 3.2, 1.8);

    ImageBuffer * im = new ImageBuffer(conf->getWidth(), conf->getHeight());
    Renderer * renderer = RendererFactory::getInstance(*conf);
    renderer->render(camera, scene, im);

    ImageUtil::gammaCorrection(im, 2.2);
    ImageUtil::writePPM(*im, conf->getOutputFile(), 6);

    return 0;
}

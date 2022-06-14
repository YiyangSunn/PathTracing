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
#include "texture/ImageTexture.h"
#include "render/BRDFSampler.h"
#include "Configuration.h"
#include "render/RendererFactory.h"

int main(int argc, char * argv[]) {
    Configuration * conf = (new Configuration())
            ->setDefaultWidth(240)
            ->setDefaultHeight(135)
            ->setDefaultSamplePerPixel(128)
            ->setDefaultMaxDepth(10)
            ->setDefaultThreadCount(5)
            ->setDefaultIntegrator("path")
            ->setDefaultOutputFile("../image/teapot.ppm")
            ->parseArgs(argc, argv);

    HitResolver * resolver = new BVH();
    Scene * scene = new Scene(resolver);
    OBJFile * file = new OBJFile("../resource/teapot/teapot.obj");

    Texture * texture_2 = new ImageTexture("../resource/teapot/tablecloth.ppm");
    Material * mat_2 = new Lambertian(texture_2);
    Object * tablecloth = file->loadObject("tablecloth_Plane.001", mat_2);
    scene->addObject(tablecloth);

    Texture * texture_3 = new ConstantTexture({0.8, 0.8, 0.8});
    Material * mat_3 = new Lambertian(texture_3);
    Object * saucer = file->loadObject("saucer_saucer_Circle", mat_3);
    scene->addObject(saucer);

    Texture * texture_4 = new ImageTexture("../resource/teapot/room_teapot.ppm", 1.f / 1.1f);
    Material * mat_4 = new Emission(texture_4);
    Object * room = file->loadObject("room_Sphere.001", mat_4);
    scene->addLight(room);

    Texture * texture_5 = new ConstantTexture({1, 0.687, 0.283});
    Material * mat_5 = new GlossyBRDF(0.3, texture_5);
    mat_5->setEnableMIS(true);
    Object * spoon = file->loadObject("spoon_spoon_mesh_Sphere.001", mat_5);
    scene->addObject(spoon);

    Texture * texture_6 = new ConstantTexture({0.552, 0.565, 0.565});
    Material * mat_6 = new GlossyBRDF(0.25, texture_6);
    mat_6->setEnableMIS(true);
    Object * teapot = file->loadObject("Teapot", mat_6);
    scene->addObject(teapot);

    Texture * texture_7 = new ConstantTexture({0.930, 0.905, 0.807});
    Material * mat_7 = new GlossyBRDF(0.4, texture_7);
    mat_7->setEnableMIS(true);
    Object * cup = file->loadObject("cup_cup_Cylinder", mat_7);
    scene->addObject(cup);

    scene->build();

    Vector3f pos(7.353, -0.12418, 6.7735);
    Vector3f tar(1.3442, 0.04966, 1.7319);
    Vector3f up(0, 0, 1);
    Camera * camera = new PerspectiveCamera(pos, tar, up, 3, 3.2, 1.8);

    ImageBuffer * im = new ImageBuffer(conf->getWidth(), conf->getHeight());
    Renderer * renderer = RendererFactory::getInstance(*conf);
    renderer->render(camera, scene, im);

    ImageUtil::gammaCorrection(im, 2.2);
    ImageUtil::writePPM(*im, conf->getOutputFile(), 6);

    return 0;
}

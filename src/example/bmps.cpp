#include <cstring>
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
#include "Configuration.h"
#include "render/RendererFactory.h"

float getRoughness(int argc, char * argv[]);

int main(int argc, char * argv[]) {
    Configuration * conf = (new Configuration())
            ->setDefaultWidth(180)
            ->setDefaultHeight(150)
            ->setDefaultSamplePerPixel(32)
            ->setDefaultMaxDepth(10)
            ->setDefaultThreadCount(5)
            ->setDefaultIntegrator("path")
            ->setDefaultOutputFile("../image/bmps.ppm")
            ->parseArgs(argc, argv);

    HitResolver * resolver = new BVH();
    Scene * scene = new Scene(resolver);
    OBJFile * file = new OBJFile("../resource/bmps/bmps.obj");

    Texture * texture_1 = new ConstantTexture({0.16, 0.16, 0.16});
    Material * mat_1 = new Lambertian(texture_1);
    Object * body = file->loadObject("body_Base.001_Base", mat_1);
    scene->addObject(body);

    Texture * texture_2 = new ImageTexture("../resource/bmps/greymarble.ppm");
    Material * mat_2 = new Lambertian(texture_2);
    Object * floor = file->loadObject("floor_Plane.003", mat_2);
    scene->addObject(floor);

    Texture * texture_3 = new ImageTexture("../resource/bmps/room_bmps.ppm");
    Material * mat_3 = new Emission(texture_3);
    Object * room = file->loadObject("room_Sphere.001", mat_3);
    scene->addLight(room);

    float roughness = getRoughness(argc, argv);

    Texture * texture_4 = new ConstantTexture({1, 0.71, 0.29});
    Material * mat_4 = new GlossyBRDF(roughness, texture_4);
    mat_4->setEnableMIS(roughness < 0.4);
    Object * shell = file->loadObject("shell_SolidModel", mat_4);
    scene->addObject(shell);

    scene->build();

    Vector3f pos(10.04, -25.85, 28.615);
    Vector3f tar(7.1031, -18.684, 22.289);
    Vector3f up(0, 0, 1);
    Camera * camera = new PerspectiveCamera(pos, tar, up, 7.5, 6, 5);

    ImageBuffer * im = new ImageBuffer(conf->getWidth(), conf->getHeight());
    Renderer * renderer = RendererFactory::getInstance(*conf);
    renderer->render(camera, scene, im);

    ImageUtil::gammaCorrection(im, 2.2);
    ImageUtil::writePPM(*im, conf->getOutputFile(), 6);

    return 0;
}

float getRoughness(int argc, char * argv[]) {
    for (int i = 0; i < argc; ++i) {
        if (!strcmp(argv[i], "-r")) {
            return std::stof(argv[i + 1]);
        }
    }
    // default value
    return 0.15;
}

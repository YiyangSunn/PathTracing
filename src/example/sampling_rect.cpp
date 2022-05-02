#include <vector>
#include <cmath>
#include <cassert>
#include "Configuration.h"
#include "object/Hittable.h"
#include "light/Light.h"
#include "material/Lambertian.h"
#include "object/native/Rectangle.h"
#include "camera/Camera.h"
#include "camera/Perspective.h"
#include "object/BVHTree.h"
#include "util/image/ImageBuffer.h"
#include "render/RayTracer.h"
#include "util/image/ImageUtil.h"
#include "material/DiffuseLight.h"
#include "light/BlueNoiseDiskLightZ.h"
#include "light/GridDiskLightZ.h"
#include "light/UniformDiskLightZ.h"

int main(int argc, char * argv[]) {
    auto * conf = new Configuration();
    conf->setDefaultWidth(1000)
        ->setDefaultHeight(1000)
        ->setDefaultMaxDepth(15)
        ->setDefaultSamplePerPixel(200)
        ->setDefaultThreadCount(5)
        ->setDefaultSampleOnLight(49)
        ->setDefaultSampler("blue")
        ->setDefaultOutputFile("sampling_rect.ppm")
        ->parseArgs(argc, argv);

    std::vector<Hittable *> objs;
    std::vector<Light *> lights;
    std::vector<Material *> mats;

    // 白色地板
    mats.push_back(new Lambertian({0.9, 0.9, 0.9}));
    objs.push_back(new Rectangle({100, -100, 0}, {0, 200, 0}, {-200, 0, 0}, mats.back()));

    // 白色浮板
    mats.push_back(new Lambertian({0.9, 0.9, 0.9}));
    objs.push_back(new Rectangle({-4, -2, 2}, {0, 4, 0}, {-4, 0, 0}, mats.back()));

    // 圆盘状光源
    mats.push_back(new DiffuseLight({10, 10, 10}));
    Light * diskLight = nullptr;
    if (conf->getSampler() == "grid") {
        diskLight = new GridDiskLightZ({-6, 0, 6.5}, 1.5, mats.back(), conf->getSampleOnLight());
    } else if (conf->getSampler() == "uniform") {
        diskLight = new UniformDiskLightZ({-6, 0, 6.5}, 1.5, mats.back(), conf->getSampleOnLight());
    } else if (conf->getSampler() == "blue") {
        diskLight = new BlueNoiseDiskLightZ({-6, 0, 6.5}, 1.5, mats.back(), conf->getSampleOnLight());
    } else {
        assert(false);
    }
    lights.push_back(diskLight);
    objs.push_back(lights.back());

    // 照相机位置
    Vector3d pos(13, 0, 5);
    // 视线方向
    Vector3d view(-1, 0, 0);
    // z 轴向上
    Vector3d up(0, 0, 1);
    // 视点到成像平面的距离
    float dist = 5;
    // 成像平面宽度
    float width = 4;
    // 成像平面高度
    float height = 4;
    // 照相机
    Camera * camera = new Perspective(pos, view, up, dist, width, height);

    // 构建 BVH 树
    Hittable * scene = new BVHTree(&objs);

    // 图片缓冲区
    auto * im = new ImageBuffer(conf->getWidth(), conf->getHeight());

    // 渲染
    RayTracer::render(camera, scene, lights, im, conf->getMaxDepth(), conf->getSamplePerPixel(),
                      conf->getThreadCount());

    // 矫正亮度
    ImageUtil::gammaCorrection(im, 2);

    // 保存图片
    ImageUtil::writePPM6(*im, conf->getOutputFile());

    // 可以不释放内存，程序结束了

    return 0;
}

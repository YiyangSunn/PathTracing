#include <iostream>
#include <vector>
#include <cmath>
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
#include "light/GridDiskLightZ.h"

void build_cuboid(std::vector<Material *> * mats, std::vector<Hittable *> * objs, const Vector3d & leftBottom,
                  const Vector3d & rightTop, float theta);

int main(int argc, char * argv[]) {
    Configuration * conf = (new Configuration())
            ->setDefaultWidth(800)
            ->setDefaultHeight(800)
            ->setDefaultMaxDepth(15)
            ->setDefaultSamplePerPixel(20)
            ->setDefaultThreadCount(5)
            ->setDefaultOutputFile("grid_sampling.ppm")
            ->parseArgs(argc, argv);

    std::vector<Hittable *> objs;
    std::vector<Light *> lights;
    std::vector<Material *> mats;

    // 白色地板
    mats.push_back(new Lambertian({0.9, 0.9, 0.9}));
    objs.push_back(new Rectangle({0, -5, 0}, {-10, 0, 0}, {0, 10, 0}, mats.back()));

    // 白色天花板
    mats.push_back(new Lambertian({0.9, 0.9, 0.9}));
    objs.push_back(new Rectangle({0, -5, 10}, {0, 10, 0}, {-10, 0, 0}, mats.back()));

    // 红色左墙
    mats.push_back(new Lambertian({0.9, 0, 0}));
    objs.push_back(new Rectangle({0, -5, 0}, {0, 0, 10}, {-10, 0, 0}, mats.back()));

    // 绿色右墙
    mats.push_back(new Lambertian({0, 0.9, 0}));
    objs.push_back(new Rectangle({0, 5, 0}, {-10, 0, 0}, {0, 0, 10}, mats.back()));

    // 白色后墙
    mats.push_back(new Lambertian({0.9, 0.9, 0.9}));
    objs.push_back(new Rectangle({-10, -5, 0}, {0, 0, 10}, {0, 10, 0}, mats.back()));

    // 圆盘状光源
    mats.push_back(new DiffuseLight({8, 8, 8}));
    lights.push_back(new GridDiskLightZ({-5, 0, 9.99}, 1.5, mats.back(), 0.05));
    objs.push_back(lights.back());

    // 左边长方体
    build_cuboid(&mats, &objs, {-8, -3.5, 0}, {-5, -0.5, 6}, 15.f / 180 * 3.14159f);

    // 右边长方体
    build_cuboid(&mats, &objs, {-5, 0, 0}, {-2, 3, 3}, -15.f / 180 * 3.14159f);

    // 照相机位置
    Vector3d pos(14, 0, 5);
    // 视线方向
    Vector3d view(-1, 0, 0);
    // z 轴向上
    Vector3d up(0, 0, 1);
    // 视点到成像平面的距离
    float dist = 5.5;
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

// 把向量 p 绕平行于 z 轴的轴 o 逆时针转 theta 角
Vector3d rotateZ(const Vector3d & p, const Vector3d & o, float theta) {
    Vector3d v = p - o;
    float cs = std::cos(theta);
    float si = std::sin(theta);
    return o + Vector3d(v[0] * cs - v[1] * si, v[0] * si + v[1] * cs, v[2]);
}

void build_cuboid(std::vector<Material *> * mats, std::vector<Hittable *> * objs, const Vector3d & leftBottom,
                  const Vector3d & rightTop, float theta) {
    Vector3d o = {(leftBottom[0] + rightTop[0]) / 2, (leftBottom[1] + rightTop[1]) / 2, 0};
    Vector3d p1 = rotateZ({rightTop[0], leftBottom[1], leftBottom[2]}, o, theta);
    Vector3d p2 = rotateZ({leftBottom[0], rightTop[1], leftBottom[2]}, o, theta);
    Vector3d p3 = rotateZ({leftBottom[0], leftBottom[1], rightTop[2]}, o, theta);
    Vector3d p4 = rotateZ({leftBottom[0], rightTop[1], rightTop[2]}, o, theta);
    Vector3d p5 = rotateZ({rightTop[0], leftBottom[1], rightTop[2]}, o, theta);
    Vector3d p6 = rotateZ({rightTop[0], rightTop[1], leftBottom[2]}, o ,theta);
    Vector3d c1 = rotateZ(leftBottom, o, theta);
    Vector3d c2 = rotateZ(rightTop, o, theta);
    Vector3d v1 = p1 - c1;
    Vector3d v2 = p2 - c1;
    Vector3d v3 = p3 - c1;
    Vector3d v4 = p4 - c2;
    Vector3d v5 = p5 - c2;
    Vector3d v6 = p6 - c2;
    mats->push_back(new Lambertian({0.8, 0.8, 0.8}));
    objs->push_back(new Rectangle(c1, v1, v3, mats->back()));
    objs->push_back(new Rectangle(c1, v3, v2, mats->back()));
    objs->push_back(new Rectangle(c1, v2, v1, mats->back()));
    objs->push_back(new Rectangle(c2, v6, v4, mats->back()));
    objs->push_back(new Rectangle(c2, v5, v6, mats->back()));
    objs->push_back(new Rectangle(c2, v4, v5, mats->back()));
}

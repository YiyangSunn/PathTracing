#include <unordered_map>
#include <cassert>
#include <iostream>
#include <cmath>
#include "light/BlueNoiseDiskLightZ.h"

BlueNoiseDiskLightZ::BlueNoiseDiskLightZ(const Vector3d & center, float radius, Material * material, int count)
    : DiskLightZ(center, radius, material) {
    // 计算最小距离
    auto minR = (float) (3.0 / std::sqrt(count * 1.5));
    // 预生成样本点
    prepareSamples(center, radius, minR);
}

Vector3d BlueNoiseDiskLightZ::getSample() {
    int idx = (int) (drand48() * (int) samples.size());
    return samples[idx];
}

float BlueNoiseDiskLightZ::getPdf() {
    float r = disk->getRadius();
    return 0.318309f / (r * r);
}

void BlueNoiseDiskLightZ::prepareSamples(const Vector3d & center, float radius, float minR) {
//    std::cout << "begin blue noise sampling...\n" << std::flush;
    float size = 2 * radius; // 正方形边长
    float ds = minR / 1.41421f; // 划分成网格后每个小正方形的边长
    int n = (int) (size / ds); // 每条边可以放多少个小正方形
    assert(n > 0 && n < 1000); // 检查 n 的范围，点不能太多
    std::vector<Vector3d> active; // 激活点集
    std::vector<Vector3d> output; // 输出点集
    float x = (float) drand48() * size; // 初始放入一个随机点
    float y = (float) drand48() * size;
    int i = (int) (x / ds);
    int j = (int) (y / ds);
    active.emplace_back(x, y, 0);
    output.emplace_back(x, y, 0);
    std::unordered_map<int, Vector3d> map; // 记录每个格子里的点坐标
    map[i * 1000 + j] = Vector3d(x, y, 0);
    while (!active.empty()) { // 至多取 count 个点
        int idx = (int) (drand48() * (float) active.size()); // 从激活队列中随机选一个点
        Vector3d p = active[idx];
        bool shouldEvict = true; // 是否要把 p 从激活点集中删除
        // 在半径 (minR, 2 * minR) 的圆环内随机取 30 个点
        for (int k = 0; k < 30; ++k) {
            float rr = (float) drand48() * minR + minR;
            auto theta = (float) (drand48() * 6.28319f);
            x = rr * std::cos(theta) + p[0];
            y = rr * std::sin(theta) + p[1];
            if (x < 0 || x > size || y < 0 || y > size) {
                continue;
            }
            i = (int) (x / ds);
            j = (int) (y / ds);
            // 检查这个点是否有效
            bool ok = true;
            for (int u = std::max(0, i - 2); u <= std::min(n, i + 2) && ok; ++u) {
                for (int v = std::max(0, j - 2); v <= std::min(n, j + 2); ++v) {
                    int key = u * 1000 + v;
                    if (map.count(key)) {
                        Vector3d d = map[key] - Vector3d(x, y, 0);
                        float dist_2 = d.dot(d);
                        if (dist_2 <= minR * minR) {
                            // 已经有一个点距离此位置小于minR
                            ok = false;
                            break;
                        }
                    }
                }
            }
            if (ok) {
                active.emplace_back(x, y, 0); // 放入激活点集
                output.emplace_back(x, y, 0); // 放入输出点集
                map[i * 1000 + j] = Vector3d(x, y, 0); // 记录在 map 里
                shouldEvict = false;
                break;
            }
        }
        if (shouldEvict) {
            // 从激活点集中删除该点，这里用最后一个点替换
            active[idx] = active.back();
            active.pop_back();
        }
    }
    // 筛选在圆盘内的点
    for (const Vector3d & v: output) {
        float rx = v[0] - radius, ry = v[1] - radius;
        if (rx * rx + ry * ry <= radius * radius) {
            samples.push_back(Vector3d(rx, ry, 0) + center);
        }
    }
//    std::cout << "sampling finished, writing to files...\n" << std::flush;
    // 输出所有采样点
    FILE * fp = fopen("blue_samples.txt", "w");
    fprintf(fp, "%f\n", size);
    for (const Vector3d & v: output) {
        fprintf(fp, "%f %f\n", v[0], v[1]);
    }
    fclose(fp);
    // 输出圆盘里的采样点
//    fp = fopen("samples_within_disk.txt", "w");
//    fprintf(fp, "%f\n", size);
//    for (const Vector3d & v: samples) {
//        Vector3d w = v - center;
//        fprintf(fp, "%f %f\n", w[0] + radius, w[1] + radius);
//    }
//    fclose(fp);
//    std::cout << "writing finished.\n" << std::flush;
}

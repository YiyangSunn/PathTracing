#ifndef SIMPLE_RAY_TRACER_IMAGETEXTURE_H
#define SIMPLE_RAY_TRACER_IMAGETEXTURE_H

#include "Texture.h"
#include "util/ImageUtil.h"
#include "util/ImageBuffer.h"

class ImageTexture: public Texture {

private:

    int width{};

    int height{};

    ImageBuffer * im{};

public:

    inline explicit ImageTexture(const std::string & filename, float gamma = 1.f / 2.2f) {
        im = ImageUtil::readPPM6(filename);
        ImageUtil::gammaCorrection(im, gamma);
        width = im->getWidth();
        height = im->getHeight();
    }

    Vector3f getValue(float u, float v, const Vector3f & p) override {
        // V 坐标自下而上
        v = 1 - v;
        float uf = u * width;
        float vf = v * height;
        int u1 = (int) uf;
        int v2 = (int) vf;
        // 计算插值比例
        float s = uf - u1;
        float t = vf - v2;
        // 取相邻 4 个点
        int u2 = u1 + 1, v1 = v2 + 1;
        if (u2 >= width) u2 = 0;
        if (v1 >= height) v1 = 0;
        // 双线性插值
        Vector3f c1 = ((*im)[v1][u2] - (*im)[v1][u1]) * s + (*im)[v1][u1];
        Vector3f c2 = ((*im)[v2][u2] - (*im)[v2][u1]) * s + (*im)[v2][u1];
        return (c1 - c2) * t + c2;
    }

    ~ImageTexture() override { delete im; }

};

#endif //SIMPLE_RAY_TRACER_IMAGETEXTURE_H

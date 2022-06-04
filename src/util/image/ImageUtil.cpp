#include <cmath>
#include "util/image/ImageUtil.h"

void ImageUtil::writePPM(const ImageBuffer & im, const std::string & filename, int type) {
    switch (type) {
        case 3:
            writePPM3(im, filename);
            break;
        case 6:
            writePPM6(im, filename);
            break;
        default:
            writePPM6(im, filename);
    }
}

void ImageUtil::writePPM6(const ImageBuffer & im, const std::string & filename) {
    FILE * fp = fopen(filename.c_str(), "wb");
    if (fp) {
        int width = im.getWidth();
        int height = im.getHeight();
        fprintf(fp, "P6\n%d %d\n%d\n", width, height, 255);
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                for (int k = 0; k < 3; ++k) {
                    float value = std::min(255.99f * im[i][j][k], 255.99f);
                    value = std::max(value, 0.01f);
                    fputc((unsigned char) value, fp);
                }
            }
        }
        fclose(fp);
    }
}

void ImageUtil::writePPM3(const ImageBuffer & im, const std::string & filename) {
    FILE * fp = fopen(filename.c_str(), "w");
    if (fp) {
        int width = im.getWidth();
        int height = im.getHeight();
        fprintf(fp, "P3\n%d %d\n%d\n", width, height, 255);
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                for (int k = 0; k < 3; ++k) {
                    float value = std::min(255.99f * im[i][j][k], 255.99f);
                    value = std::max(value, 0.01f);
                    fprintf(fp, "%d ", (int) value);
                }
                fputc('\n', fp);
            }
        }
        fclose(fp);
    }
}

void ImageUtil::gammaCorrection(ImageBuffer * im, float gamma) {
    int w = im->getWidth();
    int h = im->getHeight();
    float exp = 1.f / gamma;
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            for (int k = 0; k < 3; ++k) {
                float v = (*im)[i][j][k];
                (*im)[i][j][k] = powf(v, exp);
            }
        }
    }
}

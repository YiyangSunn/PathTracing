#include <cassert>
#include "util/image/ImageBuffer.h"
#include "util/image/ImageUtil.h"

int main() {
    int w = 10;
    int h = 5;
    ImageBuffer im(w, h);
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            for (int k = 0; k < 3; ++k) {
                im[i][j][k] = (float) drand48();
            }
        }
    }
    ImageBuffer buf(im);
    ImageUtil::gammaCorrection(&im, 0.5);
    float s = 0;
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            s += (buf[i][j] * buf[i][j] - im[i][j]).getLength();
        }
    }
    assert(s < 1e-3);

    return 0;
}

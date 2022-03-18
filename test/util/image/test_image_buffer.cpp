#include <cassert>
#include "util/image/ImageBuffer.h"
#include "test_helper.h"

int main() {
    ImageBuffer im(100, 200);
    assert(im.getHeight() == 200);
    assert(im.getWidth() == 100);
    im[2][3] = {100, 100, 100};
    assert_vector3d_equal(im[2][3], {100, 100, 100});

    ImageBuffer buf(im);
    float s = 0;
    for (int i = 0; i < im.getHeight(); ++i) {
        for (int j = 0; j < im.getWidth(); ++j) {
            s += (buf[i][j] - im[i][j]).getLength();
        }
    }
    assert(s < 1e-3);

    return 0;
}

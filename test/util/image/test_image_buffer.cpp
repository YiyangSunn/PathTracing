#include <cassert>
#include "util/image/ImageBuffer.h"
#include "test_helper.h"

int main() {
    ImageBuffer im(100, 200);
    assert(im.getHeight() == 200);
    assert(im.getWidth() == 100);
    im[2][3] = {100, 100, 100};
    assert_vector3d_equal(im[2][3], {100, 100, 100});
    return 0;
}

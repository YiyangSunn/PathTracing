#ifndef SIMPLE_RAY_TRACER_IMAGEUTIL_H
#define SIMPLE_RAY_TRACER_IMAGEUTIL_H

#include "ImageBuffer.h"

// static utility class that supports image manipulation
class ImageUtil {

public:

    // write the image to disk in .ppm format
    static void writePPM(const ImageBuffer & im, const std::string & filename, int type = 6);

    static void writePPM6(const ImageBuffer & im, const std::string & filename);

    static void writePPM3(const ImageBuffer & im, const std::string & filename);

    static void gammaCorrection(ImageBuffer * im, float gamma);

};

#endif //SIMPLE_RAY_TRACER_IMAGEUTIL_H

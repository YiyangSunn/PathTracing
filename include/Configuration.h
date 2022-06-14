#ifndef SIMPLERAYTRACER_CONFIGURATION_H
#define SIMPLERAYTRACER_CONFIGURATION_H

#include <string>
#include <cfloat>

class Configuration {

private:

    // width of the generated image
    int width{50};

    // height of the generated image
    int height{50};

    // number of threads to use
    int threadCount{1};

    // spp
    int samplePerPixel{50};

    // maximum depth of recursion
    int maxDepth{10};

    // which integrator to use
    std::string integrator{"path"};

    // clamp threshold
    float clampThresh{FLT_MAX};

    // output file name
    std::string outputFile{"output.ppm"};

public:

    // pass in the command line arguments from main
    Configuration() = default;

    Configuration * setDefaultWidth(int w);

    Configuration * setDefaultHeight(int height);

    Configuration * setDefaultThreadCount(int t);

    Configuration * setDefaultSamplePerPixel(int s);

    Configuration * setDefaultMaxDepth(int d);

    Configuration * setDefaultIntegrator(std::string i);

    Configuration * setDefaultClampThresh(float clampThresh);

    Configuration * setDefaultOutputFile(const std::string & o);

    int getWidth() const;

    int getHeight() const;

    int getThreadCount() const;

    int getSamplePerPixel() const;

    int getMaxDepth() const;

    std::string getIntegrator() const;

    float getClampThresh() const;

    std::string getOutputFile() const;

    Configuration * parseArgs(int argc, char * argv[]);

    virtual ~Configuration() = default;

};

#endif //SIMPLERAYTRACER_CONFIGURATION_H

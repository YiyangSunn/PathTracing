#ifndef SIMPLERAYTRACER_CONFIGURATION_H
#define SIMPLERAYTRACER_CONFIGURATION_H

#include <string>

class Configuration {

private:

    // width of the generated image
    int width{50};

    // height of the generated image
    int height{50};

    // number of threads to use
    int threadCount{1};

    int samplePerPixel{50};

    // maximum depth of recursion
    int maxDepth{10};

    // output file name
    std::string outputFile{"output.ppm"};

public:

    // pass in the command line arguments from main
    Configuration() = default;

    Configuration * setDefaultWidth(int width);

    Configuration * setDefaultHeight(int height);

    Configuration * setDefaultThreadCount(int threadCount);

    Configuration * setDefaultSamplePerPixel(int samplePerPixel);

    Configuration * setDefaultMaxDepth(int maxDepth);

    Configuration * setDefaultOutputFile(const std::string & outputFile);

    int getWidth() const;

    int getHeight() const;

    int getThreadCount() const;

    int getSamplePerPixel() const;

    int getMaxDepth() const;

    std::string getOutputFile() const;

    Configuration * parseArgs(int argc, char * argv[]);

    virtual ~Configuration() = default;

};

std::ostream & operator<<(std::ostream & out, const Configuration & conf);

#endif //SIMPLERAYTRACER_CONFIGURATION_H

#include <getopt.h>
#include <iostream>
#include <utility>
#include "Configuration.h"

Configuration * Configuration::setDefaultHeight(int height) {
    this->height = height;
    return this;
}

Configuration * Configuration::setDefaultWidth(int width) {
    this->width = width;
    return this;
}


Configuration * Configuration::setDefaultMaxDepth(int maxDepth) {
    this->maxDepth = maxDepth;
    return this;
}

Configuration * Configuration::setDefaultSamplePerPixel(int samplePerPixel) {
    this->samplePerPixel = samplePerPixel;
    return this;
}

Configuration * Configuration::setDefaultThreadCount(int threadCount) {
    this->threadCount = threadCount;
    return this;
}

Configuration * Configuration::setDefaultSampleOnLight(int sampleOnLight) {
    this->sampleOnLight = sampleOnLight;
    return this;
}

Configuration * Configuration::setDefaultSampler(std::string sampler) {
    this->sampler = std::move(sampler);
    return this;
}

Configuration * Configuration::setDefaultOutputFile(const std::string & outputFile) {
    this->outputFile = outputFile;
    return this;
}

int Configuration::getWidth() const {
    return width;
}

int Configuration::getHeight() const {
    return height;
}

int Configuration::getThreadCount() const {
    return threadCount;
}

int Configuration::getSamplePerPixel() const {
    return samplePerPixel;
}

int Configuration::getMaxDepth() const {
    return maxDepth;
}

int Configuration::getSampleOnLight() const {
    return sampleOnLight;
}

std::string Configuration::getSampler() const {
    return sampler;
}

std::string Configuration::getOutputFile() const {
    return outputFile;
}

Configuration * Configuration::parseArgs(int argc, char ** argv) {
    // get input args
    const char * opts = ":w:h:s:t:d:o:l:p:";
    int c = 0;
    while ((c = getopt(argc, argv, opts)) != EOF) {
        switch (c) {
            case 'w':
                width = std::stoi(optarg);
                break;
            case 'h':
                height = std::stoi(optarg);
                break;
            case 's':
                samplePerPixel = std::stoi(optarg);
                break;
            case 't':
                threadCount = std::stoi(optarg);
                break;
            case 'd':
                maxDepth = std::stoi(optarg);
                break;
            case 'l':
                sampleOnLight = std::stoi(optarg);
                break;
            case 'p':
                sampler = optarg;
                if (sampler != "grid" && sampler != "uniform" && sampler != "blue") {
                    std::cout << "Error: unknown sampler specified: " << sampler << std::endl;
                    exit(-1);
                }
                break;
            case 'o':
                outputFile = optarg;
                break;
            default:
                break;
        }
    }
    return this;
}

std::ostream & operator<<(std::ostream & out, const Configuration & conf) {
    out << "Configuration{" << std::endl
        << "    width: " << conf.getWidth() << std::endl
        << "    height: " << conf.getHeight() << std::endl
        << "    threadCount: " << conf.getThreadCount() << std::endl
        << "    samplePerPixel: " << conf.getSamplePerPixel() << std::endl
        << "    maxDepth: " << conf.getMaxDepth() << std::endl
        << "    sampleOnLight: " << conf.getSampleOnLight() << std::endl
        << "    sampler: " << conf.getSampler() << std::endl
        << "    outputFile: " << conf.getOutputFile() << std::endl
        << "}" << std::endl;
    return out;
}

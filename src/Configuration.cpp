#include <getopt.h>
#include <iostream>
#include <utility>
#include "Configuration.h"

Configuration * Configuration::setDefaultHeight(int h) {
    this->height = h;
    return this;
}

Configuration * Configuration::setDefaultWidth(int w) {
    this->width = w;
    return this;
}


Configuration * Configuration::setDefaultMaxDepth(int d) {
    this->maxDepth = d;
    return this;
}

Configuration * Configuration::setDefaultSamplePerPixel(int s) {
    this->samplePerPixel = s;
    return this;
}

Configuration * Configuration::setDefaultThreadCount(int t) {
    this->threadCount = t;
    return this;
}

Configuration * Configuration::setDefaultIntegrator(std::string i) {
    this->integrator = std::move(i);
    return this;
}

Configuration * Configuration::setDefaultOutputFile(const std::string & o) {
    this->outputFile = o;
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

std::string Configuration::getIntegrator() const {
    return integrator;
}

std::string Configuration::getOutputFile() const {
    return outputFile;
}

Configuration * Configuration::parseArgs(int argc, char ** argv) {
    // get input args
    const char * opts = ":w:h:s:t:d:o:i:";
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
            case 'i':
                integrator = optarg;
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

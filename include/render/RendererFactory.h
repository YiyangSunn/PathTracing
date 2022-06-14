#ifndef SIMPLE_RAY_TRACER_RENDERERFACTORY_H
#define SIMPLE_RAY_TRACER_RENDERERFACTORY_H

#include "Renderer.h"
#include "PathTracer.h"
#include "LightSampler.h"
#include "BRDFSampler.h"
#include "MISampler.h"
#include "Configuration.h"
#include <stdexcept>

class RendererFactory {

public:

    static Renderer * getInstance(const Configuration & conf) {
        int spp = conf.getSamplePerPixel();
        int maxDepth = conf.getMaxDepth();
        int nThreads = conf.getThreadCount();
        float clampThresh = conf.getClampThresh();
        std::string integrator = conf.getIntegrator();

        if (integrator == "path") {
            return new PathTracer(spp, maxDepth, nThreads, clampThresh);
        } else if (integrator == "light") {
            return new LightSampler(spp, nThreads);
        } else if (integrator == "brdf") {
            return new BRDFSampler(spp, nThreads);
        } else if (integrator == "mis") {
            return new MISampler(spp, nThreads);
        }

        throw std::logic_error("unknown integrator: " + integrator);
    }

};

#endif //SIMPLE_RAY_TRACER_RENDERERFACTORY_H

#ifndef SIMPLE_RAY_TRACER_RANDOM_H
#define SIMPLE_RAY_TRACER_RANDOM_H

#include <random>

class Random {

public:

    inline int randInt(int a, int b) {
        thread_local std::random_device randDev;
        thread_local std::default_random_engine randEng((randDev()));
        thread_local std::uniform_int_distribution<int> distribution;
        using param_type = std::uniform_int_distribution<int>::param_type;
        return distribution(randEng, param_type{a, b - 1});
    }

    inline float randFloat(float a, float b) {
        thread_local std::random_device randDev;
        thread_local std::default_random_engine randEng((randDev()));
        thread_local std::uniform_real_distribution<float> distribution;
        using param_type = std::uniform_real_distribution<float>::param_type;
        return distribution(randEng, param_type{a, b});
    }

};

#endif //SIMPLE_RAY_TRACER_RANDOM_H

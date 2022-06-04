#include "util/math/Random.h"

int Random::randInt(int a, int b) {
    thread_local std::random_device randDev;
    thread_local std::default_random_engine randEng((randDev()));
//    thread_local std::default_random_engine randEng(0);
    thread_local std::uniform_int_distribution<int> distribution;
    using param_type = std::uniform_int_distribution<int>::param_type;
    return distribution(randEng, param_type{a, b - 1});
}

float Random::randFloat(float a, float b) {
    thread_local std::random_device randDev;
    thread_local std::default_random_engine randEng((randDev()));
//    thread_local std::default_random_engine randEng(0);
    thread_local std::uniform_real_distribution<float> distribution;
    using param_type = std::uniform_real_distribution<float>::param_type;
    return distribution(randEng, param_type{a, b});
}

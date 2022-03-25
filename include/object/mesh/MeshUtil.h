#ifndef SIMPLE_RAY_TRACER_MESHUTIL_H
#define SIMPLE_RAY_TRACER_MESHUTIL_H

#include <vector>

#include "object/Hittable.h"

// utility class for manipulating mesh models
class MeshUtil {

public:

    // load only the model from the specified .obj file, materials and other non-mesh shapes
    // are all omitted
    static bool loadPureModelFromObj(const std::string & filename, std::vector<Hittable *> * objs, Material * mat);

private:


public:

    MeshUtil() = default;

    virtual ~MeshUtil() = default;

};

#endif //SIMPLE_RAY_TRACER_MESHUTIL_H

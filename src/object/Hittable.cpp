#include "object/Hittable.h"

Hittable::Hittable(Material * material) {
    this->material = material;
}

Material * Hittable::getMaterial() {
    return material;
}

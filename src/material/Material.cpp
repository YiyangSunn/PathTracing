#include "material/Material.h"

bool Material::isEmitting() {
    return false;
}

Vector3d Material::emit() {
    return {0, 0, 0};
}

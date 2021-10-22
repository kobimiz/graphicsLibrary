#ifndef GEOMETRY3D_H
#define GEOMETRY3D_H

// TODO abstract common dependencies of geometry and geometry3d like shader
#include "../internal/shader.h"
#include "../internal/cube.h"

namespace Geometry {

    void initGeometry3d();

    void destroyGeometry3d();

}; // namespace Geometry

#endif
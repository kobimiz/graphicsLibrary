#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "../internal/character.h"
#include "../internal/circle.h"
#include "../internal/color.h"
#include "../internal/line.h"
#include "../internal/nonInclusiveRange.h"
#include "../internal/point.h"
#include "../internal/rectangle.h"
#include "../internal/shader.h"
#include "../internal/utility.h"

namespace Geometry {

void initGeometry();

void destroyGeometry();

}; // namespace Geometry

#endif
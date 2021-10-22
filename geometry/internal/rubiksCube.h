#ifndef RUBKIS_CUBE_H
#define RUBKIS_CUBE_H

#include "../internal/cube.h"

#include <map>

class RubkisCube : public Geometry::Cube {
private:
    // std::map<int, Texture>
public:
    void draw() override;
};

#endif
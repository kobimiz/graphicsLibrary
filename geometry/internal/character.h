#ifndef CHARACTER_H
#define CHARACTER_H

#include "ft2build.h"
#include FT_FREETYPE_H

#include "glm/glm.hpp"

namespace Geometry {

struct Character {
    unsigned int textureId; // id handle
    glm::ivec2 size;        // size of glyph
    glm::ivec2 bearing;     // offset from baseline to left/top of glyph
    FT_Pos advance;   // offset to advance to next glyph
};

}; // namespace Geometry

#endif
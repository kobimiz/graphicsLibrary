#ifndef UTILITY_H
#define UTILITY_H

#include <map>
#include <string>
#include "glm/glm.hpp"

#include "character.h"

class GLFWwindow;

namespace Geometry {

class Shader;

namespace Utility {
    extern std::map<char, Character> characters;
    extern unsigned int textVao, textVbo;
	extern Shader* textShader;

    void initFreeType();
    void initGLEW(bool enableDebug);
    void initGLFW();
    void setGLFWCallbacks(GLFWwindow* window);
    void renderText(std::string text, float x, float y, float scale, glm::vec3 color);
}

}; // namespace Geometry

#endif
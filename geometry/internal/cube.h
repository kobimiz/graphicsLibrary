#ifndef CUBE_H
#define CUBE_H

namespace Geometry {

class Shader;

class Cube {
protected:
    static unsigned int cubeVao;
    static unsigned int cubeVbo;
    static Shader* shaderProgram;

public:
    static void init();
    static void destroy();

    virtual void draw();
};

}; // namespace Geometry

#endif
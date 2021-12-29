#ifndef RUBKIS_CUBE_H
#define RUBKIS_CUBE_H

#include "../internal/cube.h"

#include <GLFW/glfw3.h>

#include <map>

namespace Geometry {
class Shader;
};

#define RC_UP     0
#define RC_RIGHT  1
#define RC_FRONT  2
#define RC_LEFT   3
#define RC_DOWN   4
#define RC_BACK   5

#define RC_RED    0
#define RC_GREEN  1
#define RC_BLUE   2
#define RC_WHITE  3
#define RC_ORANGE 4
#define RC_YELLOW 5

class RubiksCube : public Geometry::Cube {
private:
    // std::map<int, Texture>
    static Geometry::Shader* rubiksCubeShader;
    static unsigned int texture;


    int faceColors[6];

    void fillSquareCoords(float* toFill, int width, int height, int x, int y);
    int getFaceOffset(int face);
    unsigned int texCoordsBuffer;
public:
    GLFWwindow* w;
    
    RubiksCube(GLFWwindow* w);
    ~RubiksCube();

    static void init();
    static void destroy();

    void draw() override;

    void colorFace(int face, int color);
};

#endif
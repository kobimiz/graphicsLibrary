#ifndef LINE_H
#define LINE_H

#include "point.h"

namespace Geometry {
    
class Shader;

class Line {
private:
    static unsigned int vao;
    static unsigned int vbo;
    static Shader* shader;

    Point p1, p2;
    float color[3];
    int thickness;
public:
    // TODO change color to Color class for easier usage of this constructor
    Line();
    Line(const Point&& p1, const Point&& p2, const float color[3], int thickness);
    void draw();
    void setStart(float x, float y);
    void setEnd  (float x, float y);

    static void init();
    static void destroy();
    static float toRadians(float deg);
};

}; // namespace Geometry

#endif
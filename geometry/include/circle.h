#ifndef CIRCLE_H
#define CIRCLE_H

namespace Geometry {

class Shader;
class Color;

class Circle {

private:
    int x, y;
    int radius;
    bool isFilled;
    float thickness;
    float color[];

    static Shader* shader;
    static unsigned int vao;
    static unsigned int vbo;
public:
    Circle(int x, int y, int radius, Color& color, float thickness, bool isFilled);
    Circle(int x, int y, int radius, const Color&& color, float thickness, bool isFilled);

    void draw();

    static void init();
    static void destroy();
};

}; // namespace Geometry

#endif
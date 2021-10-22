#define GLEW_STATIC
#include "GL/glew.h"

#include <utility>

#include "geometry.h"

#include "matrix.h"
#include "vec3.h"

unsigned int Geometry::Rectangle::recVao;
unsigned int Geometry::Rectangle::recVbo;
int Geometry::Rectangle::screenWidth = 1000;
int Geometry::Rectangle::screenHeight = 800;
Geometry::Shader* Geometry::Rectangle::shaderProgram;

namespace Geometry {

void Rectangle::init() {
    float recVertices[] = {
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f
    };

    glGenVertexArrays(1, &Rectangle::recVao);
    glGenBuffers(1, &Rectangle::recVbo);
    glBindVertexArray(Rectangle::recVao);
    glBindBuffer(GL_ARRAY_BUFFER, recVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(recVertices), recVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0 * sizeof(float)));
    glEnableVertexAttribArray(0);
    Rectangle::shaderProgram = new Shader("rectangle.vert", "rectangle.frag");
}
Point Rectangle::openglToGlfwCoords(const Point& p) {
    return Point(
        Rectangle::screenWidth * (p.x + 1) / 2.0f,
        Rectangle::screenHeight * (1 - p.y) / 2.0f
    );
}
Point Rectangle::glfwToOpenglCoords(const Point& p) {
    return Point(
        2 * p.x / Rectangle::screenWidth - 1.0f,
        1.0f - 2 * p.y / Rectangle::screenHeight
    );
}
Point Rectangle::openglToGlfwCoords(const Point&& p) {
    return Point(
        Rectangle::screenWidth * (p.x + 1) / 2.0f,
        Rectangle::screenHeight * (1 - p.y) / 2.0f
    );
}
Point Rectangle::glfwToOpenglCoords(const Point&& p) {
    return Point(
        2 * p.x / Rectangle::screenWidth - 1.0f,
        1.0f - 2 * p.y / Rectangle::screenHeight
    );
}
void Rectangle::destroy() {
    delete Rectangle::shaderProgram;
    glDeleteVertexArrays(1, &Rectangle::recVao);
    glDeleteBuffers(1, &Rectangle::recVbo);
}

Rectangle::Rectangle() : topLeft({-1.0f, 1.0f}), color(0.0f, 0.0f, 0.0f), width(10), height(10), borderWidth(0.0f) { };

Rectangle::Rectangle(Point topLeft, int width, int height, float borderWidth, Color&& color)
:topLeft(Rectangle::glfwToOpenglCoords(topLeft)), color(color), width(width), height(height), borderWidth(borderWidth) { }

Rectangle::Rectangle(float x, float y, int width, int height, float borderWidth, Color&& color)
:Rectangle(Rectangle::glfwToOpenglCoords(Point(x,y)), width, height, borderWidth, std::move(color)) { }

Rectangle::Rectangle(const Rectangle& another)
:topLeft(another.topLeft), color(another.color), width(another.width), height(another.height), borderWidth(another.borderWidth) { }

Rectangle::~Rectangle() { }

void Rectangle::draw() {
    Rectangle::shaderProgram->use();
    glBindVertexArray(Rectangle::recVao);
    // TODO switch to matrix class
    float scaleX = 2.0f * this->width/Rectangle::screenWidth; 
    float scaleY = 2.0f * this->height/Rectangle::screenHeight;
    Vec3 pivot(topLeft.x, topLeft.y, 0.0f);
    Matrix translate(Matrix::translate(pivot + Vec3(0.5f, -0.5f, 0.0f)));
    Matrix scale(Matrix::scale(scaleX, scaleY, 1.0f, pivot));
    Matrix trans(scale * translate);

    Rectangle::shaderProgram->setMat4("trans", trans.data);
    Rectangle::shaderProgram->setVec3("color", this->color.rgb);
    
    // I AM HERE
    if (borderWidth != 0.0f) {
        glEnable(GL_STENCIL_TEST);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        glStencilFunc(GL_ALWAYS, 1, 0xff);
        glStencilMask(0xff);
    }
    glDrawArrays(GL_TRIANGLES, 0, 6);
    if (borderWidth != 0.0f) {
        glStencilFunc(GL_NOTEQUAL, 1, 0xff);
        glStencilMask(0x00);
        // draw border
        // I AM HERE
        float color[3] = { 1.0f, 1.0f, 1.0f };
        Rectangle::shaderProgram->setVec3("color", color);
        Point offset(1.0f * width / Rectangle::screenWidth, -1.0f * height / Rectangle::screenHeight);
        Matrix trans2(Matrix::scale(1.0f + (float) borderWidth / width, 1.0f + (float) borderWidth / height, 1.0f, pivot + Vec3(offset.x, offset.y, 0.0f)) * trans);
        Rectangle::shaderProgram->setMat4("trans", trans2.data);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glDisable(GL_STENCIL_TEST);
        // apparantly glClear of stencil buffer uses the stencil mask
        glStencilMask(0xff);
        glStencilFunc(GL_ALWAYS, 1, 0xff);
    }
}
bool Rectangle::isInRange(float x, float y) {
    // TODO: worry about screen resize!
    Point mappedTopLeft = Rectangle::openglToGlfwCoords(this->topLeft);
    return (mappedTopLeft.x <= x && x <= mappedTopLeft.x + this->width) &&
            (mappedTopLeft.y <= y && y <= mappedTopLeft.y + this->height);
}
void Rectangle::mouseIn() {
    color = (color + 0.1f) * 0.3f;
}
void Rectangle::mouseOut() {
    color = (color * (1.0f / 0.3f)) + -0.1f;
}

bool Rectangle::doIntersectX(const Rectangle& another) {
    NonInclusiveRange thisX{this->topLeft.x, this->topLeft.x + this->width};
    NonInclusiveRange anotherX{another.topLeft.x, another.topLeft.x + another.width};
    return thisX.doIntersect(anotherX);
}
bool Rectangle::doIntersectY(const Rectangle& another) {
    NonInclusiveRange thisY{this->topLeft.y - 2 * (float) this->height / Rectangle::screenHeight, this->topLeft.y};
    NonInclusiveRange anotherY{another.topLeft.y - 2 * (float) another.height / Rectangle::screenHeight, another.topLeft.y};
    return thisY.doIntersect(anotherY);
}

bool Rectangle::doIntersect(const Rectangle& another) {
    return doIntersectX(another) && doIntersectY(another);
}

// NOTE same calculation is performed in Rectangle::openglToGlfwCoords
// and in Rectangle::glfwToOpenglCoords, consider abstracting

void Rectangle::setX(float x) {
    topLeft.x = 2 * x / Rectangle::screenWidth - 1.0f;
}

void Rectangle::setY(float y) {
    topLeft.y = 1.0f - 2 * y / Rectangle::screenHeight;
}

float Rectangle::getX() {
    return Rectangle::screenWidth * (topLeft.x + 1) / 2.0f;
}

float Rectangle::getY() {
    return Rectangle::screenHeight * (1 - topLeft.y) / 2.0f;
}

void Rectangle::setXY(float x, float y) {
    setX(x);
    setY(y);
}
void Rectangle::setXY(const Point& p) {
    setX(p.x);
    setY(p.y);
}
void Rectangle::setXY(const Point&& p) {
    setX(p.x);
    setY(p.y);
}
Point Rectangle::getXY() {
    return Rectangle::openglToGlfwCoords(topLeft);
}

}; // namespace Geometry
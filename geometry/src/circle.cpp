#include "geometry.h"
#include "GL/glew.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace Geometry {

Shader* Circle::shader;
unsigned int Circle::vao;
unsigned int Circle::vbo;

Circle::Circle(int x, int y, int radius, Color& color, float thickness, bool isFilled) {
	this->x = x;
	this->y = y;
	this->radius = radius;
	this->isFilled = isFilled;
	this->thickness = thickness;
    this->color[0] = color.rgb[0];
    this->color[1] = color.rgb[1];
    this->color[2] = color.rgb[2];
}
Circle::Circle(int x, int y, int radius, const Color&& color, float thickness, bool isFilled) {
	this->x = x;
	this->y = y;
	this->radius = radius;
	this->isFilled = isFilled;
	this->thickness = thickness;
    this->color[0] = color.rgb[0];
    this->color[1] = color.rgb[1];
    this->color[2] = color.rgb[2];
}
#include <GLFW/glfw3.h>

void Circle::draw() {
    Point openglCoords(Rectangle::glfwToOpenglCoords(Point(x,y)));
    float scaleX = 2.0f * radius / Rectangle::screenWidth;
    float scaleY = 2.0f * radius / Rectangle::screenHeight;

    float translateX = (2.0f * x) / Rectangle::screenWidth - 1.0f;
    float translateY = (2.0f * y) / Rectangle::screenHeight - 1.0f;

    float trans2[] = {
        scaleX, 0.0f  , 0.0f, translateX,
        0.0f  , scaleY, 0.0f, translateY,
        0.0f  , 0.0f  , 1.0f, 0.0f,
        0.0f  , 0.0f  , 0.0f, 1.0f
    };

    glm::mat4 trans = glm::scale(glm::mat4(1.0f), glm::vec3(scaleX, scaleY, 1.0f));
    // I AM HERE: to learn how projection works
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(translateX, translateY, 0.0f));
    translate = glm::transpose(translate);

    trans = trans * translate;

	glBindVertexArray(Circle::vao);
    Circle::shader->use();
    Circle::shader->setMat4("trans", glm::value_ptr(trans));
    Circle::shader->setVec3("color", color);
    // translate to bottom left, look at cricle.frag for explanation
    float center[] = { (float)x, (float)y };
    Circle::shader->setVec2("center", center);
    Circle::shader->setInt("radius", radius);
    Circle::shader->setBool("isFilled", isFilled);
    Circle::shader->setFloat("thickness", thickness);

    glDrawArrays(GL_TRIANGLES, 0, 6);  
}

void Circle::init() {
    float recVertices[] = {
        -1.0f, -1.0f,  0.5f,
         1.0f, -1.0f,  0.5f,
         1.0f,  1.0f,  0.5f,
         1.0f,  1.0f,  0.5f,
        -1.0f,  1.0f,  0.5f,
        -1.0f, -1.0f,  0.5f
    };
    glGenVertexArrays(1, &Circle::vao);
    glGenBuffers(1, &Circle::vbo);

    glBindVertexArray(Circle::vao);
    glBindBuffer(GL_ARRAY_BUFFER, Circle::vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(recVertices), recVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    shader = new Shader("circle.vert", "circle.frag");
}

void Circle::destroy() {
    delete Circle::shader;
    glDeleteVertexArrays(1, &Circle::vao);
    glDeleteBuffers(1, &Circle::vbo);
}

}; // namespace Geometry
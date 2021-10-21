#include <cmath>

#include "line.h"
#include "rectangle.h"
#include "circle.h"
#include "shader.h"

#include "matrix.h"
#include "vec3.h"
#include "GL/glew.h"

#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

unsigned int Geometry::Line::vao;
unsigned int Geometry::Line::vbo;
Geometry::Shader* Geometry::Line::shader;

namespace Geometry {

Line::Line() : p1(0.0f, 0.0f), p2(0.0f, 0.0f) {
	this->color[0] = 0.0f;
	this->color[1] = 0.0f;
	this->color[2] = 0.0f;
	this->thickness = 0;
}

Line::Line(const Point&& p1, const Point&& p2, const float color[3], int thickness)
	: p1(Rectangle::glfwToOpenglCoords(p1)), p2(Rectangle::glfwToOpenglCoords(p2)) {
	this->color[0] = color[0];
	this->color[1] = color[1];
	this->color[2] = color[2];
	this->thickness = thickness;
	// TODO take arguments as points, but store actual variables as length and angle. make length and angle constructor (and starting point) ?
}

float angle(Point& p1, Point& p2) {
	Point v1(p2.x - p1.x, p2.y - p1.y);
	Point v2(1.0f, 0.0f);
	// second line is x axis, which will be represented by the vector (1,0)
	float dotProduct = v1.x * v2.x + v1.y * v2.y;
	float lenV1 = sqrt(v1.x * v1.x + v1.y * v1.y);
	float lenV2 = sqrt(v2.x * v2.x + v2.y * v2.y);
	float res = acos(dotProduct / (lenV1 * lenV2));
	
	float dx = v2.x - v1.x;
	float dy = v2.y - v1.y;
	if ((dx < 0 && dy > 0) || (dx > 0 && dy < 0))
		res = 3.14159f - res;
	return res;
}
void Line::draw() {
	// TODO think about rotation and streching matrix and using one fixed vbo
	glBindVertexArray(Line::vao);
	shader->use();
	glLineWidth(thickness);
	glEnable(GL_LINE_SMOOTH);
	// glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); // TODO consider this. if so, disable this afterwards
	shader->setVec3("color", color);
	// first scale, then translate
	float scaleBy = std::abs(p2.y - p1.y) / (2.0f * sqrt(2));
	float pi = 3.14159f;
	Matrix scale(Matrix::scale(scaleBy, scaleBy, 1.0f, Vec3(p1.x, p1.y, 0.0f)));
	Matrix translate(Matrix::translate(Vec3(p1.x + 1.0f, p1.y + 1.0f, 0.0f)));
	Matrix matrix(scale * translate);
	float deg = -angle(p1, p2) - 3.14159f / 4.0f; // initial angle
	Matrix rotate(Matrix::rotate(deg, Vec3(p1.x, p1.y, 0.0f)));
	Matrix trans(rotate * matrix);

	shader->setMat4("trans", trans.data);
	glDrawArrays(GL_LINES, 0, 2);

	glDisable(GL_LINE_SMOOTH);
}
void Line::setStart(float x, float y) {
	this->p1 = Rectangle::glfwToOpenglCoords(Point(x,y));
}
void Line::setEnd(float x, float y) {
	this->p2 = Rectangle::glfwToOpenglCoords(Point(x,y));
}

// TODO make sure init isnt called twice or nullify effect. same for other init funcs
void Line::init() {
    Line::shader = new Shader("line.vert", "line.frag");

	glGenVertexArrays(1, &Line::vao);
	glGenBuffers(1, &Line::vbo);

	glBindVertexArray(Line::vao);
	glBindBuffer(GL_ARRAY_BUFFER, Line::vbo);

	float linedata[] = {
		-1.0f, -1.0f,
		 1.0f,  1.0f
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof (linedata), linedata, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)(0 * sizeof(float)));
	glEnableVertexAttribArray(0);
}
void Line::destroy() {
	delete Line::shader;
	glDeleteVertexArrays(1, &Line::vao);
    glDeleteBuffers(1, &Line::vbo);
}
float Line::toRadians(float deg) {
	return 180.0f * deg / 3.14159f;
}

}; // namespace Geometry
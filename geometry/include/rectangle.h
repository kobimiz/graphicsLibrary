#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "point.h"
#include "color.h"

namespace Geometry {

class Shader;

class Rectangle {
private:
	static unsigned int recVao;
	static unsigned int recVbo;
	static Shader* shaderProgram;

	Point topLeft;
public:
	Color color;
	int width;
	int height;
	// 0 means no border
	float borderWidth;


	static int screenWidth;
	static int screenHeight;

	static void init();
	static Point glfwToOpenglCoords(const Point& p);
	static Point openglToGlfwCoords(const Point& p);
	static Point glfwToOpenglCoords(const Point&& p);
	static Point openglToGlfwCoords(const Point&& p);
	static void destroy();

	Rectangle();
	Rectangle(Point topLeft   , int width, int height, float borderWidth = 0.0f, Color&& color = Color(0.9f,0.9f,0.9f));
	Rectangle(float x, float y, int width, int height, float borderWidth = 0.0f, Color&& color = Color(0.9f,0.9f,0.9f));
	Rectangle(const Rectangle& another);
	~Rectangle();

	void draw();
	void mouseIn();
	void mouseOut();
	bool isInRange(float x, float y);
	bool doIntersectX(const Rectangle& another);
	bool doIntersectY(const Rectangle& another);
	bool doIntersect(const Rectangle& another);

	float getX();
	float getY();
	void setX(float x);
	void setY(float y);
	void setXY(float x, float y);
	void setXY(const Point& p);
	void setXY(const Point&& p);

	Point getXY();
};

}; // namespace Geometry

#endif
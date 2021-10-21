#define GLEW_STATIC
#include "glew.h"
#include "GLFW/glfw3.h"
#include "ft2build.h"
#include FT_FREETYPE_H
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "tinyxml2.h"

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

#include "geometry.h"
#include "guiElements.h"
#include "glfwHandlers.h"

GuiElements::Window* w;

void reParse(std::string&& docPath) {
	GuiElements::Element::mouseIsIn = nullptr;
	GuiElements::Input::active = nullptr;
	GuiElements::Input::active = nullptr;
	w->deleteChildren();
	w->fromDoc(std::move(docPath));
}

void reParseClick(GuiElements::Element* elem, Event* e){
	std::cout << "reparsing\n";

	reParse("document.xml");
	w->body->findById("helloContainer")->eventListeners.addEventListener("click", reParseClick);
}

int main(int argc, const char** args) {
	Geometry::Utility::initGLFW();
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

	GLFWwindow* window = glfwCreateWindow(Geometry::Rectangle::screenWidth, Geometry::Rectangle::screenHeight, "Graphics library", NULL, NULL);
	glfwMakeContextCurrent(window);

    glfwSetWindowPos(window, 550 + 1900, 100);

	Geometry::Utility::initGLEW();
	int flags;
	
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(handlers::glDebugOutput, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}

	glfwSetKeyCallback(window, handlers::key_callback);
	glfwSetCursorPosCallback(window, handlers::cursorPositionCallback);
	glfwSetMouseButtonCallback(window, handlers::mouseButtonCallback);
	glfwSetFramebufferSizeCallback(window, handlers::window_resize_callback);
	glfwSetCharCallback(window, handlers::character_callback);
	// TODO find a better solution
	handlers::standardCursor = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
	handlers::handCursor = glfwCreateStandardCursor(GLFW_HAND_CURSOR);

	glfwSetCursor(window, handlers::standardCursor);
	glViewport(0, 0, Geometry::Rectangle::screenWidth, Geometry::Rectangle::screenHeight);

	Geometry::Rectangle::init();
	Geometry::Line::init();
	GuiElements::LineBreak::init();
	Geometry::Circle::init();
	Geometry::Utility::initFreeType();
	// finished init
	
	w = new GuiElements::Window();
	glfwSetWindowUserPointer(window, w);
	w->fromDoc("document.xml");

	// Line l(Point(-1.0f,0.0f), Point(1.0f,0.0f), color, 2);
	// Circle c(100.0f, 100.0f, 3, Color(0.42f, 0.2f, 0.8f), 3.0f, true);
	// handlers::cb = new Checkbox(Point(300.0f,640.0f),20.0f,20.0f,false);
	
	w->body->findById("helloContainer")->eventListeners.addEventListener("click", reParseClick);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		// TODO change coord system of text from bottom left to top left
		// drawing gui
		w->body->draw();

		glfwSwapBuffers(window);
		glfwPollEvents(); // I AM HERE poll events blocks rendering while resizing.
		// can be fixed by threading
	}

	glfwDestroyCursor(handlers::standardCursor);
	glfwDestroyCursor(handlers::handCursor);
	// TODO: consider something else
	Geometry::Rectangle::destroy();
	Geometry::Line::destroy();
	Geometry::Circle::destroy();
	GuiElements::LineBreak::destroy();
	delete Geometry::Utility::textShader;
	delete window;

    return 0;
}
#include "checkbox.h"

#include "utility.h"

#include "glm/glm.hpp"

Checkbox::Checkbox(const Point&& topLeft, int width, int height, bool isChecked) : Element(Rectangle(topLeft, width, height)){
	this->isChecked = isChecked;
    eventListeners.addEventListener("click", Checkbox::defaultClick);
    // TODO consider moving this to rectngle (also for input and maybe other future widgets)
}

void Checkbox::draw() {
    Element::draw();

    if (isChecked) {
        // TODO clean coord conversion
        Point p(Rectangle::openglToGlfwCoords(rect.getXY()));
        Utility::renderText("V", p.x, p.y + 20.0f, 0.5f, glm::vec3(0.3,0.9,0.45));
    }
}

void Checkbox::defaultClick(Element* element, Event* args) {
    Checkbox* cb = (Checkbox*) element;
    cb->isChecked = !cb->isChecked;
    // TODO clean this
}

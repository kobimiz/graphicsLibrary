#include "checkbox.h"

#include "geometry.h"

#include "glm/glm.hpp"

Checkbox::Checkbox(const Geometry::Point&& topLeft, int width, int height, bool isChecked) : Element(Geometry::Rectangle(topLeft, width, height)){
	this->isChecked = isChecked;
    eventListeners.addEventListener("click", Checkbox::defaultClick);
    // TODO consider moving this to rectngle (also for input and maybe other future widgets)
}

void Checkbox::draw() {
    Element::draw();

    if (isChecked) {
        // TODO clean coord conversion
        Geometry::Point p(Geometry::Rectangle::openglToGlfwCoords(rect.getXY()));
        Geometry::Utility::renderText("V", p.x, p.y + 20.0f, 0.5f, glm::vec3(0.3,0.9,0.45));
    }
}

void Checkbox::defaultClick(Element* element, Event* args) {
    Checkbox* cb = (Checkbox*) element;
    cb->isChecked = !cb->isChecked;
    // TODO clean this
}

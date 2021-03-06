#include "button.h"
#include "geometry.h"

namespace GuiElements {

Button::Button() : Element(Geometry::Rectangle()) { }
Button::Button(Geometry::Rectangle& rect, Events::eventAction onclick) : Element(rect) {
    if (onclick != nullptr)
        eventListeners.addEventListener("click", onclick);
}

void Button::draw() {
    // TODO change look
    Element::draw();
}

}; // namespace GuiElements

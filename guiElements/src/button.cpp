#include "button.h"
#include "rectangle.h"

Button::Button() : Element(Rectangle()) { }
Button::Button(Rectangle& rect, Events::eventAction onclick) : Element(rect) {
    if (onclick != nullptr)
        eventListeners.addEventListener("click", onclick);
}

void Button::draw() {
    // TODO change look
    Element::draw();
}
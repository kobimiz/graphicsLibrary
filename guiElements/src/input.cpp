#include "input.h"
#include "event.h"
#include "geometry.h"

#include "glm/glm.hpp"

extern "C" double glfwGetTime();

#include <iostream>
// define static members
GuiElements::Input* GuiElements::Input::active;
float colors[] = {
	0.3f, 0.3f, 0.3f
};
Geometry::Line GuiElements::Input::blinker(Geometry::Point(0,0),Geometry::Point(0,0), colors, 1);

namespace GuiElements {

Input::Input() : Element(Geometry::Rectangle()) {
    // TODO think of a better solution. maybe with std::functional and lambdas
    this->textWidth = 0.0f;
    eventListeners.addEventListener("focus", Input::defaultFocus);
    eventListeners.addEventListener("click", Input::defaultClick);
}
Input::Input(const Geometry::Point&& topLeft, int width, int height) : Element(Geometry::Rectangle{topLeft, width, height}) {
    // TODO think of a better solution. maybe with std::functional and lambdas
    this->textWidth = 0.0f;
    eventListeners.addEventListener("focus", Input::defaultFocus);
    eventListeners.addEventListener("click", Input::defaultClick);
}
void Input::draw() {
    Element::draw();
    // TODO think of another way this might be overkill...
    // 1 period is 1s, in 50% of the period the blinker is faded
    if (Input::active != this) return;
    // text is 25*35
    float startX = this->rect.getX() + 10.0f + textWidth;
    float startY = this->rect.getY() + 2.0f * 2.0f;
    float endY   = this->rect.getY() + this->rect.height - 2.0f * 2.0f;
    blinker.setStart(startX, startY);
    blinker.setEnd  (startX, endY);
    if (sin(2.0*3.14159 * glfwGetTime()) <= 0.0)
        blinker.draw();
}
void Input::focus() {
    eventListeners.dispatch("focus", nullptr);
}
void Input::loseFocus() {
    if (Input::active == this)
        this->rect.borderWidth = 0.0f;
    Input::active = nullptr;
}
void Input::click(Event* args) {
    eventListeners.dispatch("click", args);
}
void Input::pushChar(const char c) {
    text.str += c;
    Geometry::Character ch = Geometry::Utility::characters[c];
    this->textWidth += ch.advance * text.scale / 64.0f; // advance is 1/64th of a pixel
}
void Input::popChar() {
    char c = text.str.back();
    text.str.pop_back();
    this->textWidth -= Geometry::Utility::characters[c].advance * text.scale / 64.0f; // advance is 1/64th of a pixel
}


// --- static ---

// The default focus action of an input
void Input::defaultFocus(Element* owningObject, Event* event) {
    if (Input::active != nullptr && Input::active != owningObject)
            Input::active->loseFocus();
    Input::active = (Input*) owningObject; // TODO really clean this
    Input::active->rect.borderWidth = 2.0f;
}
void Input::defaultBlur(Element* owningObject, Event* event) {
    if (Input::active != nullptr)
            Input::active->loseFocus();
    Input::active = nullptr;
}
// The default click action of an input
void Input::defaultClick(Element* owningObject, Event* event) {
    // TODO also clean this
        Input* temp = (Input*)owningObject;
        temp->focus();
}

}; // namespace GuiElements

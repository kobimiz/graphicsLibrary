#include "element.h"

#include <numeric>

class Event;

GuiElements::Element* GuiElements::Element::mouseIsIn;
const int GuiElements::Element::AUTO = -1;

namespace GuiElements {

Element::Element(Geometry::Rectangle& rect) : eventListeners(), rect(rect) {
    isDisabled = false;
    isVisible  = true;
    eventListeners.updateOwningObject(this);
    if (rect.width == Element::AUTO)
        calculateWidth();
    if (rect.height == Element::AUTO)
        calculateHeight();

}

Element::Element(const Geometry::Rectangle&& rect) : eventListeners(), rect(rect) {
    isDisabled = false;
    isVisible  = true;
    eventListeners.updateOwningObject(this);
    if (rect.width == Element::AUTO)
        calculateWidth();
    if (rect.height == Element::AUTO)
        calculateHeight();
}

void Element::draw() {
    if (isVisible) {
        rect.draw();
        if (text.str != "") {
            Geometry::Point topLeft = rect.getXY();
            topLeft.x += 10 * text.scale;
            topLeft.y += (rect.height + 35 * text.scale) / 2.0f; // align to center
            text.draw(topLeft);
        }
    }
}

void Element::click(Event* args) {
    eventListeners.dispatch("click", args);
}

bool Element::isContainer() {
    return false;
}

void Element::calculateWidth() {
    rect.width = std::accumulate(text.str.begin(), text.str.end(), 0, [](int sum, char c) {
        auto ch = Geometry::Utility::characters[c];
        return sum + 0.5f * ch.size.x + 2 * ch.bearing.x;
    });
}

void Element::calculateHeight() {
    // TODO: this, based on rows
    rect.height = 70;
}

}; // namespace GuiElements
#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "element.h"

namespace GuiElements {

class Checkbox : public Element {
public:
    bool isChecked;
    Checkbox(const Geometry::Point&& topLeft, int width, int height, bool isChecked = false);

    void draw();

    static void defaultClick(Element* element, Event* args);
};

}; // namespace GuiElements

#endif
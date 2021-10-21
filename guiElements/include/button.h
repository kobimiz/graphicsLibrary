#ifndef BUTTON_H
#define BUTTON_H

#include "element.h"
#include "events.h"

class Geometry::Rectangle;

class Button : public Element {
public:
	Button();
	Button(Geometry::Rectangle& rect, Events::eventAction onclick = nullptr);

	void draw() override;
};

#endif
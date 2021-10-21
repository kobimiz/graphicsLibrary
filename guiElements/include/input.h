#ifndef INPUT_H
#define INPUT_H

#include <string>

#include "element.h"
#include "geometry.h"

class Input : public Element {
private:
	float textWidth;
public:
    // TODO think of not putting text as public
    static Input* active;
	// TODO consider making each input a blinker of his own (maybe no?)
	static Geometry::Line blinker;
	// TODO think about making a blinker class (singleton?)

	Input();
	Input(const Geometry::Point&& topLeft, int width, int height);
	void draw() override;
	void click(Event* args) override;
	void focus();
	void loseFocus();
	void pushChar(const char c);
	void popChar();

	static void defaultFocus(Element* owningObject, Event* event);
	static void defaultClick(Element* owningObject, Event* event);
	static void defaultBlur(Element* owningObject, Event* event);
};

#endif
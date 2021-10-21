#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>

#include "events.h"
#include "rectangle.h"
#include "text.h"

class Element {
private:
public:
    std::string id;
    
    bool isVisible;
    bool isDisabled; // can be clicked
    Events eventListeners;
	Rectangle rect;

    // TODO: better
    Text text;

    // TODO add z-index;

	static Element* mouseIsIn;

    Element(Rectangle& rect);
    Element(const Rectangle&& rect);

    virtual void draw();
    virtual void click(Event* args);
    virtual bool isContainer();
    
    // recalculate dimensions based on text
    void calculateWidth();
    void calculateHeight();

    // NOTE: does not automatically update, just sets automatically on construction
    static const int AUTO;
};

#endif
#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>

#include "events.h"
#include "geometry.h"
#include "text.h"

class Element {
private:
public:
    std::string id;
    
    bool isVisible;
    bool isDisabled; // can be clicked
    Events eventListeners;
	Geometry::Rectangle rect;

    // TODO: better
    Text text;

    // TODO add z-index;

	static Element* mouseIsIn;

    Element(Geometry::Rectangle& rect);
    Element(const Geometry::Rectangle&& rect);

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
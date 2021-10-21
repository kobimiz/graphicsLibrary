#ifndef EVENT_H
#define EVENT_H

#include <string>

#include "geometry.h"

struct Event {
    std::string name;
    Geometry::Point cursorPos;
    // TODO add keys pressed, modifiers etc
};

#endif
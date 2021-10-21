#ifndef EVENT_H
#define EVENT_H

#include <string>

#include "point.h"

struct Event {
    std::string name;
    Point cursorPos;
    // TODO add keys pressed, modifiers etc
};

#endif
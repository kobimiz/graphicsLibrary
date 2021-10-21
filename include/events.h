#ifndef EVENTS_H
#define EVENTS_H

#include <vector>
#include <map>
#include <string>

namespace GuiElements {
    class Element;
};

class Event;

// TODO ^^ think of a better solution
class Events {
public:
    typedef void (*eventAction)(GuiElements::Element*, Event*);
private:
    GuiElements::Element* owningObject;
    std::map<std::string, std::vector<eventAction>> events;
public:
    Events();
    Events(GuiElements::Element* owningObject);
    Events(GuiElements::Element* owningObject, const char* eventName, eventAction action);

    void addEventListener(const char* eventName, eventAction action);
    void dispatch(const char* eventName, Event* args);
    void updateOwningObject(GuiElements::Element* updated);
};

#endif
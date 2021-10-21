#ifndef EVENTS_H
#define EVENTS_H

#include <vector>
#include <map>
#include <string>

class Element;
class Event;

// TODO ^^ think of a better solution
class Events {
public:
    typedef void (*eventAction)(Element*, Event*);
private:
    Element* owningObject;
    std::map<std::string, std::vector<eventAction>> events;
public:
    Events();
    Events(Element* owningObject);
    Events(Element* owningObject, const char* eventName, eventAction action);

    void addEventListener(const char* eventName, eventAction action);
    void dispatch(const char* eventName, Event* args);
    void updateOwningObject(Element* updated);
};

#endif
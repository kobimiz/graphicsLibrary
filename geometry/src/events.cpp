#include <vector>

#include "events.h"

Events::Events(): owningObject(nullptr) { }
Events::Events(GuiElements::Element* owningObject): owningObject(owningObject) { }
Events::Events(GuiElements::Element* owningObject, const char*  eventName, eventAction action):owningObject(owningObject) {
    addEventListener(eventName, action);
}

void Events::addEventListener(const char* eventName, eventAction action) {
    events[eventName].push_back(action);
}

void Events::dispatch(const char* eventName, Event* args) {
    auto found = events.find(eventName);
    if (found == events.end()) return;
    // TODO consider throwing error
    std::vector<eventAction> actions = events[eventName];
    for (auto &&action : actions)
        action(owningObject, args);
}

void Events::updateOwningObject(GuiElements::Element* updated) {
    owningObject = updated;
}
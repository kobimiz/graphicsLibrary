#ifndef CONTAINER_H
#define CONTAINER_H

#include <map>
#include <string>

#include "element.h"

class Container : public Element {
public:
    std::vector<Element*> elements;
    std::map<std::string, Element*> idMap;

    Container();
    Container(Geometry::Point&& topLeft, int width, int height);
    
    void add(Element* element);
    // Does not take into account the coordinates in element
    virtual void addAutoArrange(Element* element);
    virtual void autoArrange();
    void remove(Element* element);
    Element* findById(std::string&& id);

    virtual void draw();
    virtual bool isContainer() override;

    void forEachChild(void (*func)(Element*, void*), void* args);
};

#endif
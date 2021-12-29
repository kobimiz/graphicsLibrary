#ifndef WINDOW_H
#define WINDOW_H

#include "tinyxml2.h"

#include "container.h"

namespace GuiElements {

class Window {
private:
    static Element* getElement(tinyxml2::XMLElement* elem);
    static void deleteChildren(Container* body);
    static void addDoc(tinyxml2::XMLNode& doc, Container* body);
    
public:
    float currX,currY;
    float lastX,lastY;
    float rotationXMag, rotationYMag;
    float prevRotationXMag, prevRotationYMag;

    Container* body;
    Window();
    ~Window();

    void fromDoc(std::string&& docPath);
    void deleteChildren();
};

}; // namespace GuiElements

#endif
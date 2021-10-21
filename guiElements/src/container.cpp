#include "../include/container.h"

#include <algorithm>
#include "rectangle.h"
#include "lineBreak.h"

Container::Container() : Element(Rectangle()) {};

Container::Container(Point&& topLeft, int width, int height) : Element(Rectangle(topLeft, width, height)) { }

void Container::add(Element* element) {
    if (element->id != "") {
        if (idMap.find(element->id) != idMap.end())
            throw "id '" + element->id + "' already exists";
        idMap[element->id] = element;
    }
    elements.push_back(element);

}
// Currently, there is no boundary checking. assumes container is infinite.
void Container::addAutoArrange(Element* element) {
    // Calculate next free space.
    // TODO: cache these calculations
    // TODO: add overflow reports
    // TODO: support non rectangle shapes(rotated?)
    element->rect.setXY(this->rect.getXY());

    for (auto &&e : elements) {
        if (e == LineBreak::getInstance()) {
            element->rect.setX(0.0f);
            element->rect.setY(e->rect.getY() + e->rect.height);
            continue;
        }
        if (e->rect.doIntersect(element->rect)) {
            // try to move horizontaly
            element->rect.setX(e->rect.getX() + e->rect.width);
            float thisRight = this->rect.getX() + this->rect.width;
            float elementRight = element->rect.getX() + element->rect.width;
            if (elementRight > thisRight) {
                // move to the next row
                element->rect.setX(0.0f);
                element->rect.setY(e->rect.getY() + e->rect.height);
            }
        } else
            break;
    }
    add(element);
}
// I AM HERE TODO THIS
// Currently, there is no boundary checking. assumes container is infinite.
void Container::autoArrange() {
    float x = 0.0f;
    float yStart = 0.0f;
    float yEnd   = 0.0f;
    for (auto &&elem : elements) {
        elem->rect.setX(x);
        elem->rect.setY(yStart);
        if (elem == LineBreak::getInstance()) {
            x = 0.0f;
            yStart += elem->rect.height;
            continue;
        }
        float elemRight = elem->rect.getX() + elem->rect.width;
        if (elemRight > Rectangle::screenWidth) {
            // check if can move to next row
            if (elem->rect.width > Rectangle::screenWidth) {
                // overflow x
                x = 0.0f;
                yStart += elem->rect.height;
            } else {
                elem->rect.setX(0.0f);
                elem->rect.setY(0.0f);
            }

        } else {
            x += elem->rect.width;
        }
    }
}

void Container::remove(Element* element) {
    auto result = std::find(elements.begin(), elements.end(), element);
    if (result != elements.end())
        elements.erase(result);
}

void Container::draw() {
    Element::draw();
    std::for_each(elements.begin(), elements.end(), [](Element* e) {
        e->draw();
    });
}

bool Container::isContainer() {
    return true;
}

Element* Container::findById(std::string&& id) {
    // TODO: optimize
    if (this->id == id)
        return this;
    auto res = idMap.find(id);
    if (res == idMap.end()) {
        for (auto &&e : elements) {
            if (e->isContainer()) {
                Element* eRes = ((Container*)e)->findById(std::move(id));
                if (eRes != nullptr)
                    return eRes;
            }
        }
        return nullptr;
    }
    return res->second;
}

// TODO give option to determine order
void Container::forEachChild(void (*func)(Element*, void*), void* args) {
    for (auto &&element : elements) {
        func(element, args);
        if (element->isContainer())
            ((Container*)element)->forEachChild(func, args);
    }
}

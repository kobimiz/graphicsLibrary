#ifndef LINEBREAK_H
#define LINEBREAK_H

#include "element.h"

namespace GuiElements {

class LineBreak : public Element {
private:
    LineBreak();
    static LineBreak* br;
public:
    static void init();
    static void destroy();
    static LineBreak* getInstance();

    virtual void draw() override;
};

}; // namespace GuiElements

#endif
#include "lineBreak.h"

LineBreak* LineBreak::br;

LineBreak::LineBreak() : Element(Geometry::Rectangle()) { }

void LineBreak::init() {
    LineBreak::br = new LineBreak();
    LineBreak::br->rect.height = 0;
    LineBreak::br->rect.width  = 0;
}

void LineBreak::destroy() {
    delete LineBreak::br;
}

LineBreak* LineBreak::getInstance() {
    return LineBreak::br;
}

void LineBreak::draw() {
    
}
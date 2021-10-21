#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

#include "element.h"
#include "geometry.h"

class Rectangle;
class Event;

namespace GuiElements {

class Graph : public Element {
private:
    // std::vector<Func> funcs;
    // TODO add custom number of points
    std::vector<std::vector<Geometry::Point>> curves;
public:
    Graph(Geometry::Rectangle& rec);
    void draw() override;
    void click(Event* args) override;

    static void drawCurve(std::vector<Geometry::Point>& curve);
};

}; // namespace GuiElements

#endif
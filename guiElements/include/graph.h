#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

#include "element.h"
#include "point.h"

class Rectangle;
class Event;

class Graph : public Element {
private:
    // std::vector<Func> funcs;
    // TODO add custom number of points
    std::vector<std::vector<Point>> curves;
public:
    Graph(Rectangle& rec);
    void draw() override;
    void click(Event* args) override;

    static void drawCurve(std::vector<Point>& curve);
};

#endif
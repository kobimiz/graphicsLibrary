#include "graph.h"

namespace GuiElements {

Graph::Graph(Geometry::Rectangle& rec) : Element(rec) { }
void Graph::draw() {
	Element::draw();
    for (auto &&curve : curves) {
        
    }
}
void Graph::click(Event* args) {
	// TODO
}

void Graph::drawCurve(std::vector<Geometry::Point>& curve) {
    
}

}; // namespace GuiElements
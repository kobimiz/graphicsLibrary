#include "graph.h"

Graph::Graph(Rectangle& rec) : Element(rec) { }
void Graph::draw() {
	Element::draw();
    for (auto &&curve : curves) {
        
    }
}
void Graph::click(Event* args) {
	// TODO
}

void Graph::drawCurve(std::vector<Point>& curve) {
    
}

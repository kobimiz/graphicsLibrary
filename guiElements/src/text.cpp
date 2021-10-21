#include "../include/text.h"

Text::Text() : scale(0.0f) { }

Text::Text(std::string&& str, Geometry::Color&& color, float scale) : str(str), color(color), scale(scale) { }

void Text::draw(const Geometry::Point& topLeft) {
    // TODO better
    glm::vec3 c(color.rgb[0], color.rgb[1], color.rgb[2]);
	Geometry::Utility::renderText(str, topLeft.x, topLeft.y, scale, c);
}
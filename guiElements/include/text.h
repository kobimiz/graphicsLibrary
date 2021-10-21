#ifndef TEXT_H
#define TEXT_H

#include <string>

#include "geometry.h"
 
class Text {
public:
    std::string str;
    Geometry::Color color;
    float scale;

    Text();
    Text(std::string&& str, Geometry::Color&& color, float scale);
    void draw(const Geometry::Point& topLeft);
};

#endif
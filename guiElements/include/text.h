#ifndef TEXT_H
#define TEXT_H

#include <string>

#include "rectangle.h"
#include "utility.h"
 
class Text {
public:
    std::string str;
    Color color;
    float scale;

    Text();
    Text(std::string&& str, Color&& color, float scale);
    void draw(const Point& topLeft);
};

#endif
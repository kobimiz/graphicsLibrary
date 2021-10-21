#ifndef COLOR_H
#define COLOR_H

#include <string>

namespace Geometry {

class Color {
public:
	float rgb[3];
	Color();
	Color(std::string rgb);
	Color(float r, float g, float b);
	Color(float rgb[3]);

	Color operator*(float scalar);
	Color operator+(float add);
};

}; // namespace Geometry

#endif
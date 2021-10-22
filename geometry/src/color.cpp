#include "geometry.h"

namespace Geometry {

Color::Color() {
    this->rgb[0] = 0.0f;
    this->rgb[1] = 0.0f;
    this->rgb[2] = 0.0f;
}
Color::Color(std::string rgb) {
    size_t pos = 0;
    // TODO implement more error checking and handling while parsing
    for (size_t i = 0; i < 2; i++)
    {
        size_t pos = rgb.find(",");
        if (pos == std::string::npos)
            throw "Invalid color format";
        this->rgb[i] = std::stof(rgb.substr(0,pos));
        rgb.erase(0, pos + std::string(",").length());
    }
    this->rgb[2] = std::stof(rgb);
}

Color::Color(float r, float g, float b) {
    this->rgb[0] = r;
    this->rgb[1] = g;
    this->rgb[2] = b;
}
Color::Color(float rgb[3]) {
    this->rgb[0] = rgb[0];
    this->rgb[1] = rgb[1];
    this->rgb[2] = rgb[2];
}
Color Color::operator*(float scalar) {
    return Color(scalar * this->rgb[0], scalar * this->rgb[1], scalar * this->rgb[2]);
}
Color Color::operator+(float add) {
    return Color(add + this->rgb[0], add + this->rgb[1], add + this->rgb[2]);
}

}; // namespace Geometry
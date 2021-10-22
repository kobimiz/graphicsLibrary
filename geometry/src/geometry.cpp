#include "geometry.h"


namespace Geometry {
    
void initGeometry() {
    Rectangle::init();
	Line::init();
	Circle::init();
	Utility::initFreeType();
}

void destroyGeometry() {
    Rectangle::destroy();
	Line::destroy();
	Circle::destroy();
}

}; // namespace Geometry
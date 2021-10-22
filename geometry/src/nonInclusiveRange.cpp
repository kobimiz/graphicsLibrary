#include "geometry.h"

#include <cmath>

namespace Geometry {

bool NonInclusiveRange::doIntersect(const NonInclusiveRange& another) {
	return !(this->start >= another.end || this->end <= another.start);
}

bool NonInclusiveRange::doIntersect(NonInclusiveRange&& another) {
	return doIntersect(another);
}

}; // namespace Geometry
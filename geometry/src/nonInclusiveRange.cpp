#include "nonInclusiveRange.h"
#include <cmath>

bool NonInclusiveRange::doIntersect(const NonInclusiveRange& another) {
	return !(this->start >= another.end || this->end <= another.start);
}

bool NonInclusiveRange::doIntersect(NonInclusiveRange&& another) {
	return doIntersect(another);
}

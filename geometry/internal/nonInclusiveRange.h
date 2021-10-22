#ifndef NONINCLUSIVERANGE_H
#define NONINCLUSIVERANGE_H

namespace Geometry {
    
class NonInclusiveRange {
public:
    float start, end;

    bool doIntersect(const NonInclusiveRange& another);
    bool doIntersect(NonInclusiveRange&& another);
};

}; // namespace Geometry


#endif
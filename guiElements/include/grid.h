#ifndef GRID_H
#define GRID_H

#include "container.h"
#include <vector>

class Grid : public Container {
private:
    int currentRowEndX,
        currentRowStartY,
        currentRowEndY,
        rowCount;
public:
    // NOTE: changes the position of element
    // TODO: think of something better

    Grid();
    virtual void addAutoArrange(Element* element) override;
};

#endif
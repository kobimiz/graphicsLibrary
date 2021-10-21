#include "grid.h"
#include "lineBreak.h"

int max(int x, int y) {
    if (x > y) return x;
    return y;
}

namespace GuiElements {

Grid::Grid() : Container(), rowCount(0) { }

void Grid::addAutoArrange(Element* element) {
    if (rowCount == 0) {
        rowCount = 1;
        element->rect.setXY(rect.getXY());

        currentRowEndX = rect.getX() + element->rect.width;
        currentRowStartY = rect.getY();
        currentRowEndY = currentRowStartY + element->rect.height;

    } else if(element == LineBreak::getInstance()) {
        // move to next row
        currentRowEndX = rect.getX();
        currentRowStartY = currentRowEndY;
        rowCount++;
        return;
    } else if (currentRowEndX + element->rect.width > rect.getX() + rect.width) {
        // position element
        element->rect.setX(rect.getX());
        element->rect.setY(currentRowEndY);

        // move to next row
        currentRowEndX = rect.getX() + element->rect.width;
        currentRowStartY = currentRowEndY;
        currentRowEndY += element->rect.height;
        rowCount++;

    } else {
        element->rect.setX(currentRowEndX);
        element->rect.setY(currentRowStartY);

        currentRowEndX += element->rect.width;
        currentRowEndY = max(currentRowEndY, currentRowStartY + element->rect.height);
    }

    add(element);
}

}; // namespace GuiElements
#include "game/cell.hpp"

namespace game {

void Cell::connectCell(Direction direction, Cell *cell) {
    _neighbours[direction] = cell;
}

void Cell::raiseWall(Direction direction) {
    auto neighbour = _neighbours[direction];

    _neighbours[direction] = 0;

    /* Make sure that prior neighbour also gets a wall */
    if (neighbour) {
        neighbour->_neighbours[opposite(direction)] = 0;
    }
}

bool Cell::canReach(Direction direction, Cell *cell) {
    auto neighbour = _neighbours[direction];

    while (neighbour) {
        if (neighbour == cell) {
            return true;
        }

        if (neighbour == this) {
            return false;
        }

        neighbour = neighbour->_neighbours[direction];
    }
}
}


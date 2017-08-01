#include <stdlib.h>
#include <iostream>

#include "game/cell.hpp"

#define D(x)

namespace game {

Cell::Cell() : _content(0)
{
    _neighbours[North] = { 0 };
    _neighbours[South] = { 0 };
    _neighbours[East]  = { 0 };
    _neighbours[West]  = { 0 };
}

Cell::Cell(const Cell &cell) :
    backgroundTile(),
    contentTile()
{
    D(std::cout << typeid(*this).name() << "::copying\n");

    _neighbours[North] = { 0 };
    _neighbours[South] = { 0 };
    _neighbours[East]  = { 0 };
    _neighbours[West]  = { 0 };
}

void Cell::connect(Direction direction, Cell *cell,
                   int transition)
{
    _neighbours[direction].cell       = cell;
    _neighbours[direction].transition = transition;
}

void Cell::setBackgroundTile(std::unique_ptr<sf::Sprite> t)
{
    backgroundTile = std::move(t);
    backgroundTile->setPosition(pos);
}

void Cell::setContentTile(std::unique_ptr<sf::Sprite> t)
{
    contentTile = std::move(t);
    contentTile->setPosition(pos);
}

void Cell::disallowDirection(Direction d)
{
    auto transition = &_neighbours[d];
    auto cell = transition->cell;

    if (cell) {
        auto neighbour = &cell->_neighbours[oppositeDirection[d]];

        neighbour->cell       = 0;
        neighbour->transition = 0;
    }
}

void Cell::disallow()
{
    /* My neighbours should no longer reach me */
    disallowDirection(North);
    disallowDirection(South);
    disallowDirection(West);
    disallowDirection(East);
}

bool Cell::canReach(Direction direction, Cell *cell) {
    auto neighbour = &_neighbours[direction];

    while (neighbour->cell) {
        if (neighbour->cell == cell) {
            return true;
        }

        if (neighbour->cell == this) {
            return false;
        }

        neighbour = &neighbour->cell->_neighbours[direction];
    }
    return false;
}

}


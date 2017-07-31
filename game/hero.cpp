#include "game/hero.hpp"

namespace game {

Hero::Hero(Cell *start, Direction direction) :
    _cell(start),
    pos(start->pos),
    direction(direction),
    _nextDirection(direction),
    _velocity(0)
{
}

void Hero::update(sf::Time &elapsed) {
    if (_animator.is_set()) {
        _animator.update(elapsed.asMicroseconds(),
                         [this](auto progress) {
                            if (pos.x != _cell->pos.x) {
                                pos.x += progress;
                            }
                            else {
                                pos.y += progress;
                            }
                         },
                         [this]() {
                            pos = _cell->pos;
                         });
    }
    else {
        direction = _nextDirection;

        if (_velocity) {
            auto nextCell = _cell->getNeighbour(direction);
            if (nextCell) {
                /* Start animation going for the neighbour */
                auto goal = nextCell->pos.x != _cell->pos.x ?
                            nextCell->pos.x - _cell->pos.x :
                            nextCell->pos.y - _cell->pos.y;
                _animator.set(200000, goal);
                _cell = nextCell;
                _velocity = 1;
            }
            else {
                /* No cell in current direction, stop ! */
                _velocity = 0;
            }
        }
        else {
            /* Standing still, waiting for new direction */
        }
    }
}

void Hero::start(Direction direction)
{
    _velocity = 1;
    _nextDirection = direction;
}

void Hero::stop()
{
    _velocity = 0;
}

}

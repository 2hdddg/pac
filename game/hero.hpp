#pragma once

#include "game/cell.hpp"
#include "util/animator.hpp"

namespace game {

class Hero {
public:
    Hero(Cell *start, Direction direction);

    void update(sf::Time &elapsed);
    void start(Direction direction);
    void stop();


    sf::Vector2f pos;
    Direction direction;
    float offset;
private:
    Cell      *_cell;
    float     _velocity;
    Animator  _animator;
    Direction _nextDirection;
};

}

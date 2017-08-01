#include <iostream>
#include <stdlib.h>

#include "game/monster.hpp"
#include "game/constants.hpp"

#define D(x)

namespace game {

Monster::Monster(Cell *start, Direction direction,
                 std::vector<std::shared_ptr<Hero>> &heroes) :
    pos(start->pos),
    cell(start),
    _direction(direction),
    _heroes(heroes),
    _isTeleporting(false),
    _spriteIndex(0)
{
    D(std::cout << typeid(*this).name() << "::constructor\n");
}

Monster::~Monster()
{
    D(std::cout << typeid(*this).name() << "::destructor\n");
}


bool Monster::clockwise()
{
    auto nextDirection = clockwiseDirection[_direction];
    auto next = cell->move(nextDirection);

    if (next.cell) {
        _direction = nextDirection;
        return true;
    }

    return false;
}

bool Monster::counterClockwise()
{
    auto nextDirection = clockwiseDirection[_direction];
    nextDirection = oppositeDirection[nextDirection];
    auto next = cell->move(nextDirection);

    if (next.cell) {
        _direction = nextDirection;
        return true;
    }

    return false;
}

bool Monster::opposite()
{
    auto nextDirection = oppositeDirection[_direction];
    auto next = cell->move(nextDirection);

    if (next.cell) {
        _direction = nextDirection;
        return true;
    }

    return false;
}

bool Monster::turn()
{
    return rand() % 3 ? clockwise() || counterClockwise() :
                        counterClockwise() || clockwise();
}

bool Monster::lookForHero(Hero *hero)
{
    for (auto i = 0; i < 4; i++) {
        auto d = (Direction)i;
        if (cell->canReach(d, hero->cell)) {
            _direction = d;
            return true;
        }
    }

    return false;
}

void Monster::update(long delta)
{
    D(std::cout << typeid(*this).name() << "::update\n");

    if (_cellAnimator.is_set()) {
        _cellAnimator.update(delta,
                         [this](auto progress) {
                            pos += _distance * progress;
                            auto n = _sprites[_direction].size();
                            _spriteIndex += n * progress;
                         },
                         [this]() {
                            pos = cell->pos;
                            _isTeleporting = false;
                            _spriteIndex = 0;
                         });
    }
    else {
        /* Default is to continue in same direction */
        auto next = cell->move(_direction);

        /* Always try to find the enemy */
        for (auto hero : _heroes) {
            if (lookForHero(hero.get())) {
                next = cell->move(_direction);
            }
        }

        /* Possibility to change direction */
        if ((rand() % 4) == 0 && turn()) {
            next = cell->move(_direction);
        }

        if (!next.cell) {
            turn() || opposite();
            next = cell->move(_direction);
        }

        if (next.cell) {
            auto nextCell = next.cell;

            /* Start animation going to the next cell */
            _distance = nextCell->pos - cell->pos;
            _cellAnimator.set(200000, 1);
            cell = nextCell;
            _isTeleporting = next.transition == Teleport;
        }
    }

    /* Check if my cell is same as any heroes */
    for (auto hero : _heroes) {
        if (cell == hero->cell) {
            hero->caught();
        }
    }
}

void Monster::render(sf::RenderTarget &target,
                     const sf::Transform &transform)
{
    D(std::cout << typeid(*this).name() << "::draw\n");

    if (_isTeleporting) {
        return;
    }
    auto sprite = *_sprites[_direction][_spriteIndex];
    sprite.setPosition(pos);
    target.draw(sprite);
}

void Monster::setSprite(Direction direction,
                        std::unique_ptr<sf::Sprite> sprite)
{
    _sprites[direction].push_back(std::move(sprite));
}

}

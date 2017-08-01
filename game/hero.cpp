#include <iostream>

#include "game/hero.hpp"
#include "game/constants.hpp"

#define D(x)

namespace game {

/* Time it takes to move between cells, in microseconds */
auto CELL_MOTION_TIME = 100000;

Hero::Hero(Cell *spawn,
           Direction direction) :
    pills(0),
    lives(2),
    _consumedCallback(0),
    _fx(6, 6 * CELL_MOTION_TIME, sf::Vector2f(0, 0))
{
    reset(spawn, direction);
    D(std::cout << typeid(*this).name() << "::constructor\n");
}

Hero::~Hero()
{
    D(std::cout << typeid(*this).name() << "::destructor\n");
}

void Hero::update(long delta)
{
    D(std::cout << typeid(*this).name() << "::update\n");

    _fx.update(delta);

    if (_cellAnimator.is_set()) {
        _cellAnimator.update(delta,
                /* On animation progress */
                 [this](auto progress) {
                    pos += _distance * progress;
                    auto n = _sprites[_direction].size();
                    _spriteIndex += n * progress;
                 },
                /* On animation done, entered cell! */
                 [this]() {
                    pos = cell->pos;
                    _isTeleporting = false;
                    _spriteIndex = 0;
                 });
    }

    if (_immortalAnimator.is_set()) {
        _immortalAnimator.update(delta,
                0,
                [this]() {
                    _immortalTicks--;
                    if (_immortalTicks) {
                        _isHidden = !_isHidden;
                        _immortalAnimator.set(300000, 0);
                    }
                    else {
                        _isHidden = false;
                    }
                });
    }

    if (!_cellAnimator.is_set()) {
        /* Try to consume current cell */
        switch (cell->consumeContent(_fx)) {
            case Pill:
                pills++;
                if (_consumedCallback) {
                    _consumedCallback(cell, Pill);
                }
                break;
            default:
                break;
        }

        /* Apply updates */
        if (_nextUpdate.stopped) {
            _velocity = 0;
            _nextUpdate.stopped = false;
        }
        if (_nextUpdate.started) {
            _velocity = 1;
            _direction = _nextUpdate.direction;
            _nextUpdate.started = false;
        }
        if (_nextUpdate.beenCaught) {
            _nextUpdate.beenCaught = false;

            if (_immortalTicks == 0) {
                /* Still have more lives */
                if (lives) {
                    lives--;
                    pos = _spawn->pos;
                    cell = _spawn;
                    _velocity = 0;
                    _immortalTicks = 11;
                    _immortalAnimator.set(0, 0);
                }
                /* Lost last life */
                else {
                    lives--;
                    cell = &_deathCell;
                    _velocity = 0;
                    /* Not necessary but looks better
                     * until there are sprites for hero. */
                    _isHidden = true;
                }
            }
        }

        if (_velocity) {
            auto next = cell->move(_direction);
            auto nextCell = next.cell;
            if (nextCell) {
                auto time = CELL_MOTION_TIME;
                /* I shouldn't be drawn while teleporting and
                 * since camera is following my animated
                 * position let's do it a bit slower than moving
                 * to the next cell to enhance the effect. */
                _isTeleporting = next.transition == Teleport;
                if (_isTeleporting)
                    time *= 5;

                /* Start animation going for the next cell */
                _distance = nextCell->pos - cell->pos;
                _cellAnimator.set(time, 1);
                cell = nextCell;
                _velocity = 1;
            }
            else {
                /* No cell in current direction, stop ! */
                _velocity = 0;
            }
        }
    }
}

void Hero::render(sf::RenderTarget &target,
                  const sf::Transform &transform,
                  bool isMe)
{
    D(std::cout << typeid(*this).name() << "::render\n");

    if (_isTeleporting || _isHidden) {
        return;
    }

    auto sprite = *_sprites[_direction][_spriteIndex];
    sprite.setPosition(pos);
    target.draw(sprite);

    if (isMe) {
        _fx.render(target);
    }
}

void Hero::setSprite(Direction direction,
                        std::unique_ptr<sf::Sprite> sprite)
{
    _sprites[direction].push_back(std::move(sprite));
}

void Hero::reset(Cell *spawn, Direction direction)
{
    _nextUpdate = NextUpdate();
    _spawn = spawn;
    pos = spawn->pos;
    cell = spawn;
    _velocity = 0;
    _direction = direction;
    _isHidden = false;
    _spriteIndex = 0;
    _immortalTicks = 0;
    _isTeleporting = false;
    _fx.reset();
}

}

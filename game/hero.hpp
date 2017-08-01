#pragma once

#include "game/cell.hpp"
#include "util/animator.hpp"
#include "pilleatingfx.hpp"

namespace game {

class Hero {
public:
    typedef std::function<void (Cell *cell, int content)> ConsumedFunc;

    Hero(Cell *spawn,
         Direction direction);
    ~Hero();

    void update(long delta);
    void render(sf::RenderTarget &target,
                const sf::Transform &transform,
                bool isMe);

    void setSprite(Direction direction,
                   std::unique_ptr<sf::Sprite> sprite);

    void start(Direction direction) {
        _nextUpdate.started   = true;
        _nextUpdate.direction = direction;
    }
    void stop() {
        _nextUpdate.stopped = true;
    }
    void caught() {
        _nextUpdate.beenCaught = true;
    }
    bool isDead() {
        return lives < 0;
    }
    void setConsumedCallback(ConsumedFunc consumed) {
        _consumedCallback = consumed;
    }
    void reset(Cell *spawn, Direction d);

    /* Current position, animated between cells */
    sf::Vector2f pos;
    /* Current cell and destination for animation,
     * when transitioning */
    Cell        *cell;
    /* Number of consumed pills */
    unsigned int pills;
    int          lives;

private:
    class NextUpdate {
    public:
        NextUpdate() {
            stopped = false;
            started = false;
            beenCaught = false;
        }

        bool      stopped;
        bool      started;
        Direction direction;
        bool      beenCaught;
    };

    NextUpdate   _nextUpdate;

    Direction    _direction;
    float        _velocity;
    sf::Vector2f _distance;
    bool         _isTeleporting;
    int          _immortalTicks;
    bool         _isHidden;

    Animator     _cellAnimator;
    Animator     _immortalAnimator;
    Cell        *_spawn;
    Cell         _deathCell;

    ConsumedFunc _consumedCallback;

    float                                    _spriteIndex;
    std::vector<std::unique_ptr<sf::Sprite>> _sprites[4];

    PillEatingFx   _fx;
};

}

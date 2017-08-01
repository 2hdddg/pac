#pragma once

#include <memory>

#include "game/cell.hpp"
#include "game/hero.hpp"
#include "util/animator.hpp"

namespace game {

class Monster {
public:
    Monster(Cell *start, Direction direction,
            std::vector<std::shared_ptr<Hero>> &heroes);
    ~Monster();

    void update(long delta);
    void render(sf::RenderTarget &target,
                const sf::Transform &transform);

    void setSprite(Direction direction,
                   std::unique_ptr<sf::Sprite> sprite);

    sf::Vector2f pos;
    Cell        *cell;

private:

    bool clockwise();
    bool counterClockwise();
    bool turn();
    bool opposite();
    bool lookForHero(Hero *hero);

    Direction                          _direction;
    std::vector<std::shared_ptr<Hero>> &_heroes;
    Animator                           _cellAnimator;
    sf::Vector2f                       _distance;
    bool                               _isTeleporting;

    float                                    _spriteIndex;
    std::vector<std::unique_ptr<sf::Sprite>> _sprites[4];
};

}

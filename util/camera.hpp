#pragma once

#include <iostream>


namespace game {

class Camera {
public:
    Camera(const sf::Vector2f gameSize,
           const sf::Vector2f visibleSize)
    {
        /* When centering camera, don't use position less
         * than half the visible area, otherwise we will
         * show emptyness on the left side of the screen */
        _min = visibleSize / 2.0f;
        /* Same rule for centering to the right.. */
        _max = gameSize - _min;

        if (gameSize.x < visibleSize.x) {
            _min.x = _max.x = gameSize.x / 2;
        }
        if (gameSize.y < visibleSize.y) {
            _min.y = _max.y = gameSize.y / 2;
        }
    }

    sf::Vector2f centerAt(const sf::Vector2f pos)
    {
        return sf::Vector2f(std::min(std::max(_min.x, pos.x), _max.x),
                            std::min(std::max(_min.y, pos.y), _max.y));
    }

private:
    sf::Vector2f _min;
    sf::Vector2f _max;
};

}

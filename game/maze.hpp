#pragma once

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "util/animator.hpp"
#include "game/cell.hpp"
#include "game/hero.hpp"

namespace game {

class Maze {
public:

    Maze(unsigned int width, unsigned int height);
    void event(sf::Event &event);
    void update(sf::Time &elapsed);
    void draw(sf::RenderTarget &target);

    std::unique_ptr<Hero> hero;

private:
    unsigned int _width;
    unsigned int _height;

    std::vector<Cell> _cells;
};

class Ghost {
};

}

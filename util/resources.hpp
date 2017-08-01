#pragma once

#include <SFML/Graphics.hpp>

namespace game {

class Resources {
public:
    Resources(sf::Vector2f &gameResolution);

    sf::Font     standardFont;
    sf::Vector2f gameResolution;
};

}

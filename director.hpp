#pragma once

#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "scene.hpp"

namespace game {

class Director {
public:
    Director();
    void run(sf::RenderWindow &window);
private:
    std::shared_ptr<Scene> _scene;
};

}

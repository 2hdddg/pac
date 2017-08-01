#pragma once

#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "util/resources.hpp"
#include "scenes/scenetransition.hpp"

namespace game {

class Director {
public:
    Director(std::shared_ptr<Resources> resources);
    void run(sf::RenderWindow &window);
private:
    void approxFps(long delta);

    SceneTransition _sceneTransition;
    double          _averageFps;
    bool            _showFps;
    sf::Text        _fpsText;
};

}

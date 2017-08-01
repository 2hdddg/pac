#pragma once

#include <functional>
#include <memory>
#include <SFML/Graphics.hpp>

namespace game {

class SceneTransition;

class Scene {
public:
    virtual ~Scene() {}
    virtual void event(sf::Event &event,
                       SceneTransition *transition) = 0;
    virtual void update(long delta,
                        SceneTransition *transition) = 0;
    virtual void render(sf::RenderWindow &window) = 0;
};

}

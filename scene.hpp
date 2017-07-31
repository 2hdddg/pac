#pragma once

#include <functional>
#include <memory>
#include <SFML/Graphics.hpp>

namespace game {

class Scene;
typedef std::function<void (std::shared_ptr<Scene>)> ChangeSceneFunc;

class Scene {
public:
    virtual ~Scene() {}
    virtual void event(sf::Event &event) = 0;
    virtual void update(sf::Time &elapsed,
                        ChangeSceneFunc changeScene) = 0;
    virtual void render(sf::RenderWindow &window) = 0;
};

}

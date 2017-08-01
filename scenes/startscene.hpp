#pragma once

#include <SFML/Graphics.hpp>
#include "util/animator.hpp"
#include "scene.hpp"
#include "scenes/scenetransition.hpp"
#include "util/resources.hpp"
#include "widgets/menu.hpp"
#include "widgets/blinkingtext.hpp"

namespace game {

class StartScene : public Scene {
public:
    StartScene(
        std::shared_ptr<Resources> resources);
    virtual ~StartScene();
    virtual void event(sf::Event &event,
                       SceneTransition *transition);
    virtual void update(long delta,
                       SceneTransition *transition);
    virtual void render(sf::RenderWindow &window);

private:
    int                        _num;
    std::shared_ptr<Resources> _resources;
    Menu                       _menu;
    BlinkingText               _press_key;
};

}

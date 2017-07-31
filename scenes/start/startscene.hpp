#pragma once

#include <SFML/Graphics.hpp>
#include "util/animator.hpp"
#include "scene.hpp"

namespace game {

class StartScene : public Scene {
public:
    StartScene();
    virtual ~StartScene();
    virtual void event(sf::Event &event);
    virtual void update(sf::Time &elapsed,
                        ChangeSceneFunc changeScene);
    virtual void render(sf::RenderWindow &window);

private:
    void startNewGame(ChangeSceneFunc changeScene);

private:
    sf::Font _font;
    sf::Text _press_any_key;

    Animator _animator;

    bool _showing_press;
    bool _start_game;
};

}

#include <iostream>

#include "scenes/start/startscene.hpp"
#include "scenes/game/gamescene.hpp"

namespace game {

StartScene::StartScene()
{
    std::string fontPath = "../resources/fonts/Roboto-Bold.ttf";
    if (!_font.loadFromFile(fontPath)) {
        throw "Unable to load font";
    }

    _press_any_key.setFont(_font);
    _press_any_key.setString("Press any key");
    _press_any_key.setCharacterSize(24);
    _press_any_key.setPosition(sf::Vector2f(30, 100));

    _showing_press = false;
    _animator.set(0, 0);
    _start_game = false;
}

StartScene::~StartScene()
{
}

void StartScene::event(sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed) {
        _start_game = true;
    }
}

void StartScene::update(sf::Time &elapsed,
                        ChangeSceneFunc changeScene)
{
    _animator.update(elapsed.asMicroseconds(),
                     0,
                     [this]() {
                        _showing_press = !_showing_press;
                        _animator.set(1000000, 0);
                     });

    if (_start_game && changeScene) {
        startNewGame(changeScene);
    }
}

void StartScene::render(sf::RenderWindow &window)
{
    if (_showing_press) {
        window.draw(_press_any_key);
    }
}

void StartScene::startNewGame(ChangeSceneFunc changeScene)
{
    auto maze = std::make_unique<Maze>(4, 3);
    auto gameScene = std::make_shared<GameScene>(std::move(maze));

    /* Transition to game */
    changeScene(gameScene);
}

}

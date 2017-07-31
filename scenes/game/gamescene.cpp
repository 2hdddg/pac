#include <iostream>

#include "scenes/game/gamescene.hpp"

namespace game {

GameScene::GameScene(std::unique_ptr<Maze> maze) :
    _maze(std::move(maze))
{
}

GameScene::~GameScene()
{
}

void GameScene::event(sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Up:
                _maze->hero->start(North);
                break;
            case sf::Keyboard::Down:
                _maze->hero->start(South);
                break;
            case sf::Keyboard::Left:
                _maze->hero->start(West);
                break;
            case sf::Keyboard::Right:
                _maze->hero->start(East);
                break;
            default:
                break;
        }
    }
    else if (event.type == sf::Event::KeyReleased) {
        switch (event.key.code) {
            case sf::Keyboard::Up:
            case sf::Keyboard::Down:
            case sf::Keyboard::Left:
            case sf::Keyboard::Right:
                _maze->hero->stop();
                break;
            default:
                break;
        }
    }
}

void GameScene::update(sf::Time &elapsed,
                       ChangeSceneFunc changeScene)
{
    _maze->update(elapsed);
}

void GameScene::render(sf::RenderWindow &window)
{
    _maze->draw(window);
}

}


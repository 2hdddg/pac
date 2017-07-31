#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "scene.hpp"
#include "game/maze.hpp"

namespace game {

class GameScene : public Scene {
public:
    GameScene(std::unique_ptr<Maze> maze);
    virtual ~GameScene();
    virtual void event(sf::Event &event);
    virtual void update(sf::Time &elapsed,
                        ChangeSceneFunc changeScene);
    virtual void render(sf::RenderWindow &window);
private:
    std::unique_ptr<Maze> _maze;
};

}

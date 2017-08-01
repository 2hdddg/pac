#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "scene.hpp"
#include "scenes/scenetransition.hpp"
#include "util/resources.hpp"
#include "game/maze.hpp"
#include "game/hero.hpp"
#include "game/monster.hpp"
#include "game/controller.hpp"
#include "util/camera.hpp"
#include "game/playerview.hpp"

namespace game {

class GameScene : public Scene {
public:
    GameScene(
        std::shared_ptr<Resources> resources,
        std::shared_ptr<Game> game);
    virtual ~GameScene();
    virtual void event(sf::Event &event,
                       SceneTransition *transition);
    virtual void update(long delta,
                       SceneTransition *transition);
    virtual void render(sf::RenderWindow &window);
private:
    void addPlayerView(std::shared_ptr<Hero> hero,
                       sf::Vector2f &screenSize,
                       Controller::Layout layout,
                       sf::FloatRect &viewArea);

    std::shared_ptr<Resources>               _resources;
    std::shared_ptr<Game>                    _game;
    std::vector<std::shared_ptr<PlayerView>> _playerViews;
};

}

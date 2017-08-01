#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "util/camera.hpp"
#include "util/resources.hpp"
#include "game/game.hpp"
#include "game/controller.hpp"

namespace game {

class PlayerView {
public:
    PlayerView(std::shared_ptr<Resources> resources,
               std::shared_ptr<Game> game,
               std::shared_ptr<Hero> hero,
               std::unique_ptr<Controller> controller,
               sf::Vector2f &screenSize,
               sf::FloatRect &viewArea);
    ~PlayerView();

    void event(sf::Event &event);
    void update(long delta);
    void render(sf::RenderWindow &window);
private:
    std::shared_ptr<Game>       _game;
    std::shared_ptr<Hero>       _hero;
    std::unique_ptr<Controller> _controller;
    std::unique_ptr<Camera>     _camera;
    sf::Text                    _scoreText;
    sf::View                    _view;
    sf::Vertex                  _borders[8];
    sf::Transform               _transform;
    sf::Text                    _gameOverText;
};

}

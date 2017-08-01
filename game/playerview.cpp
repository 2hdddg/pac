#include "game/playerview.hpp"
#include <iostream>

#define D(x)

namespace game {

const int headerHeight = 30;

PlayerView::PlayerView(std::shared_ptr<Resources> resources,
                       std::shared_ptr<Game> game,
                       std::shared_ptr<Hero> hero,
                       std::unique_ptr<Controller> controller,
                       sf::Vector2f &screenSize,
                       sf::FloatRect &viewArea) :
    _game(game),
    _hero(hero),
    _controller(std::move(controller))
{
    D(std::cout << typeid(*this).name() << "::constructor\n");

    _camera = std::make_unique<Camera>(
                     game->maze->getSizeInPixels(),
                     sf::Vector2f(viewArea.width,
                                  viewArea.height - headerHeight));
    _view.setViewport(sf::FloatRect(
                        viewArea.left / screenSize.x,
                       (viewArea.top + headerHeight) / screenSize.y,
                        viewArea.width / screenSize.x,
                       (viewArea.height - headerHeight) / screenSize.y));
    _view.setSize(sf::Vector2f(
                        viewArea.width,
                        viewArea.height - headerHeight));

    _scoreText.setFont(resources->standardFont);
    _scoreText.setCharacterSize(16);
    _scoreText.setPosition(sf::Vector2f(viewArea.left + 3,
                                        viewArea.top + 3));
    _gameOverText.setFont(resources->standardFont);
    _gameOverText.setCharacterSize(40);
    _gameOverText.setPosition(sf::Vector2f(viewArea.left + 20,
                                           viewArea.top + 20));
    _gameOverText.setString("GAME OVER");

    /* Upper left, Upper right, Lower left, Lower right */
    auto ul = sf::Vector2f(viewArea.left + 1,
                           viewArea.top + headerHeight);
    auto ur = sf::Vector2f(ul.x + viewArea.width - 1,
                           ul.y);
    auto ll = sf::Vector2f(ul.x,
                           ul.y + viewArea.height -
                           headerHeight - 1);
    auto lr = sf::Vector2f(ur.x,
                           ll.y);

    _borders[0] = ul;
    _borders[1] = ur;

    _borders[2] = ur;
    _borders[3] = lr;

    _borders[4] = lr;
    _borders[5] = ll;

    _borders[6] = ll;
    _borders[7] = ul;
}

PlayerView::~PlayerView()
{
    D(std::cout << typeid(*this).name() << "::destructor\n");
}

void PlayerView::event(sf::Event &event)
{
    _controller->event(event);
}

void PlayerView::update(long delta)
{
    _scoreText.setString(std::to_string(_hero->pills) +
                         "   " +
                         std::to_string(_hero->lives));
    _view.setCenter(_camera->centerAt(_hero->pos));
}

void PlayerView::render(sf::RenderWindow &window)
{
    window.draw(_scoreText);

    window.setView(_view);
    _game->maze->render(window, _transform);
    for (auto monster : _game->monsters) {
        monster->render(window, _transform);
    }
    for (auto hero : _game->heroes) {
        auto isMe = _hero == hero;
        hero->render(window, _transform, isMe);
    }
    window.setView(window.getDefaultView());
    window.draw(_borders, 8, sf::Lines);

    if (_hero->isDead()) {
        window.draw(_gameOverText);
    }
}

}

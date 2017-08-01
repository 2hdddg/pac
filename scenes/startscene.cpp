#include <iostream>

#include "scenes/startscene.hpp"
#include "game/levels.hpp"

#define D(x)

namespace game {

StartScene::StartScene(
    std::shared_ptr<Resources> resources) :
    _num(0),
    _resources(resources),
    _menu(),
    _press_key(resources, "Start game", 24, 1000000)
{
    D(std::cout << typeid(*this).name() << "::constructor\n");

    std::unique_ptr<MenuItem> menuItem;
    menuItem = std::make_unique<TextMenuItem>([this]() {
                                                 _num = 1;
                                              },
                                              _resources,
                                              "1 player");
    _menu.add(std::move(menuItem));
    menuItem = std::make_unique<TextMenuItem>([this]() {
                                                 _num = 2;
                                              },
                                              _resources,
                                              "2 players");
    _menu.add(std::move(menuItem));
    auto pos = sf::Vector2f(0, 0);
    _menu.setPos(pos);
    _menu.prepare();

    _press_key.setPosition(sf::Vector2f(30, 100));
}

StartScene::~StartScene()
{
    D(std::cout << typeid(*this).name() << "::destructor\n");
}

void StartScene::event(sf::Event &event,
                       SceneTransition *transition)
{
    if (_menu.processEvent(event)) {
        return;
    }
}

void StartScene::update(long delta,
                        SceneTransition *transition)
{
    if (_num) {
        auto game = std::make_shared<Game>(_resources, 1);
        while (_num--) {
            game->addLocalPlayer();
        }
        transition->toGame(game);
    }

    _menu.update(delta);
    _press_key.update(delta);
}

void StartScene::render(sf::RenderWindow &window)
{
    _menu.render(window);
    _press_key.render(window);
}

}

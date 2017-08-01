#include <memory>
#include <iostream>

#include "scenes/gamescene.hpp"
#include "util/tileset.hpp"
#include "game/playerview.hpp"

#define D(x)

namespace game {

GameScene::GameScene(std::shared_ptr<Resources> resources,
                     std::shared_ptr<Game> game) :
    _resources(resources),
    _game(game)
{
    D(std::cout << typeid(*this).name() << "::constructor\n");

    auto screenSize = resources->gameResolution;

    if (game->numLocalPlayers > 2) {
        throw "Too many players";
    }

    auto splitted = sf::Vector2f(screenSize.x / game->numLocalPlayers,
                                 screenSize.y);
    auto viewArea = sf::FloatRect(0, 0,
                                  screenSize.x / game->numLocalPlayers,
                                  splitted.y);
    addPlayerView(game->heroes[0], screenSize,
                  Controller::Layout::Arrows, viewArea);

    if (game->numLocalPlayers > 1) {
        viewArea.left = viewArea.width;
        addPlayerView(game->heroes[1], screenSize,
                      Controller::Layout::AWSD, viewArea);
    }
}

GameScene::~GameScene()
{
    D(std::cout << typeid(*this).name() << "::destructor\n");
}

void GameScene::addPlayerView(std::shared_ptr<Hero> hero,
                              sf::Vector2f &screenSize,
                              Controller::Layout layout,
                              sf::FloatRect &viewArea)
{
    auto controller = std::make_unique<Controller>(layout, hero);
    auto playerView = std::make_shared<PlayerView>(
                                       _resources,
                                       _game,
                                       hero,
                                       std::move(controller),
                                       screenSize,
                                       viewArea);
    _playerViews.push_back(playerView);
}

void GameScene::event(sf::Event &event,
                      SceneTransition *transition)
{
    for (auto&& playerView : _playerViews) {
        playerView->event(event);
    }
}

void GameScene::update(long delta,
                       SceneTransition *transition)
{
    switch (_game->update(delta)) {
        case Game::Transition::LevelComplete:
            transition->toLevelCompleted(_game);
            break;
        case Game::Transition::GameOver:
            transition->toStart();
            break;
        case Game::Transition::None:
        default:
            break;
    }
    for (auto&& playerView : _playerViews) {
        playerView->update(delta);
    }
}

void GameScene::render(sf::RenderWindow &window)
{
    for (auto&& playerView : _playerViews) {
        playerView->render(window);
    }
}

}


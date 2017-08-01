#include "scenes/levelcompletescene.hpp"

namespace game {

const int64_t WAIT_UNTIL_CONTINUE = 1000*1000*1;

LevelCompleteScene::LevelCompleteScene(
    std::shared_ptr<Resources> resources,
    std::shared_ptr<Game> game,
    std::shared_ptr<Scene> background) :
    _game(game),
    _background(background),
    _continue(resources, "Continue..", 30, 1000000),
    _aggregated(0)
{
    _continue.setPosition(sf::Vector2f(110, 120));
}

LevelCompleteScene::~LevelCompleteScene()
{
    D(std::cout << typeid(*this).name() << "::destructor\n");
}

void LevelCompleteScene::event(sf::Event &event,
                       SceneTransition *transition)
{
    /* Wait a bit until accepting keyboard event */
    if (_aggregated > WAIT_UNTIL_CONTINUE &&
        event.type == sf::Event::KeyPressed) {
        _game->nextLevel();
        transition->toGame(_game);
    }
}

void LevelCompleteScene::update(long delta,
                                SceneTransition *transition)
{
    _aggregated += delta;
    if (_aggregated > WAIT_UNTIL_CONTINUE) {
        _continue.update(delta);
    }
}

void LevelCompleteScene::render(sf::RenderWindow &window)
{
    _background->render(window);
    if (_aggregated > WAIT_UNTIL_CONTINUE) {
        _continue.render(window);
    }
}

}

#pragma once

#include <memory>

#include <SFML/Graphics.hpp>
#include "scene.hpp"
#include "util/resources.hpp"

#include "game/game.hpp"


namespace game {


class SceneTransition {
public:
    SceneTransition(
        std::shared_ptr<Resources> resources) :
        _current(0),
        _next(0)
    {
        _resources = resources;
        toStart();
    }

    std::shared_ptr<Scene> getNext() {
        if (_next) {
            _current = _next;
            _next = 0;
        }
        return _current;
    }

    void toStart();
    void toGame(std::shared_ptr<Game> game);
    void toLevelCompleted(std::shared_ptr<Game> game);
    void toNextLevel(std::shared_ptr<Game> game);

private:
    std::shared_ptr<Resources> _resources;
    std::shared_ptr<Scene>     _current;
    std::shared_ptr<Scene>     _next;
};

}

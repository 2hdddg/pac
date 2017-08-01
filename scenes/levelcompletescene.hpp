#pragma once

#include "scene.hpp"
#include "util/resources.hpp"
#include "widgets/blinkingtext.hpp"
#include "scenes/gamescene.hpp"

#define D(x)

namespace game {

class LevelCompleteScene : public Scene {
public:
    LevelCompleteScene(
        std::shared_ptr<Resources> resources,
        std::shared_ptr<Game> game,
        std::shared_ptr<Scene> background);

    virtual ~LevelCompleteScene();
    virtual void event(sf::Event &event,
                       SceneTransition *transition);
    virtual void update(long delta,
                       SceneTransition *transition);
    virtual void render(sf::RenderWindow &window);

private:
    std::shared_ptr<Game>      _game;
    std::shared_ptr<Scene>     _background;
    BlinkingText               _continue;
    int64_t                    _aggregated;
};

}

#include "scenes/scenetransition.hpp"

#include "scenes/startscene.hpp"
#include "scenes/gamescene.hpp"
#include "scenes/levelcompletescene.hpp"

namespace game {

void SceneTransition::toStart()
{
    _next = std::make_shared<StartScene>(_resources);
}

void SceneTransition::toGame(std::shared_ptr<Game> game)
{
    _next  = std::make_shared<GameScene>(_resources, game);
}

void SceneTransition::toLevelCompleted(std::shared_ptr<Game> game)
{
    _next = std::make_shared<LevelCompleteScene>(_resources,
                                                 game,
                                                 _current);
}

}

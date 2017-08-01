#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "util/resources.hpp"

#include "game/levels.hpp"
#include "game/maze.hpp"
#include "game/hero.hpp"
#include "game/monster.hpp"

namespace game {


class Game {
public:
    enum Transition {
        None,
        LevelComplete,
        GameOver,
    };

    Game(std::shared_ptr<Resources> resources, int mazeId);
    void addLocalPlayer();

    void nextLevel();

    Transition update(long delta);

    std::shared_ptr<Maze>                 maze;
    std::vector<std::shared_ptr<Hero>>    heroes;
    std::vector<std::shared_ptr<Monster>> monsters;
    unsigned int                          numLocalPlayers;

private:
    void loadMaze(struct MazeDefinition *definition);
    void addMonsters(struct MazeDefinition *definition);
    void loadLevel();

    sf::Texture _monsterTexture;
    sf::Texture _heroTexture;
    int         _mazeId;
};

}

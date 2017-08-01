#include "game/game.hpp"

#include "util/tileset.hpp"
#include "game/levels.hpp"

namespace game {

static void applyAnimations(
        sf::Texture &texture, int size, int num,
        std::function<void (int i, Direction d,
                            std::unique_ptr<sf::Sprite> s)> apply)
{
    auto tileset         = Tileset(texture, size, size);
    auto numStyles       = tileset.rows;
    auto numPerDirection = tileset.cols / 4;

    for (int i = 0; i < num; i++) {
        /* Row is style */
        auto row = i % numStyles;
        /* Directions */
        for (int d = 0; d < 4; d++) {
            /* Animation per direction */
            for (int a = 0; a < numPerDirection; a++) {
                auto col = d * numPerDirection + a;
                auto sprite = tileset.spriteByPos(col, row);

                apply(i, (Direction)d, std::move(sprite));
            }
        }
    }
}

struct MazeDefinition *getMazeDefinition(int id) {
    return &level2;
}

Game::Game(std::shared_ptr<Resources> resources,
           int mazeId) :
           numLocalPlayers(0),
           _mazeId(mazeId)
{
    /* Load textures */
    std::string path = "../resources/tiles/monsters.png";
    _monsterTexture.loadFromFile(path);
    path = "../resources/tiles/heroes.png";
    _heroTexture.loadFromFile(path);
    loadLevel();
}

void Game::addLocalPlayer() {
    auto hero = std::make_shared<Hero>(maze->heroSpawn, East);
    numLocalPlayers++;

    /* Whenever something is consumed in a cell */
    hero->setConsumedCallback(
        [this](Cell *cell, int x) {
            maze->consumed(x);
        });

    applyAnimations(_heroTexture, 32, 1,
        [this, hero](int i, Direction d, std::unique_ptr<sf::Sprite> s){
            hero->setSprite(d, std::move(s));
        });

    heroes.push_back(hero);
}

void Game::loadLevel()
{
    auto definition = getMazeDefinition(_mazeId);
    loadMaze(definition);
    monsters.clear();
    addMonsters(definition);
    for (auto hero : heroes) {
        hero->reset(maze->heroSpawn, East);
    }
}

void Game::nextLevel()
{
    _mazeId++;
    loadLevel();
}

Game::Transition Game::update(long delta)
{
    for (auto monster : monsters) {
        monster->update(delta);
    }

    unsigned int numDead = 0;
    for (auto hero : heroes) {
        hero->update(delta);
        if (hero->isDead()) {
            numDead++;
        }
    }

    if (maze->isEmpty()) {
        return LevelComplete;
    }

    if (numDead == heroes.size()) {
        /* All heroes dead, end the game */
        return GameOver;
    }
    if (numDead == numLocalPlayers) {
        /* All local players dead */
        return GameOver;
    }

    return Game::Transition::None;
}

void Game::loadMaze(struct MazeDefinition *definition) {
    maze = std::make_shared<Maze>(&level2);
}

void Game::addMonsters(struct MazeDefinition *definition)
{
    for (unsigned int i = 0; i < definition->numMonsters; i++) {
        auto monster = std::make_shared<Monster>(maze->monsterSpawn,
                                                 North, heroes);
        monsters.push_back(monster);
    }

    applyAnimations(_monsterTexture, 32, definition->numMonsters,
        [this](int i, Direction d, std::unique_ptr<sf::Sprite> s){
            monsters[i]->setSprite(d, std::move(s));
        });
}

}

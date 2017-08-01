#pragma once

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "util/animator.hpp"
#include "game/cell.hpp"
#include "game/levels.hpp"
#include "game/constants.hpp"


namespace game {

class Maze {
public:
    Maze(struct MazeDefinition *definition);
    void event(sf::Event &event);
    void render(sf::RenderTarget &target,
                const sf::Transform &transform);

    const sf::Vector2f getSizeInPixels() const;

    Cell *heroSpawn;
    Cell *monsterSpawn;

    int consumed(int x) {
        _pills--;
        return _pills;
    }

    bool isEmpty() {
        return _pills <= 0;
    }

private:
    /* Connects all cells to it's neighbours and
     * assigns them their position  */
    static void connectCells(std::vector<Cell> &cells,
                             unsigned int width,
                             unsigned int height);
    /* Assign tiles to cells according to the definition. */
    void assignTiles(const struct MazeDefinition *definition,
                     sf::Texture &texture);
    /* Connects teleporting cells */
    void connectTeleports(const struct MazeDefinition *definition);

    Cell* getCell(unsigned int x, unsigned int y) {
        return &_cells[(y * _width) + x];
    }

    unsigned int      _width;
    unsigned int      _height;
    std::vector<Cell> _cells;
    sf::Texture       _texture;

    int               _pills;
};

}

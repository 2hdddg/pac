#include <memory>
#include <iostream>
#include "util/tileset.hpp"
#include "game/maze.hpp"

namespace game {

Maze::Maze(struct MazeDefinition *definition) :
    _width(definition->size.x),
    _height(definition->size.y),
    _cells(definition->size.x * definition->size.y, Cell()),
    _pills(0)
{
    std::string path = "../resources/tiles/maze.png";
    if (!_texture.loadFromFile(path)) {
        throw "Unable to load maze tileset";
    }

    connectCells(_cells, _width, _height);
    assignTiles(definition, _texture);
    connectTeleports(definition);

    heroSpawn = getCell(definition->heroSpawn.x,
                        definition->heroSpawn.y);
    monsterSpawn = getCell(definition->monsterSpawn.x,
                           definition->monsterSpawn.y);
}

void Maze::connectTeleports(const struct MazeDefinition *definition)
{
    for (unsigned int i = 0; i < definition->numTeleports; i++) {
        auto teleport = &definition->teleports[i];
        auto from     = getCell(teleport->from.x, teleport->from.y);
        auto to       = getCell(teleport->to.x, teleport->to.y);

        from->connect(teleport->direction, to, Teleport);
        /* Assume all is bidirectional */
        to->connect(oppositeDirection[teleport->direction], from,
                    Teleport);
    }
}

void Maze::connectCells(std::vector<Cell> &cells,
                        unsigned int width,
                        unsigned int height)
{
    auto pos = sf::Vector2f(0, 0);

    for (unsigned int y = 0; y < height; y++) {
        pos.x = 0;
        for (unsigned int x = 0; x < width; x++) {
            Cell &cell = cells[(y * width) + x];

            cell.pos = pos;

            if (y > 0) {
                cell.connect(North, &cells[((y - 1) * width) + x],
                             Walk);
            }

            if (y < (height - 1)) {
                cell.connect(South, &cells[((y + 1) * width) + x],
                             Walk);
            }

            if (x > 0) {
                cell.connect(West, &cells[(y * width) + (x - 1)],
                             Walk);
            }

            if (x < (width - 1)) {
                cell.connect(East, &cells[(y * width) + (x + 1)],
                             Walk);
            }
            pos.x += 32;
        }
        pos.y += 32;
    }
}

void Maze::assignTiles(const struct MazeDefinition *definition,
                       sf::Texture &texture)
{
    auto tileset = Tileset(texture, 32, 32);

    for (unsigned int i = 0; i < _width * _height; i++) {
        auto tileId = definition->tiles[i];

        if (tileId > 0) {
            tileId--;
            auto tile = tileset.spriteByOffset(tileId);
            _cells[i].setBackgroundTile(std::move(tile));
            _cells[i].disallow();
        }

        if (tileId == -1) {
            _cells[i].setContent(Pill);
            _pills++;
            auto tile = tileset.spriteByOffset(23);
            _cells[i].setContentTile(std::move(tile));
        }
    }
}

void Maze::render(sf::RenderTarget &target,
                  const sf::Transform &transform)
{
    for (unsigned int i = 0; i < _width * _height; i++) {
        auto cell = &_cells[i];

        if (cell->backgroundTile) {
            target.draw(*cell->backgroundTile, transform);
        }

        if (cell->contentTile) {
            target.draw(*cell->contentTile, transform);
        }
    }
}

const sf::Vector2f Maze::getSizeInPixels() const
{
    return sf::Vector2f(_width * 32, _height * 32);
}

}

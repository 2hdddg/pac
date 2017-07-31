#include <memory>
#include "game/maze.hpp"

namespace game {

Maze::Maze(unsigned int width, unsigned int height) :
    _width(width),
    _height(height),
    _cells(width * height, Cell())
{
    auto pos = sf::Vector2f(0, 0);

    /* Connect all cells to it's neighbours */
    for (unsigned int y = 0; y < height; y++) {
        pos.x = 0;
        for (unsigned int x = 0; x < width; x++) {
            Cell &cell = _cells[(y * width) + x];

            cell.pos = pos;

            if (y > 0) {
                cell.connectCell(North, &_cells[((y - 1) * width) + x]);
            }

            if (y < (height - 1)) {
                cell.connectCell(South, &_cells[((y + 1) * width) + x]);
            }

            if (x > 0) {
                cell.connectCell(West, &_cells[(y * width) + (x - 1)]);
            }

            if (x < (width - 1)) {
                cell.connectCell(East, &_cells[(y * width) + (x + 1)]);
            }
            pos.x += 32;
        }
        pos.y += 32;
    }


    /* Testing */
    _cells[1].raiseWall(South);
    _cells[2].raiseWall(South);
    _cells[4].raiseWall(East);
    _cells[7].raiseWall(West);
    _cells[9].raiseWall(North);
    _cells[10].raiseWall(North);

    hero = std::make_unique<Hero>(&_cells[0], East);
}

void Maze::update(sf::Time &elapsed)
{
    hero->update(elapsed);
}

void Maze::draw(sf::RenderTarget &target)
{
    auto hor_wall = sf::RectangleShape(sf::Vector2f(30, 2));
    auto ver_wall = sf::RectangleShape(sf::Vector2f(2, 30));

    for (unsigned int i = 0; i < _width * _height; i++) {
        auto cell = _cells[i];

        if (cell.hasWall(North)) {
            hor_wall.setPosition(cell.pos);
            target.draw(hor_wall);
        }

        if (cell.hasWall(South)) {
            hor_wall.setPosition(sf::Vector2f(cell.pos.x, cell.pos.y + 30));
            target.draw(hor_wall);
        }

        if (cell.hasWall(West)) {
            ver_wall.setPosition(cell.pos);
            target.draw(ver_wall);
        }

        if (cell.hasWall(East)) {
            ver_wall.setPosition(sf::Vector2f(cell.pos.x + 30, cell.pos.y));
            target.draw(ver_wall);
        }
    }

    sf::CircleShape circle(12);
    circle.setPosition(sf::Vector2f(hero->pos.x + 3,
                                    hero->pos.y + 3));

    sf::CircleShape dot(2);
    dot.setFillColor(sf::Color(150, 50, 250));
    dot.setPosition(sf::Vector2f(hero->pos.x + 16 - 2,
                                 hero->pos.y + 16 - 2));
    int offset = 32 * hero->offset;
    switch (hero->direction) {
        case North:
            dot.move(0, -8);
            break;
        case South:
            dot.move(0, 8);
            break;
        case East:
            circle.move(-offset, 0);
            dot.move(-offset + 8, 0);
            break;
        case West:
            circle.move(offset, 0);
            dot.move(offset - 8, 0);
            break;
    }
    target.draw(circle);
    target.draw(dot);
}


}

#pragma once

#include <SFML/Graphics.hpp>

namespace game {

enum Direction {
    North,
    South,
    West,
    East,
};

class Cell {
public:
    void connectCell(Direction direction, Cell *cell);
    void raiseWall(Direction direction);
    bool canReach(Direction direction, Cell *cell);

    Direction opposite(Direction direction) {
        switch (direction) {
            case North:
                return South;
            case South:
                return North;
            case West:
                return East;
            case East:
                return West;
        }
        throw "Invalid direction";
    }


    bool hasWall(Direction direction) {
        return _neighbours[direction] == 0;
    }

    Cell* getNeighbour(Direction direction) {
        return _neighbours[direction];
    }

    sf::Vector2f pos;

private:
    Cell* _neighbours[4];
    unsigned int _x;
    unsigned int _y;
};

}

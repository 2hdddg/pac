#pragma once

#include <SFML/Graphics.hpp>

namespace game {

/* Do not change order! */
enum Direction {
    South,
    East,
    North,
    West,
};

const Direction clockwiseDirection[] = {
    West,
    South,
    East,
    North,
};

const Direction oppositeDirection[] = {
    North,
    West,
    South,
    East,
};

}

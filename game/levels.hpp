#pragma once

#include "game/directions.hpp"


struct Vector2 {
    unsigned int x;
    unsigned int y;
};

struct Teleport {
    struct Vector2  from;
    game::Direction direction;
    struct Vector2  to;
};

struct MazeDefinition {
    struct Vector2  size;
    struct Vector2  heroSpawn;
    struct Vector2  monsterSpawn;
    unsigned int    numMonsters;
    unsigned int    numTeleports;
    struct Teleport *teleports;
    char            tiles[];
};

extern struct MazeDefinition level1;
extern struct MazeDefinition level2;

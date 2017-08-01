#include "game/levels.hpp"

using namespace game;

struct MazeDefinition level1 = {
    .size = {
        .x = 3,
        .y = 4,
    },
    .heroSpawn = {
        .x = 1,
        .y = 1,
    },
    .monsterSpawn = {
        .x = 2,
        .y = 1,
    },
    .numMonsters = 0,
    .numTeleports = 0,
    .teleports = 0,
    .tiles = {
         4,  1,  3,
         2, -1,  2,
         2, -1,  2,
         5,  1,  6,
    },
};

struct Teleport level2Teleports[] = {
    {
        .from = {
            .x = 0,
            .y = 12,
        },
        .direction = West,
        .to = {
            .x = 24,
            .y = 12,
        },
    },
};

struct MazeDefinition level2 = {
    .size = {
        .x = 25,
        .y = 25,
    },
    .heroSpawn = {
        .x = 1,
        .y = 1,
    },
    .monsterSpawn = {
        .x = 10,
        .y = 1,
    },
    .numMonsters = 3,
    .numTeleports = sizeof(level2Teleports) / sizeof(struct Teleport),
    .teleports = level2Teleports,
    .tiles = {
         4,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 12,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  3,
         2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  2,
         2, -1, 15, 19, 19, 16, -1, 15, 19, 19, 16, -1,  2, -1, 15, 19, 19, 16, -1, 15, 19, 19, 16, -1,  2,
         2, -1, 20, 23, 23, 22, -1, 20, 23, 23, 22, -1,  2, -1, 20, 23, 23, 22, -1, 20, 23, 23, 22, -1,  2,
         2, -1, 17, 21, 21, 18, -1, 17, 21, 21, 18, -1,  7, -1, 17, 21, 21, 18, -1, 17, 21, 21, 18, -1,  2,
         2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  2,
         2, -1, 10,  1,  1,  8, -1,  9, -1, 10,  1,  1, 12,  1,  1,  8, -1,  9, -1, 10,  1,  1,  8, -1,  2,
         2, -1, -1, -1, -1, -1, -1,  2, -1, -1, -1, -1,  2, -1, -1, -1, -1,  2, -1, -1, -1, -1, -1, -1,  2,
         5,  1,  1,  1,  1,  3, -1, 13,  1,  1,  8, -1,  7, -1, 10,  1,  1, 11, -1,  4,  1,  1,  1,  1,  6,
         0,  0,  0,  0,  0,  2, -1,  2, -1, -1, -1, -1, -1, -1, -1, -1, -1,  2, -1,  2,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  2, -1,  2, -1, 15, 19, 19, 19, 19, 19, 16, -1,  2, -1,  2,  0,  0,  0,  0,  0,
         1,  1,  1,  1,  1,  6, -1,  7, -1, 20, 23, 23, 23, 23, 23, 22, -1,  7, -1,  5,  1,  1,  1,  1,  1,
         0, -1, -1, -1, -1, -1, -1, -1, -1, 20, 23, 23, 23, 23, 23, 22, -1, -1, -1, -1, -1, -1, -1, -1,  0,
         1,  1,  1,  1,  1,  3, -1,  9, -1, 20, 23, 23, 23, 23, 23, 22, -1,  9, -1,  4,  1,  1,  1,  1,  1,
         0,  0,  0,  0,  0,  2, -1,  2, -1, 17, 21, 21, 21, 21, 21, 18, -1,  2, -1,  2,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0,  2, -1,  2, -1, -1, -1, -1, -1, -1, -1, -1, -1,  2, -1,  2,  0,  0,  0,  0,  0,
         4,  1,  1,  1,  1,  6, -1,  7, -1, 10,  1,  1, 12,  1,  1,  8, -1,  7, -1,  5,  1,  1,  1,  1,  3,
         2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  2,
         2, -1, 10,  1,  1,  3, -1, 10,  1,  1,  8, -1,  7, -1, 10,  1,  1,  8, -1,  4,  1,  1,  8, -1,  2,
         2, -1, -1, -1, -1,  2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  2, -1, -1, -1, -1,  2,
        13,  1,  1,  8, -1,  7, -1,  9, -1, 10,  1,  1, 12,  1,  1,  8, -1,  9, -1,  7, -1, 10,  1,  1, 11,
         2, -1, -1, -1, -1, -1, -1,  2, -1, -1, -1, -1,  2, -1, -1, -1, -1,  2, -1, -1, -1, -1, -1, -1,  2,
         2, -1, 10,  1,  1,  1,  1, 14,  1,  1,  8, -1,  7, -1, 10,  1,  1, 14,  1,  1,  1,  1,  8, -1,  2,
         2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  2,
         5,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  6,
    },
};

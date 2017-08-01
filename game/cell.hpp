#pragma once

#include <SFML/Graphics.hpp>
#include "game/directions.hpp"
#include "game/pilleatingfx.hpp"

namespace game {

class Cell {
public:
    struct Transition {
        /* WHen not null there is some kind of valid transition
         * from this cell to another in the current direction,
         * check type for what type of transition and restrictions
         * on who can use the transition. */
        Cell *cell;
        int   transition;
    };

    Cell();
    Cell(const Cell &cell);

    /* Connects this cell to another cell and creating
     * a transition of specified type between them.
     */
    void connect(Direction direction, Cell *cell,
                 int transition);

    /* Marks this cell as a cell that cannot be
     * transitioned into. This cells neighbours are
     * changed so that they cannot transition to this
     * cell.
     */
    void disallow();

    struct Transition& move(Direction direction) {
        return _neighbours[direction];
    }

    bool canReach(Direction direction, Cell *cell);

    void setBackgroundTile(std::unique_ptr<sf::Sprite> tile);
    void setContentTile(std::unique_ptr<sf::Sprite> tile);

    void setContent(int c) {
        _content = c;
    }

    int consumeContent(PillEatingFx &fx) {
        auto c = _content;

        _content = 0;

        if (contentTile) {
            fx.add(std::move(contentTile));
            contentTile = 0;
        }

        return c;
    }

    std::unique_ptr<sf::Sprite> backgroundTile;
    std::unique_ptr<sf::Sprite> contentTile;
    sf::Vector2f pos;

private:
    void disallowDirection(Direction d);

    struct Transition _neighbours[4];
    int               _content;
};

}

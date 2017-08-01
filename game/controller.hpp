#pragma once

#include "game/hero.hpp"


namespace game {

class Controller {
public:
    enum Layout {
        Arrows,
        AWSD,
    };

    struct KeyMap {
        sf::Keyboard::Key northKey;
        sf::Keyboard::Key southKey;
        sf::Keyboard::Key eastKey;
        sf::Keyboard::Key westKey;
    };

    Controller(Layout layout,
               std::shared_ptr<Hero> hero) :
        _hero(hero),
        _pressed(0)
    {
        switch (layout) {
            case Arrows:
                _keyMap.northKey = sf::Keyboard::Up;
                _keyMap.southKey = sf::Keyboard::Down;
                _keyMap.eastKey = sf::Keyboard::Right;
                _keyMap.westKey = sf::Keyboard::Left;
                break;
            case AWSD:
                _keyMap.northKey = sf::Keyboard::W;
                _keyMap.southKey = sf::Keyboard::S;
                _keyMap.eastKey = sf::Keyboard::D;
                _keyMap.westKey = sf::Keyboard::A;
                break;
            default:
                throw "Unknown layout";
        }
    }

    void event(const sf::Event &event)
    {
        if (event.type == sf::Event::KeyPressed) {
            /* Allow mapped keys to be pressed simoultanously for
             * a bit smoother steering. */
            if (event.key.code == _keyMap.northKey) {
                _hero->start(North);
                _pressed++;
            }
            else if (event.key.code == _keyMap.southKey) {
                _hero->start(South);
                _pressed++;
            }
            else if (event.key.code == _keyMap.eastKey) {
                _hero->start(East);
                _pressed++;
            }
            else if (event.key.code == _keyMap.westKey) {
                _hero->start(West);
                _pressed++;
            }
        }
        else if (event.type == sf::Event::KeyReleased) {
            /* When no more mapped key is pressed, stop!
             * This makes the game a bit harder but more fun */
            if (event.key.code == _keyMap.northKey ||
                event.key.code == _keyMap.southKey ||
                event.key.code == _keyMap.eastKey ||
                event.key.code == _keyMap.westKey) {
                if (_pressed > 0) {
                    _pressed--;
                }
            }
            if (_pressed == 0) {
                _hero->stop();
            }
        }
    }

private:
    std::shared_ptr<Hero> _hero;
    int                   _pressed;
    struct KeyMap         _keyMap;
};

}

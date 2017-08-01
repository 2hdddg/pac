#include "util/resources.hpp"

namespace game {

Resources::Resources(sf::Vector2f &gameResolution) :
    gameResolution(gameResolution)
{
    std::string fontPath = "../resources/fonts/Roboto-Bold.ttf";
    if (!standardFont.loadFromFile(fontPath)) {
        throw "Unable to load font";
    }
}

}


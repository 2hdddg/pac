#include <iostream>

#include <SFML/Graphics.hpp>
#include "director.hpp"
#include "util/resources.hpp"

#define D(x)

int main() {
    auto mode = sf::VideoMode::getDesktopMode();
    D(std::cout << "Desktopmode: "
              << mode.width << "x" << mode.height << " - "
              << mode.bitsPerPixel << " bpp\n";)

    sf::RenderWindow window(mode, "PAC MAN");
    window.setKeyRepeatEnabled(false);
    window.setVerticalSyncEnabled(true);

    auto gameResolution = sf::Vector2f(mode.width, mode.height);
    auto resources = std::make_shared<game::Resources>(gameResolution);
    auto director = game::Director(resources);

    director.run(window);

    return 0;
}

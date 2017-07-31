#include <SFML/Graphics.hpp>
#include "director.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 400), "PAC MAN");
    game::Director   director;

    director.run(window);

    return 0;
}

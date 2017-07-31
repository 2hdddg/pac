#include "director.hpp"
#include "scenes/start/startscene.hpp"

namespace game {

Director::Director() :
    _scene(new StartScene()) {
}

void Director::run(sf::RenderWindow &window) {
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else {
                _scene->event(event);
            }
        }

        sf::Time elapsed = clock.restart();
        _scene->update(elapsed, [&](auto newScene) {
                _scene = newScene;
            });

        window.clear();
        _scene->render(window);
        window.display();
    }
}

}

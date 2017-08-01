#include <iostream>

#include "director.hpp"

namespace game {

Director::Director(
    std::shared_ptr<Resources> resources):
    _sceneTransition(resources),
    _averageFps(60),
    _showFps(false)
{
    _fpsText.setFont(resources->standardFont);
    _fpsText.setCharacterSize(16);
    _fpsText.setPosition(sf::Vector2f(10, 30));
}

void Director::run(sf::RenderWindow &window)
{
    sf::Clock clock;
    auto      scene = _sceneTransition.getNext();

    /* Main loop */
    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else {
                scene->event(event, &_sceneTransition);
            }
        }

        auto delta = clock.restart().asMicroseconds();

        scene->update(delta, &_sceneTransition);

        auto color = sf::Color(0x21, 0x21, 0x21);
        window.clear(color);
        scene->render(window);
        if (_showFps) {
            approxFps(delta);
            _fpsText.setString(std::to_string(_averageFps));
            window.draw(_fpsText);
        }

        window.display();

        scene = _sceneTransition.getNext();
    }
}

void Director::approxFps(long delta)
{
    const auto N = 100;
    auto fps = 1000000.0 / delta;

    _averageFps -= _averageFps / N;
    _averageFps += fps / N;
}

}

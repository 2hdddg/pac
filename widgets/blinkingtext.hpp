#pragma once

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "util/resources.hpp"
#include "util/animator.hpp"

namespace game {

class BlinkingText
{
public:
    BlinkingText(
        std::shared_ptr<Resources> resources,
        std::string text,
        int charSize,
        int64_t microsecondsInterval) :
        _interval(microsecondsInterval),
        _text(text, resources->standardFont, charSize)
    {
        _animator.set(0, 0);
        _visible = true;
    }

    void setPosition(sf::Vector2f pos)
    {
        _text.setPosition(pos);
    }

    void update(long delta)
    {
        _animator.update(delta,
                         0,
                         [this]() {
                            _visible = !_visible;
                            _animator.set(_interval, 0);
                         });
    }

    void render(sf::RenderTarget &target)
    {
        if (_visible) {
            target.draw(_text);
        }
    }

private:
    int64_t  _interval;
    sf::Text _text;
    Animator _animator;
    bool     _visible;
};

}

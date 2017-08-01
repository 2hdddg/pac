#pragma once

#include <iostream>

#include "util/animator.hpp"

namespace game {

class PillEatingFx {
public:
    PillEatingFx(int max, long time, sf::Vector2f end) :
        _objects(max),
        _max(max),
        _next(0),
        _endPos(end),
        _time(time)
    {
    }

    void add(std::unique_ptr<sf::Sprite> s) {
        auto object = &_objects[_next];
        object->activate(std::move(s), _time, _endPos);

        _next++;
        if (_next == _max) {
            _next = 0;
        }
    }

    void update(long delta) {
        for (AnimatedObject& o : _objects) {
            o.update(delta);
        }
    }

    void render(sf::RenderTarget &target)
    {
        for (AnimatedObject& o : _objects) {
            if (o.sprite) {
                target.draw(*o.sprite);
            }
        }
    }

    void reset()
    {
        for (AnimatedObject& o : _objects) {
            o.reset();
        }
    }

private:
    class AnimatedObject {
    public:
        AnimatedObject() {
        }

        AnimatedObject(const AnimatedObject &a) {
        }

        void activate(std::unique_ptr<sf::Sprite> s,
                      long time,
                      sf::Vector2f endPos)
        {
            sprite = std::move(s);
            _startPos = sprite->getPosition();
            _range = endPos - _startPos;
            _animator.set(time, 1);
        }

        void update(long delta) {
            if (_animator.is_set()) {
                _animator.update(delta,
                    [this](auto progress) {
                        sprite->move(_range * progress);
                    },
                    [this]() {
                        sprite = 0;
                    });
            }
        }

        void reset() {
            /* If not reset progress callback needs
             * to check sprite for null */
            _animator = Animator();
            sprite = 0;
        }

        std::unique_ptr<sf::Sprite> sprite;
    private:
        Animator        _animator;
        sf::Vector2f    _startPos;
        sf::Vector2f    _range;
    };

    std::vector<AnimatedObject> _objects;
    int                         _max;
    int                         _next;
    sf::Vector2f                _endPos;
    long                        _time;
};

}

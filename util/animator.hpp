#pragma once

#include <functional>

namespace game {

class Animator {
public:
    Animator() : _is_set(false)
    {
    }

    void set(long max, float goal)
    {
        _max = max;
        _is_set = true;
        _acc = 0;
        _goal = goal;
    }

    bool is_set()
    {
        return _is_set;
    }

    void update(long delta,
                std::function<void (float)> progress,
                std::function<void ()> done)
    {
        _acc += delta;
        if (_acc >= _max) {
            _is_set = false;
            if (done) {
                done();
            }
        }
        else {
            if (progress) {
                progress(((float)delta / _max) * _goal);
            }
        }
    }

private:
    bool  _is_set;
    long  _max;
    long  _acc;
    float _goal;
};

}

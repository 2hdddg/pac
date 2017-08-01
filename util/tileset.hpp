#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

namespace game {

class Tileset {
public:
    Tileset(sf::Texture &texture, int w, int h) :
        _texture(texture),
        _w(w),
        _h(h)
    {
        auto size = texture.getSize();

        if (size.x % w) {
            throw "Width not even multiple";
        }

        if (size.y % h) {
            throw "Height not even multiple";
        }

        cols = size.x / w;
        rows = size.y / h;
    }

    int rows;
    int cols;

    std::unique_ptr<sf::Sprite> spriteByOffset(int offset)
    {
        int row = offset / cols;
        int col = offset % cols;
        auto rect = sf::IntRect(col * _w, row * _h,
                                _w, _h);
        return std::make_unique<sf::Sprite>(_texture, rect);
    }

    std::unique_ptr<sf::Sprite> spriteByPos(int col, int row)
    {
        auto rect = sf::IntRect(col * _w, row * _h,
                                _w, _h);
        return std::make_unique<sf::Sprite>(_texture, rect);
    }

private:
    sf::Texture &_texture;
    int _w;
    int _h;
};
}

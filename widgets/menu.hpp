#pragma once

#include <SFML/Graphics.hpp>

namespace game {

class MenuItem {
public:
    MenuItem(std::function<void()> onSelected) :
        _isSelected(false),
        _onSelected(onSelected)
    {
    }

    virtual ~MenuItem()
    {
    }

    virtual void select() {
        _isSelected = true;
    }

    virtual void update(long delta) = 0;
    virtual void render(sf::RenderTarget &target) = 0;
    virtual sf::Vector2f getSize() = 0;
    virtual void setPos(sf::Vector2f &pos) = 0;
    virtual void setMax(sf::Vector2f &max) = 0;

protected:
    bool                  _isSelected;
    std::function<void()> _onSelected;
};

class TextMenuItem : public MenuItem {
public:
    TextMenuItem(std::function<void()> onSelected,
                 std::shared_ptr<Resources> resources,
                 std::string text) :
        MenuItem(onSelected),
        _text(text, resources->standardFont, 32)
    {
    }

    virtual void setPos(sf::Vector2f &pos)
    {
        _text.setPosition(pos);
    }

    virtual void setMax(sf::Vector2f &max)
    {
    }

    virtual void select() {
        _onSelected();
    }

    virtual void update(long delta)
    {
    }

    virtual void render(sf::RenderTarget &target)
    {
        target.draw(_text);
    }

    virtual sf::Vector2f getSize()
    {
        auto bounds = _text.getGlobalBounds();

        return sf::Vector2f(bounds.width, bounds.height);
    }

private:
    sf::Text _text;
};

class Menu {
public:
    Menu() {
    }

    bool processEvent(sf::Event &event)
    {
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Up:
                    if (_focusedIndex) {
                        _focusedIndex--;
                    }
                    setFocus();
                    return true;
                case sf::Keyboard::Down:
                    if (_focusedIndex < (_items.size() - 1)) {
                        _focusedIndex++;
                    }
                    setFocus();
                    return true;
                case sf::Keyboard::Return:
                    _items[_focusedIndex]->select();
                    return true;
                default:
                    break;
            }
        }
        return false;
    }

    void update(long delta)
    {
        for (auto& i : _items) {
            i->update(delta);
        }
    }

    void render(sf::RenderTarget &target)
    {
        target.draw(_rect);
        for (auto& i : _items) {
            i->render(target);
        }
    }

    void add(std::unique_ptr<MenuItem> item)
    {
        auto pos = sf::Vector2f(0, 0);
        item->setPos(pos);
        _items.push_back(std::move(item));
    }

    void prepare()
    {
        auto max = sf::Vector2f(0, 0);
        auto pos = _pos;
        auto pad = sf::Vector2f(0, 5);

        /* Find biggest width, height */
        for (auto& i : _items) {
            auto size = i->getSize();

            max.x = size.x > max.x ? size.x : max.x;
            max.y = size.y > max.y ? size.y : max.y;
        }
        _size = max + pad;

        for (auto& i : _items) {
            auto size = i->getSize();
            auto diff = max - size;
            auto centered = sf::Vector2f(pos.x + (diff.x / 2),
                                         pos.y + (diff.y / 2));
            i->setPos(centered);
            pos += pad;
            pos.y += max.y;
        }

        _rect = sf::RectangleShape(_size);
        _rect.setFillColor(sf::Color(0, 255, 0));
        _focusedIndex = 0;
        setFocus();
    }

    void setPos(sf::Vector2f &pos)
    {
        _pos = pos;
    }

private:
    void setFocus()
    {
        auto pos = sf::Vector2f(_pos.x,
                                _pos.y + (_size.y * _focusedIndex));
        _rect.setPosition(pos);
    }

private:
    std::vector<std::unique_ptr<MenuItem>> _items;
    sf::Vector2f                           _pos;
    sf::Vector2f                           _size;
    unsigned int                           _focusedIndex;
    sf::RectangleShape                     _rect;
};


}

#pragma once

#include <vector>
#include <memory>
#include "Sprite.hpp"
#include <algorithm>
#include <map>

class SpriteManager {
    public:
        void addSprite(const std::shared_ptr<Sprite> &sprite, std::size_t id)
        {
            _mapSprite[id] = sprite;
        }

        void removeSprite(std::size_t id)
        {
            auto it = _mapSprite.find(id);
            if (it != _mapSprite.end()) {
                _mapSprite.erase(it);
            }
        }

        void drawAll(sf::RenderWindow &window)
        {
            for (const auto& [id, sprite] : _mapSprite) {
                //std::cout << "draw" << std::endl;
                sprite->draw(window);
            }
        }

        std::shared_ptr<Sprite> getSprite(std::size_t id) const
        {
            auto it = _mapSprite.find(id);
            if (it != _mapSprite.end()) {
                return it->second;
            }
            return nullptr;
        }

        std::size_t getSpriteCount() const
        {
            return _mapSprite.size();
        }

        void eraseOldSprite()
        {
            
        }

    private:
        std::map<std::size_t, std::shared_ptr<Sprite>> _mapSprite;
};
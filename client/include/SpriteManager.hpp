#pragma once
#include "../include/client/Sprite.hpp"
// #include "Game.hpp"
#include <unordered_set>
#include <algorithm>
#include <vector>
#include <memory>
#include <map>
#include "Type.hpp"

class SpriteManager
{
public:
    void addSprite(const std::shared_ptr<Sprite> &sprite, std::size_t id)
    {
        _mapSprite[id] = sprite;
    }

    void removeSprite(std::size_t id)
    {
        auto it = _mapSprite.find(id);
        if (it != _mapSprite.end())
        {
            _mapSprite.erase(it);
        }
    }

    void drawAll(sf::RenderWindow &window, sf::Time deltaTime)
    {
        for (const auto &[id, sprite] : _mapSprite)
        {
            sprite->update(deltaTime);
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

        void eraseOldSprite(std::unordered_set<std::size_t> &container)
        {
            for (auto elem : container)
                std::cout << "id container: " << elem << std::endl;
            for (auto it = _mapSprite.begin(); it != _mapSprite.end(); ) {
                std::cout << "test: " << it->first << std::endl;
                if (container.find(it->first) == container.end()) {
                    if (it->second.get()->getType() != Type::Bullet){
                        death_animation(it->second.get()->getPosition());
                    }
                    it = _mapSprite.erase(it);
                } else {
                    ++it;
                }
            }
            container.clear();
        }

        void death_animation(sf::Vector2f pos)
        {
            auto sprite = std::make_shared<Sprite>("../../client/config/explosion.json");
            sprite.get()->setPosition(pos);
            _mapSprite.insert(std::make_pair(_mapSprite.size(), sprite));
        }

        void eraseAll()
        {
            _mapSprite.clear();
        }

        


    private:
        std::map<std::size_t, std::shared_ptr<Sprite>> _mapSprite;

};
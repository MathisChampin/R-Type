#pragma once
#include "../include/client/Sprite.hpp"
#include <unordered_set>
#include <algorithm>
#include <vector>
#include <memory>
#include <map>
#include "Type.hpp"

class SpriteManager {
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
        std::vector<std::size_t> toRemove;
        deltaTime = deltaTime;
        
        for (const auto &[id, sprite] : _mapSprite)
        {
            sprite->update(deltaTime);
            sprite->draw(window);
            
            if (sprite->getType() == Type::Explosions && sprite->hasFinishedAnimation())
            {
                toRemove.push_back(id);
            }
        }
        
        for (auto id : toRemove)
        {
            removeSprite(id);
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
        for (auto it = _mapSprite.begin(); it != _mapSprite.end(); )
        {
            if (container.find(it->first) == container.end())
            {
                if (it->second->getType() != Type::Bullet && 
                    it->second->getType() != Type::Explosions)
                {
                    sf::Vector2f pos = it->second->getPosition();
                    it = _mapSprite.erase(it);
                    createDeathAnimation(pos);
                }
                else
                {
                    it = _mapSprite.erase(it);
                }
            }
            else
            {
                ++it;
            }
        }
        container.clear();
    }

    void createDeathAnimation(sf::Vector2f pos)
    {
        std::size_t newId = generateUniqueId();
        auto sprite = std::make_shared<Sprite>("../../client/config/explosion.json");
        sprite->setPosition(pos);
        _mapSprite[newId] = sprite;
    }

    void eraseAll()
    {
        _mapSprite.clear();
    }

private:
    std::size_t generateUniqueId()
    {
        std::size_t newId = 0;
        while (_mapSprite.find(newId) != _mapSprite.end())
        {
            newId++;
        }
        return newId;
    }

    std::map<std::size_t, std::shared_ptr<Sprite>> _mapSprite;
};
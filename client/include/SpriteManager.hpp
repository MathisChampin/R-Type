#pragma once
#include "../include/client/Sprite.hpp"
#include <unordered_set>
#include <algorithm>
#include <vector>
#include <memory>
#include <map>
#include "Type.hpp"
#include "../include/DeathAnimation.hpp"

class SpriteManager {
public:
    SpriteManager() {
        m_deathAnimation.initialize("../../client/assets/explosions/", 7, 20.f); // Configure as needed
    }

    void addSprite(const std::shared_ptr<Sprite> &sprite, std::size_t id)
    {
        _mapSprite[id] = sprite;
    }

    void removeSprite(std::size_t id)
    {
        auto it = _mapSprite.find(id);
        if (it != _mapSprite.end())
        {
            m_deathAnimation.triggerAnimation(id % 10);
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

        m_deathAnimation.update(deltaTime.asSeconds());
        m_deathAnimation.render(window);
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
                it->second->
                if (it->second->getType() == Type::Enemy || it->second->getType() == Type::Player)
                {
                    m_deathAnimation.triggerAnimation(it->first % 10);
                    m_deathAnimation.setAnimationPosition(it->second->getPosition());
                    it = _mapSprite.erase(it);
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
    DeathAnimation m_deathAnimation;
};

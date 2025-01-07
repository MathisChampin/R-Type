#pragma once

#include "../include/client/Sprite.hpp"
#include <unordered_set>
#include <algorithm>
#include <vector>
#include <memory>
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

        void eraseOldSprite(const std::queue<NmpClient::Packet> &packetQueue)
        {
            std::unordered_set<std::size_t> idSet;
            auto tempQueue = packetQueue;
            while (!tempQueue.empty()) {
                idSet.insert(tempQueue.front().getSpriteInfo().idClient);
            }
            for (auto it = _mapSprite.begin(); it != _mapSprite.end(); ) {
                if (idSet.find(it->first) == idSet.end()) {
                    it = _mapSprite.erase(it);
                } else {
                    ++it;
                }
            }
        }


    private:
        std::map<std::size_t, std::shared_ptr<Sprite>> _mapSprite;
};
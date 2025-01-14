#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include "TextureManager.hpp"
#include <iostream>
#include "../Type.hpp"

class Sprite {
public:
    Sprite(const std::string &configPath)
    {
        loadFromConfig(configPath);
    }

    void loadFromConfig(const std::string &configPath)
    {
        std::ifstream file(configPath);
        nlohmann::json config;
        file >> config;

        position.x = config["position"]["x"];
        position.y = config["position"]["y"];
        size.x = config["size"]["width"];
        size.y = config["size"]["height"];

        if (config["type"] == "player")
        {
            m_type = Type::Player;
            animationSpeed = 10.0f;
        }
        else if (config["type"] == "enemy")
        {
            m_type = Type::Enemy;
            animationSpeed = 10.0f;
        }
        else if (config["type"] == "shoot")
        {
            m_type = Type::Bullet;
            animationSpeed = 10.0f;
        }
        else if (config["type"] == "explosions")
        {
            m_type = Type::Explosions;
            animationSpeed = 1.0f;
            frameDelay = 0.05f;
            isAnimationComplete = false;
        }

        if (config["type"] == "player" || config["type"] == "enemy" || 
            config["type"] == "shoot" || config["type"] == "explosions")
        {
            for (int i = 1; i <= 5; ++i)
            {
                std::string textureKey = "texture" + std::to_string(i);
                if (config.contains(textureKey))
                {
                    auto tex = TextureManager::getInstance().loadTexture(config[textureKey]);
                    m_textures.push_back(tex);
                }
            }

            if (!m_textures.empty())
            {
                currentTextureIndex = 0;
                sprite.setTexture(*m_textures[currentTextureIndex]);
            }
        }
        else
        {
            auto tex = TextureManager::getInstance().loadTexture(config["texture"]);
            m_textures.push_back(tex);
            sprite.setTexture(*m_textures[0]);
        }

        sprite.setPosition(position);
        updateSpriteScale();
    }

    void update(sf::Time deltaTime)
    {
        if (m_textures.size() > 1)
        {
            animationTimer += deltaTime;

            if (m_type == Type::Explosions)
            {
                if (animationTimer.asSeconds() >= frameDelay)
                {
                    if (currentTextureIndex < m_textures.size() - 1)
                    {
                        currentTextureIndex++;
                        sprite.setTexture(*m_textures[currentTextureIndex]);
                        updateSpriteScale();
                        animationTimer = sf::Time::Zero;
                    }
                    else
                    {
                        if (!isAnimationComplete)
                        {
                            isAnimationComplete = true;
                            endDelay = sf::Time::Zero;
                        }
                        else if (endDelay.asSeconds() < 1.0f)
                        {
                            endDelay += deltaTime;
                        }
                    }
                }
            }
            else
            {
                if (animationTimer.asSeconds() >= 1.0f / animationSpeed)
                {
                    currentTextureIndex = (currentTextureIndex + 1) % m_textures.size();
                    sprite.setTexture(*m_textures[currentTextureIndex]);
                    updateSpriteScale();
                    animationTimer = sf::Time::Zero;
                }
            }
        }
    }

    void draw(sf::RenderWindow &window)
    {
        if (m_type != Type::Explosions || (m_type == Type::Explosions && !isAnimationComplete))
        {
            window.draw(sprite);
        }
    }

    void setPosition(const sf::Vector2f &pos)
    {
        position = pos;
        sprite.setPosition(position);
    }

    sf::Vector2f getPosition() const
    {
        return position;
    }

    void setTextureRect(const sf::IntRect &rect)
    {
        sprite.setTextureRect(rect);
    }

    void setAnimationSpeed(float framesPerSecond)
    {
        animationSpeed = framesPerSecond;
    }

    Type getType() const
    {
        return m_type;
    }

    bool hasFinishedAnimation() const
    {
        return m_type == Type::Explosions && isAnimationComplete && endDelay.asSeconds() >= 1.0f;
    }

private:
    void updateSpriteScale()
    {
        if (!m_textures.empty())
        {
            auto currentTexture = m_textures[currentTextureIndex];
            sprite.setScale(
                size.x / currentTexture->getSize().x,
                size.y / currentTexture->getSize().y);
        }
    }

    sf::Sprite sprite;
    std::vector<std::shared_ptr<sf::Texture>> m_textures;
    sf::Vector2f position;
    sf::Vector2f size;
    Type m_type;

    size_t currentTextureIndex = 0;
    float animationSpeed = 0.0f;
    float frameDelay = 0.0f;
    sf::Time animationTimer;
    sf::Time endDelay;
    bool isAnimationComplete = false;
};

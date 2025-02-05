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
        }
        else if (config["type"] == "enemy")
        {
            m_type = Type::Enemy;
        }
        else if (config["type"] == "shoot1Player")
        {
            m_type = Type::Bullet;
        }
        else if (config["type"] == "powerup_life")
        {
            m_type = Type::PowerupLife;
        }
        else if (config["type"] == "powerup_move")
        {
            m_type = Type::PowerupMove;
        }
        else if (config["type"] == "shoot4Player")
        {
            m_type = Type::Bullet;
        }
        else if (config["type"] == "shoot2Player")
        {
            m_type = Type::Bullet;
        }
        else if (config["type"] == "shoot3Player")
        {
            m_type = Type::Bullet;
        }
        else if (config["type"] == "shoot5Player")
        {
            m_type = Type::Bullet;
        }
        else if (config["type"] == "shoot2Enemy")
        {
            m_type = Type::Bullet;
        }
        else if (config["type"] == "shoot1Enemy")
        {
            m_type = Type::Bullet;
        }
        else if (config["type"] == "shoot3Enemy")
        {
            m_type = Type::Bullet;
        }
        else if (config["type"] == "shoot4Enemy")
        {
            m_type = Type::Bullet;
        }
        else if (config["type"] == "shoot5Enemy")
        {
            m_type = Type::Bullet;
        }


        if (config["type"] == "player" || config["type"] == "enemy" || config["type"] == "shoot1Player" ||
            config["type"] == "powerup_life" || config["type"] == "powerup_move" || config["type"] == "shoot4Player" ||
            config["type"] == "shoot2Player" || config["type"] == "shoot3Player" || config["type"] == "shoot5Player" ||
            config["type"] == "shoot2Enemy" || config["type"] == "shoot1Enemy" || config["type"] == "shoot3Enemy" ||
            config["type"] == "shoot4Enemy" || config["type"] == "shoot5Enemy")
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

            if (animationTimer.asSeconds() >= 1.0f / animationSpeed)
            {
                currentTextureIndex = (currentTextureIndex + 1) % m_textures.size();
                sprite.setTexture(*m_textures[currentTextureIndex]);
                updateSpriteScale();
                animationTimer = sf::Time::Zero;
            }
        }
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(sprite);
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

    sf::Sprite getSprite() const
    {
        return sprite;
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
    float animationSpeed = 10.0f;
    sf::Time animationTimer;
};

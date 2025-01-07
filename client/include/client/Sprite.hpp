#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include "TextureManager.hpp"

class Sprite
{
public:
    /**
     * @brief Constructs a Sprite object from a configuration file.
     *
     * @param configPath The path to the configuration file.
     */
    Sprite(const std::string &configPath)
    {
        loadFromConfig(configPath);
    }

    /**
     * @brief Loads sprite configuration from a JSON file.
     *
     * This function reads the sprite configuration from the specified JSON file
     * and sets the texture, position, and size of the sprite accordingly.
     *
     * @param configPath The path to the JSON configuration file.
     */
    void loadFromConfig(const std::string &configPath)
    {
        std::ifstream file(configPath);
        nlohmann::json config;
        file >> config;

        std::string texturePath = config["texture"];
        position.x = config["position"]["x"];
        position.y = config["position"]["y"];
        size.x = config["size"]["width"];
        size.y = config["size"]["height"];

        if (config["type"] == "player")
        {
            for (int i = 1; i <= 5; ++i)
            {
                sf::Texture texture;
                texture.loadFromFile(texturePath);
                m_textures.push_back(texture);
                sprite.setTexture(m_textures[i]);
            }
        }
        else
        {
            texture = TextureManager::getInstance().loadTexture(texturePath);
            sprite.setTexture(*texture);
        }
        // sprite.setTexture(*texture);
        sprite.setPosition(position);
        sprite.setScale(size.x / texture->getSize().x, size.y / texture->getSize().y);
    }

    /**
     * @brief Draws the sprite onto the given render window.
     *
     * @param window The render window where the sprite will be drawn.
     */
    void draw(sf::RenderWindow &window)
    {
        window.draw(sprite);
    }

    /**
     * @brief Sets the position of the sprite.
     *
     * @param pos The new position of the sprite.
     */
    void setPosition(const sf::Vector2f &pos)
    {
        position = pos;
        sprite.setPosition(position);
    }

    /**
     * @brief Gets the position of the sprite.
     *
     * @return sf::Vector2f The position of the sprite.
     */
    sf::Vector2f getPosition() const
    {
        return position;
    }

    /**
     * @brief Sets the size of the sprite.
     *
     * @param s The new size of the sprite.
     */
    void setTextureRect(const sf::IntRect &rect)
    {
        sprite.setTextureRect(rect);
    }

private:
    sf::Sprite sprite;
    std::shared_ptr<sf::Texture> texture;
    std::vector<sf::Texture> m_textures;
    sf::Vector2f position;
    sf::Vector2f size;
};
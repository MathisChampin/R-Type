#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include "TextureManager.hpp"

class Sprite {
public:
    Sprite(const std::string& configPath) {
        loadFromConfig(configPath);
    }

    void loadFromConfig(const std::string& configPath) {
        std::ifstream file(configPath);
        nlohmann::json config;
        file >> config;

        std::string texturePath = config["texture"];
        position.x = config["position"]["x"];
        position.y = config["position"]["y"];
        size.x = config["size"]["width"];
        size.y = config["size"]["height"];

        texture = TextureManager::getInstance().loadTexture(texturePath);
        sprite.setTexture(*texture);
        sprite.setPosition(position); // Utilisation directe du vecteur
        sprite.setScale(size.x / texture->getSize().x, size.y / texture->getSize().y);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

    void setPosition(const sf::Vector2f& pos) { // Prend une référence constante
        position = pos;
        sprite.setPosition(position);
    }

    sf::Vector2f getPosition() const {
        return position;
    }

    void setTextureRect(const sf::IntRect& rect) {
        sprite.setTextureRect(rect);
    }

private:
    sf::Sprite sprite;
    std::shared_ptr<sf::Texture> texture;
    sf::Vector2f position;
    sf::Vector2f size;
};
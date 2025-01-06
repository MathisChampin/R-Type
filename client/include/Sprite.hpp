#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include "TextureManger.hpp"

class Sprite {
    public:
        Sprite(const std::string& configPath) {
            loadFromConfig(configPath);
        }
    
        void loadFromConfig(const std::string& configPath) {
            std::ifstream file(configPath);
            nlohmann::json config;
            file >> config;
            //la ouverture fichier etc
    
            std::string texturePath = config["texture"];
            position.x = config["position"]["x"];
            position.y = config["position"]["y"];
            size.x = config["size"]["width"];
            size.y = config["size"]["height"];
            //parse et stock les infos du fichiers
    
            texture = TextureManager::getInstance().loadTexture(texturePath);
            sprite.setTexture(*texture);
            sprite.setPosition(position);
            sprite.setScale(size.x / texture->getSize().x, size.y / texture->getSize().y);
            //choisis la bonne texture grace au texture manager et l'attribut au sprite
        }
    
        void draw(sf::RenderWindow& window) {
            window.draw(sprite);
        }
    
        void setPosition(const sf::Vector2f& pos) {
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
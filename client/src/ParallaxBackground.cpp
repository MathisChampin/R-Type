#include "../include/ParallaxBackground.hpp"
#include <iostream>

ParallaxBackground::ParallaxBackground(const sf::Vector2u& windowSize, const std::vector<std::pair<std::string, float>>& layers)
    : m_windowSize(windowSize)
{
    m_textures.reserve(layers.size());
    m_planets.resize(layers.size());
    for (const auto& layerInfo : layers) {
        setupLayer(layerInfo.first, layerInfo.second);
    }
}

void ParallaxBackground::setupLayer(const std::string& texturePath, float speed)
{
    m_textures.emplace_back();
    if (!m_textures.back().loadFromFile(texturePath)) {
        std::cerr << "Erreur lors du chargement de la texture : " << texturePath << std::endl;
        return;
    }
    m_textures.back().setRepeated(true);

    Layer layer;
    layer.textureIndex = m_textures.size() - 1;
    layer.sprite.setTexture(m_textures[layer.textureIndex]);
    layer.speed = speed;
    layer.offset = 0.0f;

    updateLayerScale(layer.sprite, m_textures[layer.textureIndex]);

    m_layers.push_back(layer);
}

void ParallaxBackground::updateLayerScale(sf::Sprite& sprite, const sf::Texture& texture)
{
    sf::Vector2u textureSize = texture.getSize();
    float scaleX = static_cast<float>(m_windowSize.x) / textureSize.x; // Utiliser la largeur de la fenêtre
    float scaleY = static_cast<float>(m_windowSize.y) / textureSize.y;
    sprite.setScale(scaleX, scaleY);
}


void ParallaxBackground::addPlanetToLayer(size_t layerIndex, const std::string& texturePath, const sf::Vector2f& position, float speed) {
    if (layerIndex >= m_layers.size()) {
        std::cerr << "Erreur : l'index du layer dépasse la taille du vecteur de layers." << std::endl;
        return;
    }

    sf::Texture texture;
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Erreur lors du chargement de la texture de la planète : " << texturePath << std::endl;
        return;
    }

    Planet planet;
    planet.sprite.setTexture(texture);
    planet.sprite.setPosition(position);
    planet.position = position;
    planet.speed = speed;

    m_planets[layerIndex].push_back(planet);
}

void ParallaxBackground::update(float deltaTime)
{
    for (auto& layer : m_layers) {
        layer.offset += layer.speed * deltaTime * 100.0f;

        if (layer.offset >= layer.sprite.getTexture()->getSize().x) { 
            layer.offset = 0.0f;
        }
        layer.sprite.setTextureRect(sf::IntRect(static_cast<int>(layer.offset), 0, static_cast<int>(m_windowSize.x), static_cast<int>(m_windowSize.y))); // Fenêtre complète
    }
    updatePlanets(deltaTime);
}

void ParallaxBackground::updatePlanets(float deltaTime) {
    for (size_t i = 0; i < m_planets.size(); ++i) {
        for (auto& planet : m_planets[i]) {
            planet.position.x -= deltaTime * planet.speed;
            planet.sprite.setPosition(planet.position);

            if (planet.position.x + planet.sprite.getGlobalBounds().width < 0) {
                planet.position.x = m_windowSize.x + planet.sprite.getGlobalBounds().width;
            }
        }
    }
}

void ParallaxBackground::render(sf::RenderWindow& window)
{
    for (auto& layer : m_layers) {
        layer.sprite.setTexture(m_textures[layer.textureIndex]);
        window.draw(layer.sprite);
        sf::Sprite secondSprite = layer.sprite;
        secondSprite.setPosition(layer.sprite.getGlobalBounds().width, 0);
        window.draw(secondSprite);
    }
    renderPlanets(window);
}

void ParallaxBackground::renderPlanets(sf::RenderWindow& window) {
    for (const auto& layerPlanets : m_planets) {
        for (const auto& planet : layerPlanets) {
            window.draw(planet.sprite);
        }
    }
}
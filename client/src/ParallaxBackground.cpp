#include "../include/ParallaxBackground.hpp"
#include <iostream>

ParallaxBackground::ParallaxBackground(const sf::Vector2u &windowSize, const std::vector<std::pair<std::string, float>> &layers)
    : m_windowSize(windowSize)
{
    for (const auto &layerInfo : layers)
    {
        setupLayer(layerInfo.first, layerInfo.second);
    }
}

void ParallaxBackground::setupLayer(const std::string &texturePath, float speed)
{
    sf::Texture texture;
    if (!texture.loadFromFile(texturePath))
    {
        std::cerr << "Erreur lors du chargement de la texture : " << texturePath << std::endl;
        return;
    }

    texture.setRepeated(true);
    m_textures.push_back(texture);

    Layer layer;
    layer.sprite.setTexture(m_textures.back());
    layer.speed = speed;
    layer.offset = 0.0f;

    updateLayerScale(layer.sprite);

    m_layers.push_back(layer);
}

void ParallaxBackground::updateLayerScale(sf::Sprite &sprite)
{
    sf::Vector2u textureSize = sprite.getTexture()->getSize();
    float scaleX = static_cast<float>(m_windowSize.x * 2) / textureSize.x;
    float scaleY = static_cast<float>(m_windowSize.y) / textureSize.y;
    sprite.setScale(scaleX, scaleY);
}

void ParallaxBackground::update(float deltaTime)
{
    for (auto &layer : m_layers)
    {
        layer.offset += layer.speed * deltaTime * 100.0f;

        if (layer.offset >= m_windowSize.x)
        {
            layer.offset = 0.0f;
        }

        layer.sprite.setPosition(-layer.offset, 0);
    }
}

void ParallaxBackground::render(sf::RenderWindow &window)
{
    for (auto &layer : m_layers)
    {
        window.draw(layer.sprite);

        layer.sprite.setPosition(-layer.offset + m_windowSize.x, 0);
        window.draw(layer.sprite);
    }
}

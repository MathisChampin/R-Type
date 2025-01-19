#ifndef PARALLAX_BACKGROUND_HPP_
#define PARALLAX_BACKGROUND_HPP_

#include <SFML/Graphics.hpp>
#include <vector>

class ParallaxBackground
{
public:
    struct Layer
    {
        sf::Sprite sprite;
        float speed;
        float offset;
        size_t textureIndex;
    };

    struct Planet
    {
        sf::Sprite sprite;
        sf::Vector2f position;
        float speed;
    };

    ParallaxBackground(const sf::Vector2u& windowSize, const std::vector<std::pair<std::string, float>>& layers);

    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    void setupLayer(const std::string& texturePath, float speed);
    void addPlanetToLayer(size_t layerIndex, const std::string& texturePath, const sf::Vector2f& position, float speed);

private:
    std::vector<Layer> m_layers;
    std::vector<sf::Texture> m_textures;
    std::vector<std::vector<Planet>> m_planets;
    sf::Vector2u m_windowSize;

    void updateLayerScale(sf::Sprite& sprite, const sf::Texture& texture);
    void loadPlanet(Layer& layer, const std::string& texturePath, const sf::Vector2f& initialPosition);
    void updatePlanets(float deltaTime);
    void renderPlanets(sf::RenderWindow& window);
};

#endif // PARALLAX_BACKGROUND_HPP_
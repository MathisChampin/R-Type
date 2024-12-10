#ifndef PARALLAX_BACKGROUND_HPP_
#define PARALLAX_BACKGROUND_HPP_

#include <SFML/Graphics.hpp>
#include <vector>

class ParallaxBackground {
public:
    struct Layer {
        sf::Sprite sprite;
        float speed;
        float offset;
    };

    ParallaxBackground(const sf::Vector2u& windowSize, const std::vector<std::pair<std::string, float>>& layers);

    void update(float deltaTime);
    void render(sf::RenderWindow& window);

private:
    std::vector<Layer> m_layers;
    std::vector<sf::Texture> m_textures;
    sf::Vector2u m_windowSize;

    void setupLayer(const std::string& texturePath, float speed);
    void updateLayerScale(sf::Sprite& sprite);
};

#endif // PARALLAX_BACKGROUND_HPP_

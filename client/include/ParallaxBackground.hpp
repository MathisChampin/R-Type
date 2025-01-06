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
    };
    ParallaxBackground() = default;

    /**
     * @brief Constructs a ParallaxBackground object.
     *
     * @param windowSize The size of the window as a sf::Vector2u object.
     * @param layers A vector of pairs, where each pair contains a string representing the file path of the layer image and a float representing the parallax factor for that layer.
     */
    ParallaxBackground(const sf::Vector2u &windowSize, const std::vector<std::pair<std::string, float>> &layers);

    /**
     * @brief Updates the parallax background based on the elapsed time.
     *
     * @param deltaTime The time elapsed since the last update.
     */
    void update(float deltaTime);

    /**
     * @brief Renders the parallax background onto the given render window.
     *
     * @param window The render window where the parallax background will be drawn.
     */
    void render(sf::RenderWindow &window);

private:
    std::vector<Layer> m_layers;
    std::vector<sf::Texture> m_textures;
    sf::Vector2u m_windowSize;

    void setupLayer(const std::string &texturePath, float speed);
    void updateLayerScale(sf::Sprite &sprite);
};

#endif // PARALLAX_BACKGROUND_HPP_

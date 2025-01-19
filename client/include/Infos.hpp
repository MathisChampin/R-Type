#ifndef INFOS_HPP
#define INFOS_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <memory>

class Infos {
public:
    struct InfoItem {
        std::shared_ptr<sf::Texture> texture;
        sf::Sprite sprite;
        sf::Text description;
    };

    Infos(sf::RenderWindow& window, sf::Font& font);

    void addItem(const std::shared_ptr<sf::Texture>& texture, const std::string& description, bool alignRight, float scaleX, float scaleY, float yOffset = 0.0f);
    void addText(const std::string& text, sf::Color color, unsigned int size, bool bold = false);
    void addCustomText(const std::shared_ptr<sf::Text>& text);
    void update(float deltaTime);
    void render();

private:
    sf::RenderWindow& m_window;
    sf::Font& m_font;
    std::vector<InfoItem> m_items;
    std::vector<std::shared_ptr<sf::Text>> m_titles;
    float m_currentYOffset;
    float m_spacing = 20.0f;
    private:
    float m_currentYOffsetRight;

};

#endif // INFOS_HPP

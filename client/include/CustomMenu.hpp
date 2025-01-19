#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

enum class SkinType {
    SKIN1,
    SKIN2,
    SKIN3,
    SKIN4,
    SKIN5,
};

class CustomMenu {
public:
    CustomMenu(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event);
    void update();
    void render();
    SkinType getSelectedSkin() const { return static_cast<SkinType>(m_selectedSkinIndex); }

private:
    void setupTitleText();
    void setupSkins();
    void updateSkinText();
    void loadSkinTextures();

    sf::RenderWindow& m_window;
    sf::Font m_font;
    sf::Text m_titleText;
    sf::Text m_skinText;
    std::vector<std::string> m_skins;
    std::vector<sf::Texture> m_skinTextures;
    std::vector<sf::Sprite> m_skinSprites;
    size_t m_selectedSkinIndex;
    const float SPRITE_SCALE = 5.0f;
};

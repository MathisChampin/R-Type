#include "Infos.hpp"
#include <iostream>

Infos::Infos(sf::RenderWindow& window, sf::Font& font)
    : m_window(window), m_font(font), m_currentYOffset(50.0f), m_currentYOffsetRight(50.0f) {}

void Infos::addItem(const std::shared_ptr<sf::Texture>& texture, const std::string& descriptionText, bool alignRight, float x, float y, float yOffset)
{
    InfoItem item;

    item.texture = texture;

    item.sprite.setTexture(*texture);
    item.sprite.setScale(x, y);

    item.description.setFont(m_font);
    item.description.setString(descriptionText);
    item.description.setCharacterSize(20);
    item.description.setFillColor(sf::Color::White);

    if (alignRight) {
        sf::Vector2u windowSize = m_window.getSize();
        item.sprite.setPosition(windowSize.x - item.sprite.getGlobalBounds().width - 50.0f, m_currentYOffset + yOffset);
    } else {
        item.sprite.setPosition(50.0f, m_currentYOffset + yOffset);
    }

    sf::FloatRect spriteBounds = item.sprite.getGlobalBounds();
    sf::FloatRect textBounds = item.description.getLocalBounds();

    float textX = alignRight
        ? spriteBounds.left - textBounds.width - 20.0f
        : spriteBounds.left + spriteBounds.width + 20.0f;

    float textY = spriteBounds.top + (spriteBounds.height / 2) - (textBounds.height / 2) - textBounds.top;

    item.description.setPosition(textX, textY);

    m_items.push_back(item);

    m_currentYOffset += spriteBounds.height + 20.0f;
}


void Infos::addCustomText(const std::shared_ptr<sf::Text>& text) {
    m_titles.push_back(text);
}


void Infos::addText(const std::string& text, sf::Color color, unsigned int size, bool bold) {
    auto title = std::make_shared<sf::Text>();
    title->setString(text);
    title->setFont(m_font);
    title->setCharacterSize(size);
    title->setFillColor(color);

    if (bold) {
        title->setStyle(sf::Text::Bold);
    }

    title->setPosition(50.0f, m_currentYOffset);

    m_titles.push_back(title);

    m_currentYOffset += title->getGlobalBounds().height + 20.0f;
}

void Infos::update(float deltaTime) {
    (void)deltaTime;
}

void Infos::render() {
    for (const auto& title : m_titles) {
        m_window.draw(*title);
    }

    for (const auto& item : m_items) {
        m_window.draw(item.sprite);
        m_window.draw(item.description);
    }
}

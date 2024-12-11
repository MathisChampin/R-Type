#include "../include/OptionsMenu.hpp"
#include <iostream>

OptionsMenu::OptionsMenu(sf::RenderWindow& window)
    : m_window(window), m_volume(50.0f)
    {
    if (!m_font.loadFromFile("./assets/fonts/ZenDots-Regular.ttf")) {
        std::cerr << "Erreur : Impossible de charger la police !" << std::endl;
    }
    // if (!m_music.openFromFile("./assets/music/back2.mp3")) {
    //     std::cerr << "Erreur : Impossible de charger la musique !" << std::endl;
    // }
    m_music.setLoop(true);
    m_music.play();
    m_music.setVolume(m_volume);

    setupTitleText();
    setupVolumeText();
    setupVolumeBar();
}

void OptionsMenu::setupTitleText()
{
    m_titleText.setFont(m_font);
    m_titleText.setString("Options");
    m_titleText.setCharacterSize(90);
    m_titleText.setFillColor(sf::Color::Blue);
    m_titleText.setPosition(100, 50);
    sf::FloatRect textRect = m_titleText.getLocalBounds();
    m_titleText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    m_titleText.setPosition(m_window.getSize().x / 2.0f, textRect.height + 90);
}

void OptionsMenu::setupVolumeText()
{
    m_volumeText.setFont(m_font);
    m_volumeText.setString("Volume: " + std::to_string(static_cast<int>(m_volume)));
    m_volumeText.setCharacterSize(30);
    m_volumeText.setFillColor(sf::Color::White);
    m_volumeText.setPosition(m_window.getSize().x / 2.0f - 350, 350);
}

void OptionsMenu::setupVolumeBar()
{
    m_volumeBarBackground.setSize(sf::Vector2f(300, 20));
    m_volumeBarBackground.setFillColor(sf::Color(100, 100, 100));
    m_volumeBarBackground.setPosition(m_window.getSize().x / 2.0f - 400, 400);

    m_volumeBarForeground.setSize(sf::Vector2f(m_volume * 3, 20));
    m_volumeBarForeground.setFillColor(sf::Color::Green);
    m_volumeBarForeground.setPosition(m_window.getSize().x / 2.0f - 400, 400);
}

void OptionsMenu::updateVolumeBar()
{
    m_volumeBarForeground.setSize(sf::Vector2f(m_volume * 3, 20));
}

void OptionsMenu::updateMusicVolume()
{
    m_music.setVolume(m_volume);
}

void OptionsMenu::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            m_volume = std::min(100.0f, m_volume + 5.0f);
        } else if (event.key.code == sf::Keyboard::Down) {
            m_volume = std::max(0.0f, m_volume - 5.0f);
        }
        m_volumeText.setString("Volume: " + std::to_string(static_cast<int>(m_volume)));
        updateVolumeBar();
        updateMusicVolume();
    } else if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
            sf::FloatRect volumeBarBounds = m_volumeBarBackground.getGlobalBounds();
            if (volumeBarBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                float newVolume = (mousePos.x - volumeBarBounds.left) / volumeBarBounds.width * 100.0f;
                m_volume = std::clamp(newVolume, 0.0f, 100.0f);
                m_volumeText.setString("Volume: " + std::to_string(static_cast<int>(m_volume)));
                updateVolumeBar();
                updateMusicVolume();
            }
        }
    } else if (event.type == sf::Event::MouseMoved) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
            sf::FloatRect volumeBarBounds = m_volumeBarBackground.getGlobalBounds();
            if (volumeBarBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                float newVolume = (mousePos.x - volumeBarBounds.left) / volumeBarBounds.width * 100.0f;
                m_volume = std::clamp(newVolume, 0.0f, 100.0f);
                m_volumeText.setString("Volume: " + std::to_string(static_cast<int>(m_volume)));
                updateVolumeBar();
                updateMusicVolume();
            }
        }
    }
}

void OptionsMenu::update()
{

}

void OptionsMenu::render()
{
    m_window.draw(m_titleText);
    m_window.draw(m_volumeText);
    m_window.draw(m_volumeBarBackground);
    m_window.draw(m_volumeBarForeground);
}
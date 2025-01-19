// SettingsMenu.cpp
#include "../include/SettingsMenu.hpp"
#include <iostream>
#include <algorithm> // Pour std::clamp

SettingsMenu::SettingsMenu(sf::RenderWindow &window, SoundManager &soundManager)
    : m_window(window), m_soundManager(soundManager), m_volume(50.0f), m_fps(60)
{
    if (!m_font.loadFromFile("./assets/fonts/ZenDots-Regular.ttf"))
    {
        std::cerr << "Erreur : Impossible de charger la police !" << std::endl;
    }

    // Initialisation des éléments
    setupTitleText();
    setupVolumeText();
    setupVolumeBar();
    setupFPSText();
    setupFPSBar();
}

void SettingsMenu::setupTitleText()
{
    m_titleText.setFont(m_font);
    m_titleText.setString("Options");
    m_titleText.setCharacterSize(90);
    m_titleText.setFillColor(sf::Color::Blue);
    sf::FloatRect textRect = m_titleText.getLocalBounds();
    m_titleText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    m_titleText.setPosition(m_window.getSize().x / 2.0f, textRect.height + 50);
}

void SettingsMenu::setupVolumeText()
{
    m_volumeText.setFont(m_font);
    m_volumeText.setString("Volume: " + std::to_string(static_cast<int>(m_volume)));
    m_volumeText.setCharacterSize(30);
    m_volumeText.setFillColor(sf::Color::White);
    m_volumeText.setPosition(100, 200);
}

void SettingsMenu::setupVolumeBar()
{
    m_volumeBarBackground.setSize(sf::Vector2f(300, 20));
    m_volumeBarBackground.setFillColor(sf::Color(100, 100, 100));
    m_volumeBarBackground.setPosition(100, 250);

    m_volumeBarForeground.setSize(sf::Vector2f(m_volume * 3, 20));
    m_volumeBarForeground.setFillColor(sf::Color::Green);
    m_volumeBarForeground.setPosition(100, 250);
}

void SettingsMenu::setupFPSText()
{
    m_fpsText.setFont(m_font);
    m_fpsText.setString("FPS: " + std::to_string(m_fps));
    m_fpsText.setCharacterSize(30);
    m_fpsText.setFillColor(sf::Color::White);
    m_fpsText.setPosition(100, 350);
}

void SettingsMenu::setupFPSBar()
{
    m_fpsBarBackground.setSize(sf::Vector2f(300, 20));
    m_fpsBarBackground.setFillColor(sf::Color(100, 100, 100));
    m_fpsBarBackground.setPosition(100, 400);

    m_fpsBarForeground.setSize(sf::Vector2f((m_fps / 240.0f) * 300.0f, 20));
    m_fpsBarForeground.setFillColor(sf::Color::Green);
    m_fpsBarForeground.setPosition(100, 400);
}

void SettingsMenu::updateVolumeBar()
{
    m_volumeBarForeground.setSize(sf::Vector2f(m_volume * 3, 20));
    m_soundManager.setAllMusicVolume(m_volume); // Mise à jour du volume sonore
}

void SettingsMenu::updateFPSBar()
{
    m_fpsBarForeground.setSize(sf::Vector2f((m_fps / 240.0f) * 300.0f, 20));
}

void SettingsMenu::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Up)
        {
            m_volume = std::min(100.0f, m_volume + 5.0f);
        }
        else if (event.key.code == sf::Keyboard::Down)
        {
            m_volume = std::max(0.0f, m_volume - 5.0f);
        }
        else if (event.key.code == sf::Keyboard::Right)
        {
            m_fps = std::min(240, m_fps + 10);
        }
        else if (event.key.code == sf::Keyboard::Left)
        {
            m_fps = std::max(30, m_fps - 10);
        }
        else if (event.key.code == sf::Keyboard::Escape)
        {
            // Retour au menu principal
            // Remplacez "ChangerEtat" par la fonction pour revenir au menu dans votre moteur
            std::cout << "Retour au menu principal." << std::endl;
        }

        m_volumeText.setString("Volume: " + std::to_string(static_cast<int>(m_volume)));
        m_fpsText.setString("FPS: " + std::to_string(m_fps));
        updateVolumeBar();
        updateFPSBar();
    }
    else if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);

            // Gestion du volume
            sf::FloatRect volumeBounds = m_volumeBarBackground.getGlobalBounds();
            if (volumeBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
            {
                float newVolume = (mousePos.x - volumeBounds.left) / volumeBounds.width * 100.0f;
                m_volume = std::clamp(newVolume, 0.0f, 100.0f);
                m_volumeText.setString("Volume: " + std::to_string(static_cast<int>(m_volume)));
                updateVolumeBar();
            }

            // Gestion des FPS
            sf::FloatRect fpsBounds = m_fpsBarBackground.getGlobalBounds();
            if (fpsBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
            {
                float newFPS = (mousePos.x - fpsBounds.left) / fpsBounds.width * 240.0f;
                m_fps = std::clamp(static_cast<int>(newFPS), 30, 240);
                m_fpsText.setString("FPS: " + std::to_string(m_fps));
                updateFPSBar();
            }
        }
    }
}

void SettingsMenu::update()
{
    // Logique de mise à jour supplémentaire si nécessaire
}

void SettingsMenu::render()
{
    m_window.draw(m_titleText);
    m_window.draw(m_volumeText);
    m_window.draw(m_volumeBarBackground);
    m_window.draw(m_volumeBarForeground);
    m_window.draw(m_fpsText);
    m_window.draw(m_fpsBarBackground);
    m_window.draw(m_fpsBarForeground);
}

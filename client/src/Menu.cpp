#include "../include/Menu.hpp"
#include <iostream>

Menu::Menu(sf::RenderWindow& window) 
    : m_window(window)
    , m_hoveredItem(-1) {
    if (!loadFont()) {
        std::cerr << "Erreur : Impossible de charger la police !" << std::endl;
    }

    if (!loadMusic()) {
        std::cerr << "Erreur : Impossible de charger la musique !" << std::endl;
    } else {
        setupMusic();
    }

    setupTitle();
    setupFooter();
    setupCredits();
}

bool Menu::loadFont() {
    return m_font.loadFromFile("./assets/fonts/ZenDots-Regular.ttf");
}

bool Menu::loadMusic() {
    return m_music.openFromFile("./assets/music/background.mp3");
}

void Menu::setupMusic() {
    m_music.setLoop(true);
    m_music.play();
}

void Menu::setupTitle() {
    m_title.setFont(m_font);
    m_title.setString("R-Type");
    m_title.setCharacterSize(90);
    m_title.setFillColor(sf::Color::Blue);

    sf::Vector2u windowSize = m_window.getSize();
    float centerX = windowSize.x / 2.0f;

    m_title.setPosition(centerX, 130); 
    m_title.setOrigin(m_title.getLocalBounds().width / 2, 0);
}

void Menu::setupFooter() {
    m_footer.setFont(m_font);
    m_footer.setString("Epitech Project 2024");
    m_footer.setCharacterSize(20);
    m_footer.setFillColor(sf::Color::White);

    sf::Vector2u windowSize = m_window.getSize();
    float centerX = windowSize.x / 2.0f;

    m_footer.setPosition(centerX, windowSize.y - 50);
    m_footer.setOrigin(m_footer.getLocalBounds().width / 2, 0);
}

void Menu::setupCredits() {
    std::vector<std::string> creditNames = {
        "Pablo Peiro",
        "Arthur Baudelot",
        "Mathis Liberati",
        "Alexandre Lorgeoux",
        "Mathis Champin",
    };

    sf::Vector2u windowSize = m_window.getSize();
    float creditYPosition = windowSize.y - 50; 

    for (const auto& name : creditNames) {
        sf::Text credit(name, m_font, 15);
        credit.setFillColor(sf::Color::White);
        credit.setPosition(windowSize.x - 10, creditYPosition);  
        credit.setOrigin(credit.getLocalBounds().width, credit.getLocalBounds().height); 
        m_credits.push_back(credit);
        creditYPosition -= 20;  
    }
}

void Menu::addOption(const std::string& text, std::function<void()> callback) {
    sf::Text option(text, m_font, 40);
    sf::Vector2u windowSize = m_window.getSize();
    float centerX = windowSize.x / 2.0f;
    
    option.setPosition(centerX, 0);
    option.setFillColor(sf::Color::White);
    option.setOrigin(option.getLocalBounds().width / 2, 0);
    
    m_options.push_back(option);
    m_callbacks.push_back(callback ? callback : [](){}); 
}

bool Menu::isMouseOverOption(const sf::Text& option, float mouseX, float mouseY) const {
    sf::FloatRect bounds = option.getGlobalBounds();
    bounds.left -= 5;
    bounds.top -= 5;
    bounds.width += 10;
    bounds.height += 10;
    
    return bounds.contains(mouseX, mouseY);
}

void Menu::updateHoveredItem(float mouseX, float mouseY) {
    m_hoveredItem = -1;
    for (size_t i = 0; i < m_options.size(); ++i) {
        if (isMouseOverOption(m_options[i], mouseX, mouseY)) {
            m_hoveredItem = static_cast<int>(i);
            break;
        }
    }
}

void Menu::update() {
    sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
    updateHoveredItem(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

void Menu::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed && 
        event.mouseButton.button == sf::Mouse::Left) {
        
        sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
        
        for (size_t i = 0; i < m_options.size(); ++i) {
            if (isMouseOverOption(m_options[i], mousePos.x, mousePos.y)) {
                std::cout << m_options[i].getString().toAnsiString() << " sélectionné !" << std::endl;
                
                if (m_callbacks[i]) {
                    m_callbacks[i]();
                }
                
                if (m_options[i].getString() == "Quitter") {
                    m_window.close();
                }
                break;
            }
        }
    }
}

void Menu::render() {
    m_window.draw(m_title);

    sf::Vector2u windowSize = m_window.getSize();
    float centerY = windowSize.y / 2.0f;
    float totalHeight = m_options.size() * 50;
    float startY = centerY - (totalHeight / 2.0f);
    
    for (size_t i = 0; i < m_options.size(); ++i) {
        m_options[i].setPosition(
            m_options[i].getPosition().x,
            startY + i * 50
        );
        
        if (static_cast<int>(i) == m_hoveredItem) {
            m_options[i].setFillColor(sf::Color::Blue);
            m_options[i].setScale(1.1f, 1.1f);
        } else {
            m_options[i].setFillColor(sf::Color::White);
            m_options[i].setScale(1.0f, 1.0f);
        }
        
        m_window.draw(m_options[i]);
    }

    m_window.draw(m_footer);

    for (const auto& credit : m_credits) {
        m_window.draw(credit);
    }
}

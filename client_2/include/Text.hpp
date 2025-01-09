#pragma once

    #include <SFML/Graphics.hpp>
    #include <string>
    #include <iostream>

class TextManager {
    public:
        TextManager(const std::string& fontFile, unsigned int fontSize = 30) {
            if (!_font.loadFromFile(fontFile)) {
                std::cerr << "Error loading font from file: " << fontFile << std::endl;
            }
            _text.setFont(_font);
            _text.setCharacterSize(fontSize);
            _text.setFillColor(sf::Color::White);
        }

        void displayText(sf::RenderWindow &window, const std::string &text, float x, float y) {
            _text.setString(text);
            _text.setPosition(x, y);
            window.draw(_text);
        }

        void setTextColor(const sf::Color& color) {
            _text.setFillColor(color);
        }

        void setTextSize(unsigned int size) {
            _text.setCharacterSize(size);
        }

    private:
        sf::Font _font;
        sf::Text _text;
};

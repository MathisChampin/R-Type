#include "../include/Shoot.hpp"
#include <iostream>
#include <filesystem>

// Constructeur
Shoot::Shoot(int id, const sf::Vector2f &startPosition)
    : _id(id), m_position(startPosition)
{
    m_shape.setSize(sf::Vector2f(9.0f, 9.0f));
    m_shape.setFillColor(sf::Color::White);
    m_shape.setPosition(m_position);

    std::cout << "[Shoot] Position initiale : x = " << m_position.x << ", y = " << m_position.y << std::endl;
}

// Méthode d'affichage
void Shoot::render(sf::RenderWindow &window)
{
    window.draw(m_shape);
}

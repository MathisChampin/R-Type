#include "../include/Shoot.hpp"
#include <SFML/Graphics.hpp>
#include <stdexcept>

Shoot::Shoot(int id, const sf::Vector2f &startPosition)
    : _id(id), m_position(startPosition)
{
    m_shape = sf::CircleShape(5);
    m_shape.setFillColor(sf::Color(150, 50, 250));

    m_shape.setOutlineThickness(1);
    m_shape.setOutlineColor(sf::Color(255, 255, 255));

    m_shape.setPosition(m_position);
}

void Shoot::render(sf::RenderWindow &window)
{
    window.draw(m_shape);
}

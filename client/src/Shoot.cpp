#include "../include/Shoot.hpp"
#include "../include/client/Sprite.hpp"

Shoot::Shoot(int id, const sf::Vector2f& startPosition, const std::string& configPath)
    : _id(id), m_position(startPosition)
{
    Sprite sprite(configPath);
    sf::Texture texture;

    // Charger la texture depuis le fichier
    if (!texture.loadFromFile(configPath)) {
        // Gérer l'erreur de chargement de la texture
        // Vous pourriez lancer une exception ou utiliser une texture par défaut ici
    }
    m_shape.setTexture(&texture);
    m_shape.setSize(sf::Vector2f(texture.getSize()));
    m_shape.setPosition(m_position);
}

void Shoot::render(sf::RenderWindow& window)
{
    window.draw(m_shape);
}
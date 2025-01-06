#include "../include/Player.hpp"
#include <iostream>

Player::Player()
    : velocityX(0), velocityY(0), isJumping(false), frameWidth(64), frameHeight(64),
      totalFrames(8), currentFrame(0), animationSpeed(0.15f), timeSinceLastFrame(0.0f)
{
    if (!texture.loadFromFile("./assets/player.png")) {
        std::cerr << "Texture not found" << std::endl;
    }
    setTexture(texture);

    // Initialisation du rectangle pour la première frame
    frameRect = sf::IntRect(0, 0, frameWidth, frameHeight);
    setTextureRect(frameRect);

    // Positionner en bas à gauche de l'écran
    setPosition(0, 835); // Position de départ
}

void Player::handleInput(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Left)
            moveLeft();
        if (event.key.code == sf::Keyboard::Right)
            moveRight();
        if (event.key.code == sf::Keyboard::Space && !isJumping)
            jump();
    } else if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right) {
            velocityX = 0; // Arrêter l'animation lorsque le joueur s'arrête
        }
    }
}

void Player::moveLeft() { 
    velocityX = -5; 
    frameRect.top = 64; // Ligne pour marche à gauche
}
void Player::moveRight() { 
    velocityX = 5; 
    frameRect.top = 0; // Ligne pour marche à droite
}
void Player::jump() {
    if (!isJumping) {
        velocityY = jumpHeight;
        isJumping = true;

        // Frame pour le saut
        frameRect.top = 128; // Ligne pour le saut
        frameRect.left = 0;  // Première frame de saut
        setTextureRect(frameRect);
    }
}

void Player::updateAnimation(float deltaTime) {
    if (velocityX != 0 && !isJumping) { // Animation uniquement si le joueur bouge
        timeSinceLastFrame += deltaTime;

        if (timeSinceLastFrame >= animationSpeed) {
            timeSinceLastFrame = 0.0f;
            currentFrame = (currentFrame + 1) % totalFrames;

            // Mettre à jour la frame de la ligne correspondante
            frameRect.left = currentFrame * frameWidth;
            setTextureRect(frameRect);
        }
    } else if (isJumping) {
        // Gérer le saut : garder une frame fixe pendant le saut
        frameRect.left = 0; // Première frame de saut
        setTextureRect(frameRect);
    } else {
        // Gérer l'arrêt : afficher la première frame par défaut
        frameRect.left = 0;
        setTextureRect(frameRect);
    }
}

void Player::update(float deltaTime) {
    // Appliquer la gravité
    if (isJumping) {
        velocityY += gravity;
    }

    // Déplacer le joueur
    move(velocityX, velocityY);

    // Empêcher le joueur de descendre sous le sol
    if (getPosition().y >= 835) {
        isJumping = false;
        velocityY = 0;
        setPosition(getPosition().x, 835);

        // Retour à l'animation par défaut
        frameRect.top = 0; // Ligne par défaut
        frameRect.left = 0;
        setTextureRect(frameRect);
    }

    // Mettre à jour l'animation
    updateAnimation(deltaTime);
}

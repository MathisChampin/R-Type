#include "../include/Player.hpp"
#include <iostream>

Player::Player()
    : velocityX(5), velocityY(64), isJumping(false), frameWidth(64), frameHeight(64),
      totalFrames(8), currentFrame(0), animationSpeed(0.15f), timeSinceLastFrame(0.0f)
{
    if (!texture.loadFromFile("./assets/player.png")) {
        std::cerr << "Texture not found" << std::endl;
    }
    setTexture(texture);

    frameRect = sf::IntRect(0, 0, frameWidth, frameHeight);
    setTextureRect(frameRect);
    posX = 0;
    posY = 835;
    setPosition(posX, posY);
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
            velocityX = 0;
        }
    }
}

void Player::moveLeft() { 
    velocityX = -5; 
    frameRect.top = 64;
}
void Player::moveRight() { 
    velocityX = 5; 
    frameRect.top = 0;
}
void Player::jump() {
    if (!isJumping) {
        velocityY = jumpHeight;
        isJumping = true;
        frameRect.top = 128;
        frameRect.left = 0;
        setTextureRect(frameRect);
    }
}

void Player::updateAnimation(float deltaTime) {
    if (velocityX != 0 && !isJumping) {
        timeSinceLastFrame += deltaTime;

        if (timeSinceLastFrame >= animationSpeed) {
            timeSinceLastFrame = 0.0f;
            currentFrame = (currentFrame + 1) % totalFrames;
            frameRect.left = currentFrame * frameWidth;
            setTextureRect(frameRect);
        }
    } else if (isJumping) {
        frameRect.left = 0;
        setTextureRect(frameRect);
    } else {
        frameRect.left = 0;
        setTextureRect(frameRect);
    }
}

void Player::update(float deltaTime) {
    if (isJumping) {
        velocityY += gravity;
    }
    move(velocityX, velocityY);
    if (getPosition().y >= 835) {
        isJumping = false;
        velocityY = 0;
        setPosition(getPosition().x, 835);
        frameRect.top = 0;
        frameRect.left = 0;
        setTextureRect(frameRect);
    }
    updateAnimation(deltaTime);
}

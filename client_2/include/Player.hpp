#pragma once
#include <SFML/Graphics.hpp>

class Player : public sf::Sprite {
    public:
        Player();
        void handleInput(const sf::Event& event);
        void update(float deltaTimem);
    private:
        sf::Texture texture;
        sf::IntRect frameRect;

        float velocityX;
        float velocityY;
        bool isJumping;
        const float gravity = 0.5f;
        const float jumpHeight = -12.0f;
    
        int frameWidth;
        int frameHeight;
        int totalFrames;
        int currentFrame;
        float animationSpeed;
        float timeSinceLastFrame;

        void moveLeft();
        void moveRight();
        void jump();
        void updateAnimation(float deltaTime);

};

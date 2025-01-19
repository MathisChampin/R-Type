#include "../include/Game.hpp"
#include <iostream>

Game::Game(registry ecs):
    window(sf::VideoMode(1920, 1080), "Game2", sf::Style::Default), _ecs(ecs), background(),
    player("./assets/player.png", 100, 750, 240, 160, 8, 0.1f), text("./assets/Roboto-Black.ttf") {
    window.setFramerateLimit(60);

    _ecs.createPlayer();
    _ecs.createEnemy();

     if (!playButtonTexture.loadFromFile("./assets/play.png")) {
        std::cerr << "Failed to load play button texture!" << std::endl;
    }
    if (!exitButtonTexture.loadFromFile("./assets/exit.png")) {
        std::cerr << "Failed to load exit button texture!" << std::endl;
    }

    playButtonSprite.setTexture(playButtonTexture);
    playButtonSprite.setPosition(860, 400);

    exitButtonSprite.setTexture(exitButtonTexture);
    exitButtonSprite.setPosition(860, 500);

    playButtonSprite.setScale(2.0f, 2.0f);
    exitButtonSprite.setScale(2.0f, 2.0f);
    if (!titleFont.loadFromFile("./assets/Roboto-Black.ttf")) {
        std::cerr << "Failed to load title font!" << std::endl;
    }

    if (!endGameFont.loadFromFile("./assets/Roboto-Black.ttf")) {
        std::cerr << "Failed to load title font!" << std::endl;
    }
    titleText.setFont(titleFont);
    titleText.setString("GAME MENU");
    titleText.setCharacterSize(100);
    titleText.setFillColor(sf::Color::White);
    titleText.setStyle(sf::Text::Bold);
    titleText.setPosition(640, 100);
}

void Game::run() {
    sf::Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        handleInput();
        update(deltaTime);
        render();
    }
}

void Game::handleMenuInput()
{
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            sf::Vector2f playPosition = playButtonSprite.getPosition();
            sf::Vector2f playSize(
                playButtonTexture.getSize().x * playButtonSprite.getScale().x,
                playButtonTexture.getSize().y * playButtonSprite.getScale().y
            );

            if (mousePos.x >= playPosition.x && mousePos.x <= playPosition.x + playSize.x &&
                mousePos.y >= playPosition.y && mousePos.y <= playPosition.y + playSize.y) {
                gameState = GameState::PLAYING;
            }

            sf::Vector2f exitPosition = exitButtonSprite.getPosition();
            sf::Vector2f exitSize(
                exitButtonTexture.getSize().x * exitButtonSprite.getScale().x,
                exitButtonTexture.getSize().y * exitButtonSprite.getScale().y
            );

            if (mousePos.x >= exitPosition.x && mousePos.x <= exitPosition.x + exitSize.x &&
                mousePos.y >= exitPosition.y && mousePos.y <= exitPosition.y + exitSize.y) {
                window.close();
            }
        }
    }
}



void Game::handleInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            if (gameState == GameState::PLAYING) {
                gameState = GameState::MENU;
            } else if (gameState == GameState::MENU || gameState == GameState::PAUSED) {
                gameState = GameState::PLAYING;
            } else if (gameState == GameState::WIN || gameState == GameState::LOSE) {
                gameState = GameState::MENU;
            }
        }

        if (gameState == GameState::MENU) {
            handleMenuInput();
        } else if (gameState == GameState::PLAYING) {
            if (event.key.code == sf::Keyboard::Left) {
                _ecs.movePlayer(component::controllable::Left);
                player.setPosition(_ecs.getPlayerPosition());
            } else if (event.key.code == sf::Keyboard::Right) {
                _ecs.movePlayer(component::controllable::Right);
                player.setPosition(_ecs.getPlayerPosition());
            } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                _ecs.movePlayer(component::controllable::Shoot6);
            } else if (event.key.code == sf::Keyboard::Space) {
                _ecs.movePlayer(component::controllable::Clear);
            }
        }
    }
}



void Game::renderGameOver() {
    sf::RectangleShape backgroundRect(sf::Vector2f(1920, 1080));
    backgroundRect.setFillColor(sf::Color(0, 0, 0, 200));
    window.draw(backgroundRect);

    sf::Text gameOverText;
    gameOverText.setFont(endGameFont);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(100);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setStyle(sf::Text::Bold);

    sf::FloatRect textBounds = gameOverText.getLocalBounds();
    gameOverText.setOrigin(textBounds.width / 2, textBounds.height / 2);
    gameOverText.setPosition(window.getSize().x / 2, window.getSize().y / 2 - 100);
    window.draw(gameOverText);

    sf::Text returnText;
    returnText.setFont(endGameFont);
    returnText.setString("Press ESC to return to menu");
    returnText.setCharacterSize(40);
    returnText.setFillColor(sf::Color::White);

    textBounds = returnText.getLocalBounds();
    returnText.setOrigin(textBounds.width / 2, textBounds.height / 2);
    returnText.setPosition(window.getSize().x / 2, window.getSize().y / 2 + 50);
    window.draw(returnText);
}


void Game::renderGameWin() {
    sf::RectangleShape backgroundRect(sf::Vector2f(1920, 1080));
    backgroundRect.setFillColor(sf::Color(0, 0, 0, 200));
    window.draw(backgroundRect);

    sf::Text winText;
    winText.setFont(endGameFont);
    winText.setString("YOU WIN!");
    winText.setCharacterSize(100);
    winText.setFillColor(sf::Color::Green);
    winText.setStyle(sf::Text::Bold);

    sf::FloatRect textBounds = winText.getLocalBounds();
    winText.setOrigin(textBounds.width / 2, textBounds.height / 2);
    winText.setPosition(window.getSize().x / 2, window.getSize().y / 2 - 100);
    window.draw(winText);

    sf::Text returnText;
    returnText.setFont(endGameFont);
    returnText.setString("Press ESC to return to menu");
    returnText.setCharacterSize(40);
    returnText.setFillColor(sf::Color::White);

     textBounds = returnText.getLocalBounds();
    returnText.setOrigin(textBounds.width / 2, textBounds.height / 2);
    returnText.setPosition(window.getSize().x / 2, window.getSize().y / 2 + 50);
    window.draw(returnText);
}


void Game::update(float deltaTime)
{
    background.moveParallax();
    if (gameState == GameState::PLAYING) {
        player.update(deltaTime);
        _ecs.update(deltaTime);
        if (_ecs.updateGame() == 1)
            gameState = GameState::LOSE;
        if (_ecs.updateGame() == 2)
            gameState = GameState::WIN;
    }
}

void Game::renderMenu()
{
    window.draw(titleText);

    window.draw(playButtonSprite);
    window.draw(exitButtonSprite);
}

void Game::render() {
    window.clear();

    background.drawParallax(window);

    if (gameState == GameState::MENU) {
        renderMenu();
    } else if (gameState == GameState::PLAYING) {
        _ecs.check_lose(window);
        if (!_ecs.checkPlayer())
            player.drawSprite(window);
        _ecs.drawEnemies(window);
        _ecs.drawShoots(window);
        text.displayText(window, "Score:", 100, 0);
        text.displayText(window, std::to_string(_ecs.getScorePlayer()), 210, 2);
        text.displayText(window, "Life:", 1700, 0);
        text.displayText(window, std::to_string(_ecs.getLifePlayer()), 1780, 2);
    } else if (gameState == GameState::WIN) {
        renderGameWin();
    } else if (gameState == GameState::LOSE) {
        renderGameOver();
    }

    window.display();
}


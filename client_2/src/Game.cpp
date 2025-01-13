#include "../include/Game.hpp"
#include <iostream>

Game::Game(registry ecs):
    window(sf::VideoMode(1920, 1080), "Game2", sf::Style::Default), _ecs(ecs), background(),
    player("./assets/player.png", 100, 750, 240, 160, 8, 0.1f), text("./assets/Roboto-Black.ttf") {
    window.setFramerateLimit(60);

    _ecs.createPlayer();
    _ecs.createEnemy();
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

void Game::handleInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape) {
            window.close();
        }
        if (event.key.code == sf::Keyboard::Left) {
            _ecs.movePlayer(component::controllable::Left);
            player.setPosition(_ecs.getPlayerPosition());
        } else if (event.key.code == sf::Keyboard::Right) {
            _ecs.movePlayer(component::controllable::Right);
            player.setPosition(_ecs.getPlayerPosition());
        } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            _ecs.movePlayer(component::controllable::Shoot);
        } else if (event.key.code == sf::Keyboard::Space) {
            _ecs.movePlayer(component::controllable::Clear);
        }
    }
}

void Game::update(float deltaTime) {
    player.update(deltaTime);
    _ecs.update(deltaTime);
    background.moveParallax();
}

void Game::render() {
    window.clear();
    _ecs.check_lose(window);
    background.drawParallax(window);
    if (!_ecs.checkPlayer())
        player.drawSprite(window);
    _ecs.drawEnemies(window);
    _ecs.drawShoots(window);
    text.displayText(window, "Score:", 100, 0);
    text.displayText(window, std::to_string(_ecs.getScorePlayer()), 210, 2);
    text.displayText(window, "Life:", 1700, 0);
    text.displayText(window, std::to_string(_ecs.getLifePlayer()), 1780, 2);
    window.display();
}

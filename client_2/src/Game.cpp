#include "../include/Game.hpp"
#include <iostream>

Game::Game(registry ecs): window(sf::VideoMode(1920, 1080), "Game2", sf::Style::Default), _ecs(ecs), background(), player("./assets/player.png", 100, 750, 240, 160, 8, 0.1f) {
    window.setFramerateLimit(60);

    _ecs.createPlayer();
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
    }
}

void Game::update(float deltaTime) {
    player.update(deltaTime);
    background.moveParallax();
}

void Game::render() {
    window.clear();
    background.drawParallax(window);
    player.drawSprite(window);
    window.display();
}

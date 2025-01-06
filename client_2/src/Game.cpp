#include "../include/Game.hpp"
#include <iostream>

Game::Game() : window(sf::VideoMode(1920, 1080), "Game2", sf::Style::Default), background() {
    window.setFramerateLimit(60);
}

void Game::run() {
    sf::Clock clock; // Horloge pour calculer le deltaTime

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds(); // Temps écoulé depuis la dernière frame

        handleInput();
        update(deltaTime);
        render();
    }
}

void Game::handleInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.key.code == sf::Keyboard::Escape)
            window.close();
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        player.handleInput(event);
    }
}

void Game::update(float deltaTime) {
    background.moveParallax();
    player.update(deltaTime);
    for (auto& enemy : enemies) {
        enemy.update();
    }
}

void Game::render() {
    window.clear();
    background.drawParallax(window);
    window.draw(player);
    for (const auto& enemy : enemies) {
        window.draw(enemy);
    }
    window.display();
}

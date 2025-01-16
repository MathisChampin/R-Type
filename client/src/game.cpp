#include "Game.hpp"
#include <iostream>
#include <algorithm>

Game::Game(std::string ip, sf::RenderWindow &window, SkinType skinType, sf::Font &font, ParallaxBackground &playingBackground, SoundManager &soundManager)
    : _ip(ip),
      m_window(window),
      m_skinType(skinType),
      m_playingBackground(playingBackground),
      m_client(_ip),
      m_players(m_client),
      m_currentState(GameState::Playing),
      m_font(font),
      m_SoundManager(soundManager),
      m_previousLevel(0)
{
    m_life.initialize("./assets/life/hearts.png", 5, 15.f);
    m_score.initialize(m_font, 30, sf::Vector2f(20, 60));
    m_level.initialize(m_font, 30, sf::Vector2f(0, 60));
}

Game::~Game()
{
    m_enemies.clear();
    m_shoots.clear();
}

void Game::handleEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        processInput(event);
    }
}

void Game::processInput(sf::Event &event)
{
    if (event.type == sf::Event::Closed)
    {
        m_window.close();
    }
}

void Game::update(float deltaTime)
{

    if (m_currentState == GameState::Playing || m_currentState == GameState::PlayingInLobby)
    {
        m_players.handleInput();
        m_players.sendQueuedMovements();
        m_playingBackground.update(deltaTime);
    }
}

bool Game::AnimationLevel()
{
    int currentLevel = m_level.getLevel();

    if (currentLevel != m_previousLevel && (currentLevel == 3 || currentLevel == 4 || currentLevel == 5 || currentLevel == 6))
    {
        m_previousLevel = currentLevel;
        std::cout << "Changement de niveau détecté : " << currentLevel << std::endl;
        return true;
    }

    return false; // Pas de changement ou niveau non concerné
}

void Game::render(float deltaTime)
{
    // m_window.clear();
    if (m_currentState == GameState::Playing || m_currentState == GameState::PlayingInLobby)
    {
        m_playingBackground.render(m_window);
        _spriteMng.drawAll(m_window, sf::seconds(deltaTime));
        m_life.render(m_window);
        m_score.render(m_window);
        m_level.render(m_window);
    }
}

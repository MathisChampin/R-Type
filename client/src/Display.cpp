#include "../include/Game.hpp"
#include <iostream>
#include <queue>
#include <thread>
#include <chrono>

void Game::launch_getter(std::size_t id, NmpClient::SpriteInfo &sp)
{
    auto it = _mapHandlerPacket.find(id);
    if (it != _mapHandlerPacket.end())
    {
        it->second(sp);
    }
    else
    {
        std::cerr << "Erreur : Aucun handler pour l'id " << id << std::endl;
    }
}

void Game::handler_packets()
{
    if (!m_client.has_value()) {
        return;
    }

    auto data = m_client->get_data();
    if (!data.has_value()) {
        return;
    }

    auto p = data.value();
    if (p.getOpCode() == NmpClient::EVENT::EOI) {
        std::cout << "END OF FRAME" << std::endl;
        std::cout << "count before: " << _spriteMng.getSpriteCount() << std::endl;
        _spriteMng.eraseOldSprite(_containerEndFrameId);
        std::cout << "count after: " << _spriteMng.getSpriteCount() << std::endl;
        return;
    } else if (p.getOpCode() == NmpClient::EVENT::LIFE) {
        int newLife = p.getElem();
        std::cout << "LIFE: " << newLife << std::endl;
        m_life.updateLife(newLife);
    } else if (p.getOpCode() == NmpClient::EVENT::SCORE) {
        int newScore = p.getElem();
        std::cout << "SCORE: " << newScore << std::endl;
        m_score.updateScore(newScore);
    } else if (p.getOpCode() == NmpClient::EVENT::JOIN) {
        _spriteMng.eraseAll();
        if (m_client.has_value()) {
            m_client->_id = p.getId();
            std::cout << "new id" << p.getId() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }
    auto spriteInf = p.getSpriteInfo();
    _containerEndFrameId.insert(spriteInf.idClient);
    launch_getter(spriteInf.id, spriteInf);
}

void Game::get_player(NmpClient::SpriteInfo &sp)
{
    std::cout << "\thandle players: " << sp.idClient << std::endl;
    sf::Vector2f vecPos;
    vecPos.x = sp.x;
    vecPos.y = sp.y;
    auto sprite = _spriteMng.getSprite(sp.idClient);
    if (sprite != nullptr)
    {
        sprite.get()->setPosition(vecPos);
    }
    else
    {
        auto sprite = std::make_shared<Sprite>("../../client/config/player.json");
        sprite.get()->setPosition(vecPos);
        _spriteMng.addSprite(sprite, sp.idClient);
    }
    handler_packets();
}

void Game::get_ennemies5(NmpClient::SpriteInfo &sp)
{
    std::cout << "handle ennemies: " << sp.idClient << std::endl;
    sf::Vector2f vecPos;
    vecPos.x = sp.x;
    vecPos.y = sp.y;
    auto sprite = _spriteMng.getSprite(sp.idClient);
    if (sprite != nullptr)
    {
        sprite.get()->setPosition(vecPos);
    }
    else
    {
        auto sprite = std::make_shared<Sprite>("../../client/config/enemy5.json");
        sprite.get()->setPosition(vecPos);
        _spriteMng.addSprite(sprite, sp.idClient);
    }
    handler_packets();
}

void Game::get_ennemies4(NmpClient::SpriteInfo &sp)
{
    std::cout << "handle ennemies: " << sp.idClient << std::endl;
    sf::Vector2f vecPos;
    vecPos.x = sp.x;
    vecPos.y = sp.y;
    auto sprite = _spriteMng.getSprite(sp.idClient);
    if (sprite != nullptr)
    {
        sprite.get()->setPosition(vecPos);
    }
    else
    {
        auto sprite = std::make_shared<Sprite>("../../client/config/enemy4.json");
        sprite.get()->setPosition(vecPos);
        _spriteMng.addSprite(sprite, sp.idClient);
    }
    handler_packets();
}

void Game::get_ennemies3(NmpClient::SpriteInfo &sp)
{
    std::cout << "handle ennemies: " << sp.idClient << std::endl;
    sf::Vector2f vecPos;
    vecPos.x = sp.x;
    vecPos.y = sp.y;
    auto sprite = _spriteMng.getSprite(sp.idClient);
    if (sprite != nullptr)
    {
        sprite.get()->setPosition(vecPos);
    }
    else
    {
        auto sprite = std::make_shared<Sprite>("../../client/config/enemy3.json");
        sprite.get()->setPosition(vecPos);
        _spriteMng.addSprite(sprite, sp.idClient);
    }
    handler_packets();
}

void Game::get_ennemies2(NmpClient::SpriteInfo &sp)
{
    std::cout << "handle ennemies: " << sp.idClient << std::endl;
    sf::Vector2f vecPos;
    vecPos.x = sp.x;
    vecPos.y = sp.y;
    auto sprite = _spriteMng.getSprite(sp.idClient);
    if (sprite != nullptr)
    {
        sprite.get()->setPosition(vecPos);
    }
    else
    {
        auto sprite = std::make_shared<Sprite>("../../client/config/enemy2.json");
        sprite.get()->setPosition(vecPos);
        _spriteMng.addSprite(sprite, sp.idClient);
    }
    handler_packets();
}

void Game::get_ennemies(NmpClient::SpriteInfo &sp)
{
    std::cout << "\thandle ennemies: " << sp.idClient << std::endl;
    sf::Vector2f vecPos;
    vecPos.x = sp.x;
    vecPos.y = sp.y;
    auto sprite = _spriteMng.getSprite(sp.idClient);
    if (sprite != nullptr)
    {
        sprite.get()->setPosition(vecPos);
    }
    else
    {
        auto sprite = std::make_shared<Sprite>("../../client/config/enemy.json");
        sprite.get()->setPosition(vecPos);
        _spriteMng.addSprite(sprite, sp.idClient);
    }
    handler_packets();
}

void Game::get_shoots(NmpClient::SpriteInfo &sp)
{
    std::cout << "\thandle shoots: " << sp.idClient << std::endl;
    sf::Vector2f vecPos;
    vecPos.x = sp.x;
    vecPos.y = sp.y;
    auto sprite = _spriteMng.getSprite(sp.idClient);
    if (sprite != nullptr)
    {
        sprite.get()->setPosition(vecPos);
    }
    else
    {
        auto sprite = std::make_shared<Sprite>("../../client/config/shoot.json");
        sprite.get()->setPosition(vecPos);
        if (GameState::Playing == m_currentState){
            m_SoundManager.loadSound("shoot", "./assets/sound/Blaster.mp3");
            m_SoundManager.playSound("shoot");
        }
        _spriteMng.addSprite(sprite, sp.idClient);
    }
    handler_packets();
}

void Game::run()
{
    while (m_window.isOpen())
    {
        float deltaTime = m_clock.restart().asSeconds();
        std::cout << "BEGIN LOOP\n";
        handleEvents();

        if (m_currentState == GameState::Playing || m_currentState == GameState::PlayingInLobby) {
            handler_packets();
        }

        update(deltaTime);
        render(deltaTime);
        std::cout << "END LOOP" <<std::endl;
    }
}
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
    auto data = m_client.get_data();
    if (!data.has_value()) {return;}

    auto p = data.value();
    if (p.getOpCode() == NmpClient::EVENT::EOI)
    {
        std::cout << "END OF FRAME" << std::endl;
        std::cout << "count before: " << _spriteMng.getSpriteCount() << std::endl;
        
        _spriteMng.eraseOldSprite(_containerEndFrameId);
        std::cout << "count after: " << _spriteMng.getSpriteCount() << std::endl;
        return;
    }
    else if (p.getOpCode() == NmpClient::EVENT::INFO)
    {
        int newLife = p.getLife();
        int newScore = p.getScore();
        std::cout << "LIFE: " << newLife << std::endl;
        std::cout << "SCORE: " << newScore << std::endl;
        m_life.updateLife(newLife);
        m_score.updateScore(newScore);
    }
    else if (p.getOpCode() == NmpClient::EVENT::JOIN)
    {
        std::cout << "new level" << std::endl;
        std::cout << "size: " << _spriteMng.getSpriteCount() << std::endl;
        _spriteMng.eraseAll();
        m_client._id = p.getId();
        std::cout << "new id" << p.getId() << std::endl;
    }
    //if (p.getOpCode() == NmpClient::EVENT::SPRITE) {
        auto spriteInf = p.getSpriteInfo();
        _containerEndFrameId.insert(spriteInf.idClient);
        launch_getter(spriteInf.id, spriteInf);
    //}
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
        std::shared_ptr<Sprite> sprite;
        if (m_skinType == SkinType::SKIN1)
        {
            sprite = std::make_shared<Sprite>("../../client/config/player.json");
        }
        else if (m_skinType == SkinType::SKIN2)
        {
            sprite = std::make_shared<Sprite>("../../client/config/player2.json");
        }
        else if (m_skinType == SkinType::SKIN3)
        {
            sprite = std::make_shared<Sprite>("../../client/config/player3.json");
        }
        else if (m_skinType == SkinType::SKIN4)
        {
            sprite = std::make_shared<Sprite>("../../client/config/player4.json");
        }
        else if (m_skinType == SkinType::SKIN5)
        {
            sprite = std::make_shared<Sprite>("../../client/config/player5.json");
        }
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
        auto sprite = std::make_shared<Sprite>("../../client/config/player/shoot1.json");
        sprite.get()->setPosition(vecPos);
        if (GameState::Playing == m_currentState)
        {
            m_SoundManager.loadSound("shoot", "./assets/sound/Blaster.mp3");
            m_SoundManager.playSound("shoot");
        }
        _spriteMng.addSprite(sprite, sp.idClient);
    }
    handler_packets();
}

void Game::get_shoots6(NmpClient::SpriteInfo &sp)
{
    std::cout << "\thandle shoots: " << sp.idClient << std::endl;
    sf::Vector2f vecPos;
    vecPos.x = sp.x;
    vecPos.y = sp.y;
    std::cout << "position shoot 6 x = " << sp.x << "y = " << sp.y << std::endl;
    auto sprite = _spriteMng.getSprite(sp.idClient);
    if (sprite != nullptr)
    {
        sprite.get()->setPosition(vecPos);
    }
    else
    {
        auto sprite = std::make_shared<Sprite>("../../client/config/player/shoot5.json");
        sprite.get()->setPosition(vecPos);
        if (GameState::Playing == m_currentState){
            m_SoundManager.loadSound("shoot", "./assets/sound/Blaster.mp3");
            m_SoundManager.playSound("shoot");
        }
        _spriteMng.addSprite(sprite, sp.idClient);
    }
    handler_packets();
}

void Game::get_shoots2(NmpClient::SpriteInfo &sp)
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
        auto sprite = std::make_shared<Sprite>("../../client/config/enemy/shoot2.json");
        sprite.get()->setPosition(vecPos);
        if (GameState::Playing == m_currentState){
            m_SoundManager.loadSound("shoot", "./assets/sound/Blaster.mp3");
            m_SoundManager.playSound("shoot");
        }
        _spriteMng.addSprite(sprite, sp.idClient);
    }
    handler_packets();
}

void Game::get_shoots3(NmpClient::SpriteInfo &sp)
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
        auto sprite = std::make_shared<Sprite>("../../client/config/player/shoot2.json");
        sprite.get()->setPosition(vecPos);
        if (GameState::Playing == m_currentState){
            m_SoundManager.loadSound("shoot", "./assets/sound/Blaster.mp3");
            m_SoundManager.playSound("shoot");
        }
        _spriteMng.addSprite(sprite, sp.idClient);
    }
    handler_packets();
}

void Game::get_shoots7(NmpClient::SpriteInfo &sp)
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
        auto sprite = std::make_shared<Sprite>("../../client/config/enemy/shoot2.json");
        sprite.get()->setPosition(vecPos);
        if (GameState::Playing == m_currentState){
            m_SoundManager.loadSound("shoot", "./assets/sound/Blaster.mp3");
            m_SoundManager.playSound("shoot");
        }
        _spriteMng.addSprite(sprite, sp.idClient);
    }
    handler_packets();
}
void Game::get_shoots8(NmpClient::SpriteInfo &sp)
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
        auto sprite = std::make_shared<Sprite>("../../client/config/enemy/shoot3.json");
        sprite.get()->setPosition(vecPos);
        if (GameState::Playing == m_currentState){
            m_SoundManager.loadSound("shoot", "./assets/sound/Blaster.mp3");
            m_SoundManager.playSound("shoot");
        }
        _spriteMng.addSprite(sprite, sp.idClient);
    }
    handler_packets();
}

void Game::get_shoots9(NmpClient::SpriteInfo &sp)
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
        auto sprite = std::make_shared<Sprite>("../../client/config/enemy/shoot4.json");
        sprite.get()->setPosition(vecPos);
        if (GameState::Playing == m_currentState){
            m_SoundManager.loadSound("shoot", "./assets/sound/Blaster.mp3");
            m_SoundManager.playSound("shoot");
        }
        _spriteMng.addSprite(sprite, sp.idClient);
    }
    handler_packets();
}

void Game::get_shoots11(NmpClient::SpriteInfo &sp)
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
        auto sprite = std::make_shared<Sprite>("../../client/config/enemy/shoot1.json");
        sprite.get()->setPosition(vecPos);
        if (GameState::Playing == m_currentState){
            m_SoundManager.loadSound("shoot", "./assets/sound/Blaster.mp3");
            m_SoundManager.playSound("shoot");
        }
        _spriteMng.addSprite(sprite, sp.idClient);
    }
    handler_packets();
}

void Game::get_shoots10(NmpClient::SpriteInfo &sp)
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
        auto sprite = std::make_shared<Sprite>("../../client/config/enemy/shoot5.json");
        sprite.get()->setPosition(vecPos);
        if (GameState::Playing == m_currentState){
            m_SoundManager.loadSound("shoot", "./assets/sound/Blaster.mp3");
            m_SoundManager.playSound("shoot");
        }
        _spriteMng.addSprite(sprite, sp.idClient);
    }
    handler_packets();
}

void Game::get_shoots4(NmpClient::SpriteInfo &sp)
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
        auto sprite = std::make_shared<Sprite>("../../client/config/player/shoot3.json");
        sprite.get()->setPosition(vecPos);
        if (GameState::Playing == m_currentState){
            m_SoundManager.loadSound("shoot", "./assets/sound/Blaster.mp3");
            m_SoundManager.playSound("shoot");
        }
        _spriteMng.addSprite(sprite, sp.idClient);
    }
    handler_packets();
}

void Game::get_shoots5(NmpClient::SpriteInfo &sp)
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
        auto sprite = std::make_shared<Sprite>("../../client/config/player/shoot4.json");
        sprite.get()->setPosition(vecPos);
        if (GameState::Playing == m_currentState){
            m_SoundManager.loadSound("shoot", "./assets/sound/Blaster.mp3");
            m_SoundManager.playSound("shoot");
        }
        _spriteMng.addSprite(sprite, sp.idClient);
    }
    handler_packets();
}

void Game::get_powerup_life(NmpClient::SpriteInfo &sp)
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
        auto sprite = std::make_shared<Sprite>("../../client/config/powerup_life.json");
        sprite.get()->setPosition(vecPos);
        _spriteMng.addSprite(sprite, sp.idClient);
    }
    handler_packets();
}

void Game::get_powerup_move(NmpClient::SpriteInfo &sp)
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
        auto sprite = std::make_shared<Sprite>("../../client/config/powerup_move.json");
        sprite.get()->setPosition(vecPos);
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

        if (m_currentState == GameState::Playing || m_currentState == GameState::PlayingInLobby)
        {
            handler_packets();
        }

        update(deltaTime);
        render(deltaTime);
        std::cout << "END LOOP" << std::endl;
    }
}
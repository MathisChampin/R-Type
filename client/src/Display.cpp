#include "../include/Game.hpp"
#include <iostream>
#include <queue>

// plusieurs cas diiférents
// si id pas trouvé -> j'ajoute dans la map
// si id trouvé -> update
// si pas mentionné erase -> probablement autre fonction

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
    if (!data.has_value())
    {
        return;
    }
    auto p = data.value();
    if (p.getOpCode() != NmpClient::EVENT::SPRITE)
    {
        std::cout << "END OF FRAME" << std::endl;
        std::cout << "count berfore: " << _spriteMng.getSpriteCount() << std::endl;
        // _spriteMng.eraseOldSprite(_queuePacket);
        std::cout << "count after: " << _spriteMng.getSpriteCount() << std::endl;

        return;
    }
    _queuePacket.push(p);
    auto spriteInf = p.getSpriteInfo();
    std::cout << "id sprite: " << spriteInf.id << std::endl;
    launch_getter(spriteInf.id, spriteInf);
}

void Game::get_player(NmpClient::SpriteInfo &sp)
{
    std::cout << "handle players" << std::endl;
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
        auto sprite = std::make_shared<Sprite>("../../client/config/enemy.json");
        sprite.get()->setPosition(vecPos);
        _spriteMng.addSprite(sprite, sp.idClient);
    }
    handler_packets();
}

void Game::get_shoots(NmpClient::SpriteInfo &sp)
{
    std::cout << "handle shoots: " << sp.idClient << std::endl;
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
        _spriteMng.addSprite(sprite, sp.idClient);
    }
    handler_packets();
}

void Game::run()
{
    // std::queue<NmpClient::Packet> queuePacket;

    while (m_window.isOpen())
    {
        float deltaTime = m_clock.restart().asSeconds();
        ////std::cout << "BEGIN LOOP\n";
        handleEvents();
        // std::cout << "JE SORS DE RENDER" << std::endl;
        // std::cout << "JE SORS DE HANDLEEVENTS" << std::endl;

        handler_packets();

        update(deltaTime);
        render(deltaTime);
        // std::cout << "END LOOP" <<std::endl;
    }
}
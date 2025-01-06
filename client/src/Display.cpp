#include "../include/Game.hpp"
#include <iostream>
#include <queue>


//plusieurs cas diiférents
//si id pas trouvé -> j'ajoute dans la map
//si id trouvé -> update
//si pas mentionné erase -> probablement autre fonction

void Game::get_player(NmpClient::Packet &data)
{
    auto spriteInfo = data.getSpriteInfo();

    if (spriteInfo.id == 1) {
        std::cout << "handle players" << std::endl;
        sf::Vector2f vecPos;
        vecPos.x = spriteInfo.x;
        vecPos.y = spriteInfo.y;
        auto sprite = _spriteMng.getSprite(spriteInfo.idClient);
        if (sprite != nullptr) {
            std::cout << "\tupdate" << std::endl;
            sprite.get()->setPosition(vecPos);
            std::cout << "test: " << sprite.get()->getPosition().x << std::endl; 
        } else {
            std::cout << "\tcreate" << std::endl;
            auto sprite = std::make_shared<Sprite>("../../client/config/player.json");
            sprite.get()->setPosition(vecPos);
            _spriteMng.addSprite(sprite, spriteInfo.idClient);
            std::cout << "test: " << sprite.get()->getPosition().x << std::endl; 
        }
    }
}

void Game::get_ennemies(NmpClient::Packet &data)
{
    auto spriteInfo = data.getSpriteInfo();

    if (spriteInfo.id == 2) {
        std::cout << "handle ennemies" << std::endl;
        if (_spriteMng.getSprite(spriteInfo.idClient) != nullptr) {
            std::cout << "\tupdate" << std::endl;
        } else {
            std::cout << "\tcreate" << std::endl;
        }

    }
}

void Game::get_shoots(NmpClient::Packet &data)
{
    auto spriteInfo = data.getSpriteInfo();

    if (spriteInfo.id == 3) {
        std::cout << "handle shoots" << std::endl;
        if (_spriteMng.getSprite(spriteInfo.idClient) != nullptr) {
            std::cout << "\tupdate" << std::endl;
        } else {
            std::cout << "\tcreate" << std::endl;
        }
    }
}

void Game::run()
{
    std::queue<NmpClient::Packet> queuePacket;

    while (m_window.isOpen()) {
        float deltaTime = m_clock.restart().asSeconds();
        //std::cout << "BEGIN LOOP\n";
        handleEvents();
        //std::cout << "JE SORS DE RENDER" << std::endl;
        //std::cout << "JE SORS DE HANDLEEVENTS" << std::endl;
        auto packet = m_client.get_data();
        if (!packet.has_value()) {
            std::cout << "TEST" << std::endl;
            continue;
        }
        auto p = packet.value();

        if (p.getOpCode() != NmpClient::EVENT::SPRITE) {
            std::cout << "END OF FRAME" << std::endl;
            continue;
        }
        queuePacket.push(p);
        get_ennemies(p);
        //std::cout << "je sors de get ennemies" << std::endl;
        get_player(p);
        //std::cout << "je sors de get player" << std::endl;
        get_shoots(p);
        //std::cout << "je sors de get shoot" << std::endl;
        _spriteMng.drawAll(m_window);
        update(deltaTime);
        render();
        //std::cout << "END LOOP" <<std::endl;
    }
}
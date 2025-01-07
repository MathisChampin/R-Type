#include "../include/Game.hpp"
#include <iostream>
#include <queue>


//plusieurs cas diiférents
//si id pas trouvé -> j'ajoute dans la map
//si id trouvé -> update
//si pas mentionné erase -> probablement autre fonction

void Game::launch_getter(std::size_t id, NmpClient::SpriteInfo &sp) 
{
    // Vérifier si l'id existe dans la map
    auto it = _mapHandlerPacket.find(id);
    if (it != _mapHandlerPacket.end()) {
        std::cout << "lallalala" << std::endl;
        // Appeler la fonction associée
        it->second(sp); // Appel de la fonction avec l'objet sp
    } else {
        // Gérer le cas où l'id n'existe pas
        std::cerr << "Erreur : Aucun handler pour l'id " << id << std::endl;
    }
}

void Game::handler_packets()
{
    auto data = m_client.get_data();
    if (!data.has_value()) {
        return;
    }
    auto p = data.value();
    if (p.getOpCode() != NmpClient::EVENT::SPRITE) {
        std::cout << "END OF FRAME" << std::endl;
        return;
    }
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
        if (sprite != nullptr) {
            //std::cout << "\tupdate" << std::endl;
            sprite.get()->setPosition(vecPos);
            //std::cout << "test: " << sprite.get()->getPosition().x << std::endl; 
        } else {
            //std::cout << "\tcreate" << std::endl;
            auto sprite = std::make_shared<Sprite>("../../client/config/player.json");
            sprite.get()->setPosition(vecPos);
            _spriteMng.addSprite(sprite, sp.idClient);
            //std::cout << "test: " << sprite.get()->getPosition().x << std::endl; 
        }
    handler_packets();
}

void Game::get_ennemies(NmpClient::SpriteInfo &sp)
{
    std::cout << "handle ennemies: " << sp.idClient << std::endl;
    handler_packets();
}

void Game::get_shoots(NmpClient::SpriteInfo &sp)
{
    std::cout << "handle shoots: " << sp.idClient << std::endl;
    handler_packets();
}

void Game::run()
{
    //std::queue<NmpClient::Packet> queuePacket;

    while (m_window.isOpen()) {
        float deltaTime = m_clock.restart().asSeconds();
        ////std::cout << "BEGIN LOOP\n";
        handleEvents();
        //std::cout << "JE SORS DE RENDER" << std::endl;
        //std::cout << "JE SORS DE HANDLEEVENTS" << std::endl;
        
        handler_packets();
        
        update(deltaTime);
        render();
        //std::cout << "END LOOP" <<std::endl;
    }
}
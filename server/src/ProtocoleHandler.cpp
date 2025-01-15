#include "ProtocolHandler.hpp"
#include "Server.hpp"
#include "idPlayer.hpp"
#include "shoot_type.hpp"

namespace NmpServer
{
    void ProtocoleHandler::executeOpCode()
    {
        std::cout << "CALL PROTOCOLE" << std::endl;
        EVENT key = _pck.getOpCode();
        auto it = _mapFctOpCode.find(key);
        if (it != _mapFctOpCode.end()) {
            it->second();
        }
            std::cout << "OK PROTOCOLE" << std::endl;
        //createEnnemies(); //en fraire un thread 
        //shootEnnemies();  //en fraire un thread
        //sys.position_system(_ecs);
        //std::cout << "position system" << std::endl;
        //sys.collision_system(_ecs);
        //sys.kill_system(_ecs);
    }

    registry &ProtocoleHandler::getECS() {
        return _ecs;
    }

    ProtocoleHandler::ProtocoleHandler(Server &server) : 
        _refServer(server),
        _lastEnemyCreationTime(std::chrono::steady_clock::now()),
        _lastShootCreationTime(std::chrono::steady_clock::now())
    {
        std::cout << "protocole Handler create" << std::endl;
        this->initComponents();
    }

    void ProtocoleHandler::fillPacket(Packet &packet)
    {
        _pck = packet;
    }

    std::optional<asio::ip::udp::endpoint> ProtocoleHandler::foundEndpointByClient(Entity &player)
    {
        std::optional<asio::ip::udp::endpoint> optionEndpoint{std::nullopt};

        for (const auto &pair : _vecPlayer) {
            if (pair.first == player) {
                return optionEndpoint = pair.second;
            }
        }
        return optionEndpoint;
    }

    void ProtocoleHandler::updateMoveEcs(
        Entity &player, 
        component::controllable::Key &control, 
        sparse_array<component::position>::value_type &pos,
        component::attribute &att)
    {
        System sys;
        std::optional<asio::ip::udp::endpoint> foundEndpoint{this->foundEndpointByClient(player)}; 

        if (foundEndpoint.has_value()) {
            if (att._type == component::attribute::Player1) {
                _ecs.emplace_component<component::controllable>(player, control);
                std::cout << "le controle est = " << control << std::endl;
                sys.control_system_p1(_ecs);
            }
            if (att._type == component::attribute::Player2) {
                _ecs.emplace_component<component::controllable>(player, control);
                sys.control_system_p2(_ecs);
            }
            if (att._type == component::attribute::Player3) {
                _ecs.emplace_component<component::controllable>(player, control);
                sys.control_system_p3(_ecs);
            }
            if (att._type == component::attribute::Player4) {
                _ecs.emplace_component<component::controllable>(player, control);
                sys.control_system_p4(_ecs);
            }
            //Packet packetPos(EVENT::MOVE, pos.x, pos.y);
            //_refServer.get().send_data(packetPos, foundEndpoint.value());
        } else {
            std::cout << "no endpoint found for this client" << std::endl;
            std::cout << "pos x: " << pos.x << " pos y: " << pos.y << std::endl;
        }
    }

    void ProtocoleHandler::evalMove()
    {
        std::cout << "evalMove" << std::endl;
        std::cout << "id client: " << _pck.getId() << std::endl;
        std::size_t idClient{ _pck.getId()};
        sparse_array<component::position> &pos = _ecs.get_components<component::position>();
        Entity player = _ecs.get_entity(idClient);
        sparse_array<component::position>::value_type &position = pos[player.get_id()];
        std::optional<NmpServer::DIRECTION> direction = _pck.getArg();
        auto &attributes = _ecs.get_components<component::attribute>();
        auto &att = attributes[player.get_id()];

        if (direction == DIRECTION::DOWN) {
            std::cout << "DOWN" << std::endl;
            auto control = component::controllable::Down;
            updateMoveEcs(player, control, position, att);
        } else if (direction == DIRECTION::UP) {
            std::cout << "UP" << std::endl;
            auto control = component::controllable::Up;
            updateMoveEcs(player, control, position, att);
        } else if (direction == DIRECTION::LEFT) {
            std::cout << "LEFT" << std::endl;
            auto control = component::controllable::Left;
            updateMoveEcs(player, control, position, att);
        } else if (direction == DIRECTION::RIGHT) {
            std::cout << "RIGHT" << std::endl;
            auto control = component::controllable::Right;
            updateMoveEcs(player, control, position, att);
        } else if ((direction == DIRECTION::SHOOT)) {
            auto control = component::controllable::Shoot;
            updateMoveEcs(player, control, position, att);
        } else if ((direction == DIRECTION::Key1)) {
            auto control = component::controllable::Shoot1;
            updateMoveEcs(player, control, position, att);
        } else if ((direction == DIRECTION::Key2)) {
            auto control = component::controllable::Shoot2;
            updateMoveEcs(player, control, position, att);
        } else if ((direction == DIRECTION::Key3)) {
            auto control = component::controllable::Shoot3;
            updateMoveEcs(player, control, position, att);
        } else if ((direction == DIRECTION::Key4)) {
            auto control = component::controllable::Shoot4;
            updateMoveEcs(player, control, position, att);
        } else if ((direction == DIRECTION::Key5)) {
            auto control = component::controllable::Shoot5;
            updateMoveEcs(player, control, position, att);
        } else 
            std::cout << "x " << position.x << " y " << position.y << std::endl;
            //std::cout << "NO KEY" << std::endl;
    }

    void ProtocoleHandler::evalQuit()
    {
        std::cout << "evalQuit" << std::endl;
    }

    void ProtocoleHandler::evalJoin()
    {

        Entity player;
        this->initPlayer();
        auto lastPlayer = _vecPlayer.back().first;
        auto lastEndpoint = _vecPlayer.back().second;

        std::cout << "send new id: " << lastPlayer.get_id() << std::endl;
        Packet joinPacket(lastPlayer.get_id(), EVENT::JOIN);
        _refServer.get().send_data(joinPacket, lastEndpoint);
        //_refServer.get()._vecPlayer = _vecPlayer;
    }

    void ProtocoleHandler::initComponents()
    {
        _ecs.register_component<component::attribute>();
        _ecs.register_component<component::controllable>();
        _ecs.register_component<component::level>();
        _ecs.register_component<component::life>();
        _ecs.register_component<component::position>();
        _ecs.register_component<component::score>();
        _ecs.register_component<component::size>();
        _ecs.register_component<component::state>();
        _ecs.register_component<component::velocity>();
        _ecs.register_component<component::idPlayer>();
        _ecs.register_component<component::shoot_type>();

    }

    void ProtocoleHandler::initPlayer()
    {
        Entity player = _ecs.spawn_entity();
        auto lastEndpoint = _refServer.get().getLastEndpoint();

        for (size_t i = 0; i < 4; i++) {
            if (_vecPlayer.size() == 0)
                _ecs.add_component<component::attribute>(player, {component::attribute::Player1});
            if (_vecPlayer.size() == 1)
                _ecs.add_component<component::attribute>(player, {component::attribute::Player2});
            if (_vecPlayer.size() == 2)
                _ecs.add_component<component::attribute>(player, {component::attribute::Player3});
            if (_vecPlayer.size() == 3)
                _ecs.add_component<component::attribute>(player, {component::attribute::Player4});
        }
        _ecs.add_component<component::controllable>(player, {component::controllable::NoKey});
        _ecs.add_component<component::level>(player, {component::level::Level0});
        _ecs.add_component<component::life>(player, {3});
        _ecs.add_component<component::position>(player, {50, 500});
        _ecs.add_component<component::score>(player, {0});
        _ecs.add_component<component::size>(player, {100, 50});
        _ecs.add_component<component::state>(player, {component::state::Alive});
        _ecs.add_component<component::velocity>(player, {5, 5});
        _ecs.add_component<component::idPlayer>(player, {player.get_id()});
        _ecs.add_component<component::shoot_type>(player, {component::attribute::Shoot});
        //_refServer.get()._vecPlayer.push_back(std::make_pair(player, lastEndpoint));
        _vecPlayer.push_back(std::make_pair(player, lastEndpoint));  
    }

    void ProtocoleHandler::initEnnemies(int posX, int posY, int type)
    {

        Entity ennemies = _ecs.spawn_entity();

        if (type == 1) {
            _ecs.add_component<component::attribute>(ennemies, {component::attribute::Ennemies});
            _ecs.add_component<component::velocity>(ennemies, {-2, 0});
            _ecs.add_component<component::size>(ennemies, {50, 50});
            _ecs.add_component<component::life>(ennemies, {1});
        }
        if (type == 2) {
            _ecs.add_component<component::attribute>(ennemies, {component::attribute::Ennemies2});
            _ecs.add_component<component::velocity>(ennemies, {0, -2});
            _ecs.add_component<component::size>(ennemies, {50, 50});
            _ecs.add_component<component::life>(ennemies, {1});
        }
        if (type == 3) {
            _ecs.add_component<component::attribute>(ennemies, {component::attribute::Ennemies3});
            _ecs.add_component<component::velocity>(ennemies, {-2, -2});
            _ecs.add_component<component::size>(ennemies, {50, 50});
            _ecs.add_component<component::life>(ennemies, {1});
        }
        if (type == 4) {
            _ecs.add_component<component::attribute>(ennemies, {component::attribute::Ennemies4});
            _ecs.add_component<component::size>(ennemies, {50, 50});
            _ecs.add_component<component::velocity>(ennemies, {-2, -2});
            _ecs.add_component<component::life>(ennemies, {1});

        }
        if (type == 5) {
            _ecs.add_component<component::attribute>(ennemies, {component::attribute::Ennemies5});
            _ecs.add_component<component::size>(ennemies, {900, 800});
            _ecs.add_component<component::velocity>(ennemies, {0, 0});
            _ecs.add_component<component::life>(ennemies, {10});
        }

        _ecs.add_component<component::level>(ennemies, {component::level::Level0});
        _ecs.add_component<component::controllable>(ennemies, {component::controllable::Key::NoKey});
        _ecs.add_component<component::position>(ennemies, {posX, posY});
        _ecs.add_component<component::state>(ennemies, {component::state::Alive});
        _ecs.add_component<component::idPlayer>(ennemies, {ennemies.get_id()});
    }

    void ProtocoleHandler::loadEnnemiesFromconfig(const std::vector<infoEnnemies_t> vecEnnemies)
    {
        for (auto elem : vecEnnemies)
            initEnnemies(elem.posX, elem.posY, elem.type);
    }

    void ProtocoleHandler::joinNewLevel(asio::ip::udp::endpoint ip)
    {
        Entity player;
        this->initPlayer();
        auto lastPlayer = _vecPlayer.back().first;

        std::cout << "send new id: " << lastPlayer.get_id() << std::endl;
        Packet joinPacket(lastPlayer.get_id(), EVENT::JOIN);
        _refServer.get().send_data(joinPacket, ip);
    }

    void ProtocoleHandler::clearPlayer()
    {
        _vecPlayer.clear();
        for (auto elem : _refServer.get()._vecPlayer) {
            std::cout << "send new id" << std::endl;
            joinNewLevel(elem);
        }

    }
}
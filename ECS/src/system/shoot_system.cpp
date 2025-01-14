#include "system.hpp"
#include "position.hpp"
#include "controllable.hpp"
#include "attribute.hpp"
#include "velocity.hpp"
#include "idPlayer.hpp"
#include "state.hpp"
#include "size.hpp"
#include <chrono>
#include <iostream>

void create_shoot(Entity entity, registry &reg)
{
    Entity shoot = reg.spawn_entity();

    auto &positions = reg.get_components<component::position>();
    auto &pos = positions[entity.get_id()];
    reg.add_component<component::attribute>(shoot, {component::attribute::Shoot});
    reg.add_component<component::position>(shoot, {pos.x, pos.y - 50});
    reg.add_component<component::controllable>(shoot, {component::controllable::NoKey});
    reg.add_component<component::velocity>(shoot, {15, 15});
    reg.add_component<component::size>(shoot, {50, 50});
    reg.add_component<component::idPlayer>(shoot, {entity.get_id()});
    reg.add_component<component::state>(shoot, {component::state::stateKey::Alive});
    reg.emplace_component<component::controllable>(entity, component::controllable::NoKey);
}

void create_shoot3(Entity entity, registry &reg)
{
    Entity shoot = reg.spawn_entity();

    auto &positions = reg.get_components<component::position>();
    auto &pos = positions[entity.get_id()];
    reg.add_component<component::attribute>(shoot, {component::attribute::Shoot3});
    reg.add_component<component::position>(shoot, {pos.x, pos.y - 50});
    reg.add_component<component::controllable>(shoot, {component::controllable::NoKey});
    reg.add_component<component::velocity>(shoot, {20, -20});
    reg.add_component<component::size>(shoot, {50, 50});
    reg.add_component<component::idPlayer>(shoot, {entity.get_id()});
    reg.add_component<component::state>(shoot, {component::state::stateKey::Alive});
    reg.emplace_component<component::controllable>(entity, component::controllable::NoKey);
}

void create_shoot4(Entity entity, registry &reg)
{
    Entity shoot = reg.spawn_entity();

    auto &positions = reg.get_components<component::position>();
    auto &pos = positions[entity.get_id()];
    reg.add_component<component::attribute>(shoot, {component::attribute::Shoot4});
    reg.add_component<component::position>(shoot, {pos.x, pos.y - 50});
    reg.add_component<component::controllable>(shoot, {component::controllable::NoKey});
    reg.add_component<component::velocity>(shoot, {30, 30});
    reg.add_component<component::size>(shoot, {50, 50});
    reg.add_component<component::idPlayer>(shoot, {entity.get_id()});
    reg.add_component<component::state>(shoot, {component::state::stateKey::Alive});
    reg.emplace_component<component::controllable>(entity, component::controllable::NoKey);
}

void create_shoot5(Entity entity, registry &reg)
{
    Entity shoot = reg.spawn_entity();

    auto &positions = reg.get_components<component::position>();
    auto &pos = positions[entity.get_id()];
    reg.add_component<component::attribute>(shoot, {component::attribute::Shoot5});
    reg.add_component<component::position>(shoot, {pos.x, pos.y - 50});
    reg.add_component<component::controllable>(shoot, {component::controllable::NoKey});
    reg.add_component<component::velocity>(shoot, {30, 30});
    reg.add_component<component::size>(shoot, {50, 50});
    reg.add_component<component::idPlayer>(shoot, {entity.get_id()});
    reg.add_component<component::state>(shoot, {component::state::stateKey::Alive});
    reg.emplace_component<component::controllable>(entity, component::controllable::NoKey);
}

void create_shoot6(Entity entity, registry &reg)
{
    Entity shoot = reg.spawn_entity();

    auto &positions = reg.get_components<component::position>();
    auto &pos = positions[entity.get_id()];
    reg.add_component<component::attribute>(shoot, {component::attribute::Shoot6});
    reg.add_component<component::position>(shoot, {pos.x, pos.y - 50});
    reg.add_component<component::controllable>(shoot, {component::controllable::NoKey});
    reg.add_component<component::velocity>(shoot, {40, -40});
    reg.add_component<component::size>(shoot, {50, 50});
    reg.add_component<component::idPlayer>(shoot, {entity.get_id()});
    reg.add_component<component::state>(shoot, {component::state::stateKey::Alive});
    reg.emplace_component<component::controllable>(entity, component::controllable::NoKey);
}

void create_shoot_ennemie(Entity entity, registry &reg)
{
    Entity shoot = reg.spawn_entity();

    auto &positions = reg.get_components<component::position>();
    auto &pos = positions[entity.get_id()];
    std::cout << "shoot id Ennemis: " << shoot.get_id() << std::endl;

    reg.add_component<component::attribute>(shoot, {component::attribute::Shoot1});
    reg.add_component<component::position>(shoot, {pos.x, pos.y - 50});
    reg.add_component<component::velocity>(shoot, {-20, 0});
    reg.add_component<component::size>(shoot, {50, 50});
    reg.add_component<component::idPlayer>(shoot, {entity.get_id()});
    reg.add_component<component::state>(shoot, {component::state::stateKey::Alive});
}

void create_shoot_ennemie2(Entity entity, registry &reg)
{
    Entity shoot = reg.spawn_entity();

    auto &positions = reg.get_components<component::position>();
    auto &pos = positions[entity.get_id()];
    std::cout << "shoot id Ennemis: " << shoot.get_id() << std::endl;

    reg.add_component<component::attribute>(shoot, {component::attribute::Shoot2});
    reg.add_component<component::position>(shoot, {pos.x, pos.y});
    reg.add_component<component::velocity>(shoot, {-25, 0});
    reg.add_component<component::size>(shoot, {50, 50});
    reg.add_component<component::idPlayer>(shoot, {entity.get_id()});
    reg.add_component<component::state>(shoot, {component::state::stateKey::Alive});
}

void create_shoot_ennemie3(Entity entity, registry &reg)
{
    Entity shoot = reg.spawn_entity();

    auto &positions = reg.get_components<component::position>();
    auto &pos = positions[entity.get_id()];
    std::cout << "shoot id Ennemis: " << shoot.get_id() << std::endl;

    reg.add_component<component::attribute>(shoot, {component::attribute::Shoot7});
    reg.add_component<component::position>(shoot, {pos.x, pos.y});
    reg.add_component<component::velocity>(shoot, {-30, -25});
    reg.add_component<component::size>(shoot, {50, 50});
    reg.add_component<component::idPlayer>(shoot, {entity.get_id()});
    reg.add_component<component::state>(shoot, {component::state::stateKey::Alive});
}

void create_shoot_ennemie4(Entity entity, registry &reg)
{
    Entity shoot = reg.spawn_entity();

    auto &positions = reg.get_components<component::position>();
    auto &pos = positions[entity.get_id()];
    std::cout << "shoot id Ennemis: " << shoot.get_id() << std::endl;

    reg.add_component<component::attribute>(shoot, {component::attribute::Shoot8});
    reg.add_component<component::position>(shoot, {pos.x, pos.y});
    reg.add_component<component::velocity>(shoot, {-30, -25});
    reg.add_component<component::size>(shoot, {50, 50});
    reg.add_component<component::idPlayer>(shoot, {entity.get_id()});
    reg.add_component<component::state>(shoot, {component::state::stateKey::Alive});
}

void create_shoot_ennemie5(Entity entity, registry &reg)
{
    Entity shoot = reg.spawn_entity();

    auto &positions = reg.get_components<component::position>();
    auto &pos = positions[entity.get_id()];

    reg.add_component<component::attribute>(shoot, {component::attribute::Shoot9});
    reg.add_component<component::position>(shoot, {pos.x, pos.y});
    reg.add_component<component::velocity>(shoot, {-40, -30});
    reg.add_component<component::size>(shoot, {50, 50});
    reg.add_component<component::idPlayer>(shoot, {entity.get_id()});
    reg.add_component<component::state>(shoot, {component::state::stateKey::Alive});
}

void create_shoot_ennemie6(Entity entity, registry &reg)
{
    Entity shoot = reg.spawn_entity();

    auto &positions = reg.get_components<component::position>();
    auto &pos = positions[entity.get_id()];

    reg.add_component<component::attribute>(shoot, {component::attribute::Shoot10});
    reg.add_component<component::position>(shoot, {pos.x, pos.y});
    reg.add_component<component::velocity>(shoot, {-40, -30});
    reg.add_component<component::size>(shoot, {50, 50});
    reg.add_component<component::idPlayer>(shoot, {entity.get_id()});
    reg.add_component<component::state>(shoot, {component::state::stateKey::Alive});
}

void System::shoot_system_player_1(registry &reg, size_t i)
{
    Entity player = reg.get_entity(i);
    create_shoot(player, reg);
}

void System::shoot_system_player_2(registry &reg, size_t i)
{
    Entity player = reg.get_entity(i);
    create_shoot3(player, reg);
}

void System::shoot_system_player_3(registry &reg, size_t i)
{
    Entity player = reg.get_entity(i);
    create_shoot4(player, reg);
}

void System::shoot_system_player_4(registry &reg, size_t i)
{
    Entity player = reg.get_entity(i);
    create_shoot5(player, reg);
}

void System::shoot_system_player_5(registry &reg, size_t i)
{
    Entity player = reg.get_entity(i);
    create_shoot6(player, reg);
}

void System::shoot_system_ennemies(registry &reg)
{
    auto &attribute = reg.get_components<component::attribute>();
    auto &state = reg.get_components<component::state>();

    using namespace std::chrono;
    static auto lastSpawnTime1 = steady_clock::now();
    static auto lastSpawnTime2 = steady_clock::now();
    static auto lastSpawnTime3 = steady_clock::now();
    static auto lastSpawnTime4 = steady_clock::now();
    static auto lastSpawnTime5 = steady_clock::now();
    static auto lastSpawnTime6 = steady_clock::now();
    static auto lastSpawnTime7 = steady_clock::now();
    auto currentTime = steady_clock::now();

    if (duration_cast<seconds>(currentTime - lastSpawnTime1).count() >= 2) {
        for (size_t i = 0; i < attribute.size(); i++) {
            auto &att = attribute[i];
            auto &st = state[i];
            if (att._type == component::attribute::Ennemies && st._stateKey == component::state::stateKey::Alive) {
                Entity ennemies = reg.get_entity(i);
                create_shoot_ennemie(ennemies, reg);
            }
        lastSpawnTime1 = currentTime;

        }
    }
    if (duration_cast<seconds>(currentTime - lastSpawnTime2).count() >= 4) {
        for (size_t i = 0; i < attribute.size(); i++) {
            auto &att = attribute[i];
            auto &st = state[i];
            if (att._type == component::attribute::Ennemies2 && st._stateKey == component::state::stateKey::Alive) {
                Entity ennemies = reg.get_entity(i);
                create_shoot_ennemie2(ennemies, reg);
                std::cout  << "je creer shoot for ennemi 2" << std::endl;
            }
        }
        lastSpawnTime2 = currentTime;
    }
    if (duration_cast<seconds>(currentTime - lastSpawnTime3).count() >= 8) {
        for (size_t i = 0; i < attribute.size(); i++) {
            auto &att = attribute[i];
            auto &st = state[i];
            if (att._type == component::attribute::Ennemies3 && st._stateKey == component::state::stateKey::Alive) {
                Entity ennemies = reg.get_entity(i);
                create_shoot_ennemie3(ennemies, reg);
            }
        }
        lastSpawnTime3 = currentTime;
    }
    if (duration_cast<seconds>(currentTime - lastSpawnTime6).count() >= 8) {
        for (size_t i = 0; i < attribute.size(); i++) {
            auto &att = attribute[i];
            auto &st = state[i];
            if (att._type == component::attribute::Ennemies4 && st._stateKey == component::state::stateKey::Alive) {
                Entity ennemies = reg.get_entity(i);
                create_shoot_ennemie4(ennemies, reg);
            }
        }
        lastSpawnTime6 = currentTime;
    }
    if (duration_cast<seconds>(currentTime - lastSpawnTime4).count() >= 12) {
        for (size_t i = 0; i < attribute.size(); i++) {
            auto &att = attribute[i];
            auto &st = state[i];
            if (att._type == component::attribute::Ennemies5 && st._stateKey == component::state::stateKey::Alive) {
                Entity ennemies = reg.get_entity(i);
                create_shoot_ennemie5(ennemies, reg);
            }
        }
        lastSpawnTime4 = currentTime;
    }
    if (duration_cast<seconds>(currentTime - lastSpawnTime7).count() >= 15) {
        spawn_power_up(reg);
        lastSpawnTime7 = currentTime;
    }
    if (duration_cast<seconds>(currentTime - lastSpawnTime5).count() >= 15) {
        for (size_t i = 0; i < attribute.size(); i++) {
            auto &att = attribute[i];
            auto &st = state[i];
            if (att._type == component::attribute::Ennemies5 && st._stateKey == component::state::stateKey::Alive) {
                Entity ennemies = reg.get_entity(i);
                create_shoot_ennemie5(ennemies, reg);
            }
        }
        lastSpawnTime5 = currentTime;
    }
}
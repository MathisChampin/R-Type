#include "system.hpp"
#include "position.hpp"
#include "controllable.hpp"
#include "attribute.hpp"
#include "velocity.hpp"
#include "idPlayer.hpp"
#include "state.hpp"
#include "size.hpp"

void create_shoot(Entity entity, registry &reg)
{
    Entity shoot = reg.spawn_entity();

    auto &positions = reg.get_components<component::position>();
    auto &pos = positions[entity.get_id()];

    std::cout << "shoot id Player: " << shoot.get_id() << std::endl;
    reg.add_component<component::attribute>(shoot, {component::attribute::Shoot});
    reg.add_component<component::position>(shoot, {pos.x, pos.y});
    reg.add_component<component::controllable>(shoot, {component::controllable::NoKey});
    reg.add_component<component::velocity>(shoot, {15, 0});
    reg.add_component<component::size>(shoot, {150, 150});
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

    reg.add_component<component::attribute>(shoot, {component::attribute::Shoot});
    reg.add_component<component::position>(shoot, {pos.x, pos.y});
    reg.add_component<component::velocity>(shoot, {-20, 0});
    reg.add_component<component::size>(shoot, {150, 150});
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
    reg.add_component<component::size>(shoot, {150, 150});
    reg.add_component<component::idPlayer>(shoot, {entity.get_id()});
    reg.add_component<component::state>(shoot, {component::state::stateKey::Alive});
}

void create_shoot_ennemie34(Entity entity, registry &reg)
{
    Entity shoot = reg.spawn_entity();

    auto &positions = reg.get_components<component::position>();
    auto &pos = positions[entity.get_id()];
    std::cout << "shoot id Ennemis: " << shoot.get_id() << std::endl;

    reg.add_component<component::attribute>(shoot, {component::attribute::Shoot3});
    reg.add_component<component::position>(shoot, {pos.x, pos.y});
    reg.add_component<component::velocity>(shoot, {-30, -25});
    reg.add_component<component::size>(shoot, {150, 150});
    reg.add_component<component::idPlayer>(shoot, {entity.get_id()});
    reg.add_component<component::state>(shoot, {component::state::stateKey::Alive});
}

void create_shoot_ennemie5(Entity entity, registry &reg)
{
    Entity shoot = reg.spawn_entity();

    auto &positions = reg.get_components<component::position>();
    auto &pos = positions[entity.get_id()];
    std::cout << "shoot id Ennemis: " << shoot.get_id() << std::endl;

    reg.add_component<component::attribute>(shoot, {component::attribute::Shoot5});
    reg.add_component<component::position>(shoot, {pos.x, pos.y});
    reg.add_component<component::velocity>(shoot, {-40, -30});
    reg.add_component<component::size>(shoot, {150, 150});
    reg.add_component<component::idPlayer>(shoot, {entity.get_id()});
    reg.add_component<component::state>(shoot, {component::state::stateKey::Alive});
}

void System::shoot_system_player(registry &reg)
{
    auto &controllable = reg.get_components<component::controllable>();
    auto &state = reg.get_components<component::state>();

    for (size_t i = 0; i < controllable.size(); i++) {
        auto &ctrl = controllable[i];
        auto &st = state[i];

        if (ctrl.active_key == component::controllable::Shoot && st._stateKey == component::state::stateKey::Alive) {
            Entity player = reg.get_entity(i);
            create_shoot(player, reg);
        }
    }
}

void System::shoot_system_ennemies(registry &reg)
{
    auto &attribute = reg.get_components<component::attribute>();
    auto &state = reg.get_components<component::state>();

    for (size_t i = 0; i < attribute.size(); i++) {
        auto &att = attribute[i];
        auto &st = state[i];
        if (att._type == component::attribute::Ennemies && st._stateKey == component::state::stateKey::Alive) {
            Entity ennemies = reg.get_entity(i);
            create_shoot_ennemie(ennemies, reg);
        }
        if (att._type == component::attribute::Ennemies2 && st._stateKey == component::state::stateKey::Alive) {
            Entity ennemies = reg.get_entity(i);
            create_shoot_ennemie2(ennemies, reg);
            std::cout  << "je creer shoot for ennemi 2" << std::endl;
        }
        if ((att._type == component::attribute::Ennemies3 || att._type == component::attribute::Ennemies4) && st._stateKey == component::state::stateKey::Alive) {
            Entity ennemies = reg.get_entity(i);
            create_shoot_ennemie34(ennemies, reg);
        }
        if (att._type == component::attribute::Ennemies5 && st._stateKey == component::state::stateKey::Alive) {
            Entity ennemies = reg.get_entity(i);
            create_shoot_ennemie5(ennemies, reg);
        }
    }
}
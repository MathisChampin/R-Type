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

    reg.add_component<component::attribute>(shoot, {component::attribute::Shoot});
    reg.add_component<component::position>(shoot, {pos.x, pos.y});
    reg.add_component<component::velocity>(shoot, {10, 0});
    reg.add_component<component::size>(shoot, {int(0.1), int(0.1)});
    reg.add_component<component::idPlayer>(shoot, {entity.get_id()});
    reg.add_component<component::state>(shoot, {component::state::stateKey::Alive});
}

void create_shoot_ennemie(Entity entity, registry &reg)
{
    Entity shoot = reg.spawn_entity();

    auto &positions = reg.get_components<component::position>();
    auto &pos = positions[entity.get_id()];

    reg.add_component<component::attribute>(shoot, {component::attribute::Shoot});
    reg.add_component<component::position>(shoot, {pos.x, pos.y});
    reg.add_component<component::velocity>(shoot, {-10, 0});
    reg.add_component<component::size>(shoot, {int(0.1), int(0.1)});
    reg.add_component<component::idPlayer>(shoot, {entity.get_id()});
    reg.add_component<component::state>(shoot, {component::state::stateKey::Alive});
}

void System::shoot_system_player(registry &reg)
{
    auto &controllable = reg.get_components<component::controllable>();

    for (size_t i = 0; i < controllable.size(); i++) {
        auto &ctrl = controllable[i];
        if (ctrl.active_key == component::controllable::Shoot) {
            Entity player = reg.get_entity(i);
            create_shoot(player, reg);
        }
    }
}

void System::shoot_system_ennemies(registry &reg)
{
    auto &attribute = reg.get_components<component::attribute>();

    for (size_t i = 0; i < attribute.size(); i++) {
        auto &att = attribute[i];
        if (att._type == component::attribute::Ennemies) {
            Entity ennemies = reg.get_entity(i);
            create_shoot_ennemie(ennemies, reg);
        }
    }
}
#include "system.hpp"
#include "position.hpp"
#include "controllable.hpp"
#include "attribute.hpp"
#include "velocity.hpp"
#include "idPlayer.hpp"
#include "size.hpp"
#include <iostream>


void create_shoot(Entity player, registry &reg)
{
    Entity shoot = reg.spawn_entity();

    auto &positions = reg.get_components<component::position>();
    auto &pos = positions[player.get_id()];
    std::cout << pos.x << " & " << pos.y << std::endl;
    reg.add_component<component::attribute>(shoot, {component::attribute::Shoot});
    reg.add_component<component::position>(shoot, {pos.x, pos.y});
    reg.add_component<component::velocity>(shoot, {10, 0});
    reg.add_component<component::size>(shoot, {10, 10});
    reg.add_component<component::idPlayer>(shoot, {player.get_id()});
}

void System::shoot_system(registry &reg)
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


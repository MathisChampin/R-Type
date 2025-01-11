#include <criterion/criterion.h>
#include "position.hpp"
#include "size.hpp"
#include "system.hpp"
#include "attribute.hpp"
#include "state.hpp"
#include "Registry.hpp"

Test(system, collision_system_player_powerup_detects_collision) {
    registry reg;
    System sys;

    Entity player = reg.spawn_entity();
    reg.add_component<component::position>(player, {10, 10});
    reg.add_component<component::size>(player, {10, 10});
    reg.add_component<component::attribute>(player, {component::attribute::Player1});
    reg.add_component<component::state>(player, {component::state::stateKey::Alive});

    Entity powerUp = reg.spawn_entity();
    reg.add_component<component::position>(powerUp, {15, 15});
    reg.add_component<component::size>(powerUp, {5, 5});
    reg.add_component<component::attribute>(powerUp, {component::attribute::PowerUpMove});
    reg.add_component<component::state>(powerUp, {component::state::stateKey::Alive});

    bool result = sys.collision_power_up_move(reg);
    cr_assert(result, "Expected collision_system_player_powerup to return true for collision");
}

Test(system, collision_system_player_powerup_no_collision) {
    registry reg;
    System sys;

    Entity player = reg.spawn_entity();
    reg.add_component<component::position>(player, {0, 0});
    reg.add_component<component::size>(player, {10, 10});
    reg.add_component<component::attribute>(player, {component::attribute::Player1});
    reg.add_component<component::state>(player, {component::state::stateKey::Alive});

    Entity powerUp = reg.spawn_entity();
    reg.add_component<component::position>(powerUp, {20, 20});
    reg.add_component<component::size>(powerUp, {5, 5});
    reg.add_component<component::attribute>(powerUp, {component::attribute::PowerUpMove});
    reg.add_component<component::state>(powerUp, {component::state::stateKey::Alive});

    bool result = sys.collision_power_up_move(reg);
    cr_assert_not(result, "Expected collision_system_player_powerup to return false for no collision");
}


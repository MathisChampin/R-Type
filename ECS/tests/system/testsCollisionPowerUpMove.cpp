#include <criterion/criterion.h>
#include "position.hpp"
#include "size.hpp"
#include "system.hpp"
#include "attribute.hpp"
#include "state.hpp"
#include "Registry.hpp"
#include "velocity.hpp"

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

Test(system, velocity_player1) {
    registry reg;
    System sys;

    auto &velo = reg.register_component<component::velocity>();

    Entity player = reg.spawn_entity();
    reg.add_component<component::velocity>(player, {10, 10});
    reg.add_component<component::attribute>(player, {component::attribute::Player1});
    reg.add_component<component::state>(player, {component::state::stateKey::Alive});

    sys.power_up_velocity_p1(reg);
    auto &vel = velo[player.get_id()];

    cr_assert_eq(vel.x, 15, "Expected velocity x to be 15, but got %d", vel.x);
    cr_assert_eq(vel.y, 15, "Expected velocity y to be 15, but got %d", vel.y);
}

Test(system, velocity_player2) {
    registry reg;
    System sys;

    auto &velo = reg.register_component<component::velocity>();

    Entity player = reg.spawn_entity();
    reg.add_component<component::velocity>(player, {10, 10});
    reg.add_component<component::attribute>(player, {component::attribute::Player2});
    reg.add_component<component::state>(player, {component::state::stateKey::Alive});

    sys.power_up_velocity_p2(reg);
    auto &vel = velo[player.get_id()];

    cr_assert_eq(vel.x, 15, "Expected velocity x to be 15, but got %d", vel.x);
    cr_assert_eq(vel.y, 15, "Expected velocity y to be 15, but got %d", vel.y);
}

Test(system, velocity_player3) {
    registry reg;
    System sys;

    auto &velo = reg.register_component<component::velocity>();

    Entity player = reg.spawn_entity();
    reg.add_component<component::velocity>(player, {10, 10});
    reg.add_component<component::attribute>(player, {component::attribute::Player3});
    reg.add_component<component::state>(player, {component::state::stateKey::Alive});

    sys.power_up_velocity_p3(reg);
    auto &vel = velo[player.get_id()];

    cr_assert_eq(vel.x, 15, "Expected velocity x to be 15, but got %d", vel.x);
    cr_assert_eq(vel.y, 15, "Expected velocity y to be 15, but got %d", vel.y);
}

Test(system, velocity_player4) {
    registry reg;
    System sys;

    auto &velo = reg.register_component<component::velocity>();

    Entity player = reg.spawn_entity();
    reg.add_component<component::velocity>(player, {10, 10});
    reg.add_component<component::attribute>(player, {component::attribute::Player4});
    reg.add_component<component::state>(player, {component::state::stateKey::Alive});

    sys.power_up_velocity_p4(reg);
    auto &vel = velo[player.get_id()];

    cr_assert_eq(vel.x, 15, "Expected velocity x to be 15, but got %d", vel.x);
    cr_assert_eq(vel.y, 15, "Expected velocity y to be 15, but got %d", vel.y);
}

Test(system, reset_velocity_player1) {
    registry reg;
    System sys;

    auto &velo = reg.register_component<component::velocity>();

    Entity player = reg.spawn_entity();
    reg.add_component<component::velocity>(player, {10, 10});
    reg.add_component<component::attribute>(player, {component::attribute::Player1});
    reg.add_component<component::state>(player, {component::state::stateKey::Alive});

    sys.reset_velocity_p1(reg);
    auto &vel = velo[player.get_id()];

    cr_assert_eq(vel.x, 5, "Expected velocity x to be 5, but got %d", vel.x);
    cr_assert_eq(vel.y, 5, "Expected velocity y to be 5, but got %d", vel.y);
}

Test(system, reset_velocity_player2) {
    registry reg;
    System sys;

    auto &velo = reg.register_component<component::velocity>();

    Entity player = reg.spawn_entity();
    reg.add_component<component::velocity>(player, {10, 10});
    reg.add_component<component::attribute>(player, {component::attribute::Player2});
    reg.add_component<component::state>(player, {component::state::stateKey::Alive});

    sys.reset_velocity_p2(reg);
    auto &vel = velo[player.get_id()];

    cr_assert_eq(vel.x, 5, "Expected velocity x to be 5, but got %d", vel.x);
    cr_assert_eq(vel.y, 5, "Expected velocity y to be 5, but got %d", vel.y);
}

Test(system, reset_velocity_player3) {
    registry reg;
    System sys;

    auto &velo = reg.register_component<component::velocity>();

    Entity player = reg.spawn_entity();
    reg.add_component<component::velocity>(player, {10, 10});
    reg.add_component<component::attribute>(player, {component::attribute::Player3});
    reg.add_component<component::state>(player, {component::state::stateKey::Alive});

    sys.reset_velocity_p3(reg);
    auto &vel = velo[player.get_id()];

    cr_assert_eq(vel.x, 5, "Expected velocity x to be 5, but got %d", vel.x);
    cr_assert_eq(vel.y, 5, "Expected velocity y to be 5, but got %d", vel.y);
}

Test(system, reset_velocity_player4) {
    registry reg;
    System sys;

    auto &velo = reg.register_component<component::velocity>();

    Entity player = reg.spawn_entity();
    reg.add_component<component::velocity>(player, {10, 10});
    reg.add_component<component::attribute>(player, {component::attribute::Player4});
    reg.add_component<component::state>(player, {component::state::stateKey::Alive});

    sys.reset_velocity_p4(reg);
    auto &vel = velo[player.get_id()];

    cr_assert_eq(vel.x, 5, "Expected velocity x to be 5, but got %d", vel.x);
    cr_assert_eq(vel.y, 5, "Expected velocity y to be 5, but got %d", vel.y);
}
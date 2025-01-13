#include <criterion/criterion.h>
#include "position.hpp"
#include "size.hpp"
#include "system.hpp"
#include "attribute.hpp"
#include "state.hpp"
#include "Registry.hpp"
#include "velocity.hpp"
#include "idPlayer.hpp"

Test(system, collision_system_player_powerup_shoot_collision) {
    registry reg;
    System sys;

    Entity player = reg.spawn_entity();
    reg.add_component<component::position>(player, {10, 10});
    reg.add_component<component::size>(player, {10, 10});
    reg.add_component<component::attribute>(player, {component::attribute::Player1});
    reg.add_component<component::state>(player, {component::state::stateKey::Alive});

    Entity powerShoot = reg.spawn_entity();
    reg.add_component<component::position>(powerShoot, {15, 15});
    reg.add_component<component::size>(powerShoot, {5, 5});
    reg.add_component<component::attribute>(powerShoot, {component::attribute::PowerUpShoot});
    reg.add_component<component::state>(powerShoot, {component::state::stateKey::Alive});

    bool result = sys.collision_power_up_shoot(reg);
    cr_assert(result, "Expected collision_system_player_powerup to return true for collision");
}

Test(system, collision_system_player_powerup_shoot_no_collision) {
    registry reg;
    System sys;

    Entity player = reg.spawn_entity();
    reg.add_component<component::position>(player, {0, 0});
    reg.add_component<component::size>(player, {10, 10});
    reg.add_component<component::attribute>(player, {component::attribute::Player1});
    reg.add_component<component::state>(player, {component::state::stateKey::Alive});

    Entity powerUpShoot = reg.spawn_entity();
    reg.add_component<component::position>(powerUpShoot, {20, 20});
    reg.add_component<component::size>(powerUpShoot, {5, 5});
    reg.add_component<component::attribute>(powerUpShoot, {component::attribute::PowerUpShoot});
    reg.add_component<component::state>(powerUpShoot, {component::state::stateKey::Alive});

    bool result = sys.collision_power_up_shoot(reg);
    cr_assert_not(result, "Expected collision_system_player_powerup to return false for no collision");
}

Test(system, shoot_player1) {
    registry reg;
    System sys;

    auto &velo = reg.register_component<component::velocity>();

    Entity player = reg.spawn_entity();
    reg.add_component<component::velocity>(player, {10, 10});
    reg.add_component<component::attribute>(player, {component::attribute::Player1});
    reg.add_component<component::state>(player, {component::state::stateKey::Alive});

    Entity Shoot = reg.spawn_entity();
    reg.add_component<component::velocity>(Shoot, {10, 10});
    reg.add_component<component::attribute>(Shoot, {component::attribute::Shoot});
    reg.add_component<component::state>(Shoot, {component::state::stateKey::Alive});
    reg.add_component<component::idPlayer>(Shoot, {player.get_id()});

    sys.update_shoot_velocity_p1(reg);
    auto &vel = velo[Shoot.get_id()];

    cr_assert_eq(vel.x, 15, "Expected velocity x to be 15, but got %d", vel.x);
    cr_assert_eq(vel.y, 15, "Expected velocity y to be 15, but got %d", vel.y);
}

Test(system, shoot_player2) {
    registry reg;
    System sys;

    auto &velo = reg.register_component<component::velocity>();

    Entity player = reg.spawn_entity();
    reg.add_component<component::velocity>(player, {10, 10});
    reg.add_component<component::attribute>(player, {component::attribute::Player2});
    reg.add_component<component::state>(player, {component::state::stateKey::Alive});

    Entity Shoot = reg.spawn_entity();
    reg.add_component<component::velocity>(Shoot, {10, 10});
    reg.add_component<component::attribute>(Shoot, {component::attribute::Shoot});
    reg.add_component<component::state>(Shoot, {component::state::stateKey::Alive});
    reg.add_component<component::idPlayer>(Shoot, {player.get_id()});

    sys.update_shoot_velocity_p2(reg);
    auto &vel = velo[Shoot.get_id()];

    cr_assert_eq(vel.x, 15, "Expected velocity x to be 15, but got %d", vel.x);
    cr_assert_eq(vel.y, 15, "Expected velocity y to be 15, but got %d", vel.y);
}

Test(system, shoot_player3) {
    registry reg;
    System sys;

    auto &velo = reg.register_component<component::velocity>();

    Entity player = reg.spawn_entity();
    reg.add_component<component::velocity>(player, {10, 10});
    reg.add_component<component::attribute>(player, {component::attribute::Player3});
    reg.add_component<component::state>(player, {component::state::stateKey::Alive});

    Entity Shoot = reg.spawn_entity();
    reg.add_component<component::velocity>(Shoot, {10, 10});
    reg.add_component<component::attribute>(Shoot, {component::attribute::Shoot});
    reg.add_component<component::state>(Shoot, {component::state::stateKey::Alive});
    reg.add_component<component::idPlayer>(Shoot, {player.get_id()});

    sys.update_shoot_velocity_p3(reg);
    auto &vel = velo[Shoot.get_id()];

    cr_assert_eq(vel.x, 15, "Expected velocity x to be 15, but got %d", vel.x);
    cr_assert_eq(vel.y, 15, "Expected velocity y to be 15, but got %d", vel.y);
}

Test(system, shoot_player4) {
    registry reg;
    System sys;

    auto &velo = reg.register_component<component::velocity>();

    Entity player = reg.spawn_entity();
    reg.add_component<component::velocity>(player, {10, 10});
    reg.add_component<component::attribute>(player, {component::attribute::Player4});
    reg.add_component<component::state>(player, {component::state::stateKey::Alive});

    Entity Shoot = reg.spawn_entity();
    reg.add_component<component::velocity>(Shoot, {10, 10});
    reg.add_component<component::attribute>(Shoot, {component::attribute::Shoot});
    reg.add_component<component::state>(Shoot, {component::state::stateKey::Alive});
    reg.add_component<component::idPlayer>(Shoot, {player.get_id()});

    Entity Shoot2 = reg.spawn_entity();
    reg.add_component<component::velocity>(Shoot2, {10, 10});
    reg.add_component<component::attribute>(Shoot2, {component::attribute::Shoot});
    reg.add_component<component::state>(Shoot2, {component::state::stateKey::Alive});
    reg.add_component<component::idPlayer>(Shoot2, {player.get_id()});

    Entity Shoot3 = reg.spawn_entity();
    reg.add_component<component::velocity>(Shoot3, {10, 10});
    reg.add_component<component::attribute>(Shoot3, {component::attribute::Shoot});
    reg.add_component<component::state>(Shoot3, {component::state::stateKey::Alive});
    reg.add_component<component::idPlayer>(Shoot3, {player.get_id()});

    sys.update_shoot_velocity_p4(reg);
    auto &vel1 = velo[Shoot.get_id()];

    cr_assert_eq(vel1.x, 15, "Expected velocity x to be 15, but got %d", vel1.x);
    cr_assert_eq(vel1.y, 15, "Expected velocity y to be 15, but got %d", vel1.y);

    auto &vel2 = velo[Shoot2.get_id()];

    cr_assert_eq(vel2.x, 15, "Expected velocity x to be 15, but got %d", vel2.x);
    cr_assert_eq(vel2.y, 15, "Expected velocity y to be 15, but got %d", vel2.y);

    auto &vel3 = velo[Shoot3.get_id()];

    cr_assert_eq(vel3.x, 15, "Expected velocity x to be 15, but got %d", vel3.x);
    cr_assert_eq(vel3.y, 15, "Expected velocity y to be 15, but got %d", vel3.y);
}

Test(system, reset_shoot_player1) {
    registry reg;
    System sys;

    auto &velo = reg.register_component<component::velocity>();

    Entity player = reg.spawn_entity();
    reg.add_component<component::velocity>(player, {10, 10});
    reg.add_component<component::attribute>(player, {component::attribute::Player1});
    reg.add_component<component::state>(player, {component::state::stateKey::Alive});

    Entity Shoot = reg.spawn_entity();
    reg.add_component<component::velocity>(Shoot, {10, 10});
    reg.add_component<component::attribute>(Shoot, {component::attribute::Shoot});
    reg.add_component<component::state>(Shoot, {component::state::stateKey::Alive});
    reg.add_component<component::idPlayer>(Shoot, {player.get_id()});

    sys.reset_shoot_velocity_p1(reg);
    auto &vel = velo[Shoot.get_id()];

    cr_assert_eq(vel.x, 5, "Expected velocity x to be 5, but got %d", vel.x);
    cr_assert_eq(vel.y, 5, "Expected velocity y to be 5, but got %d", vel.y);
}

Test(system, reset_shoot_player2) {
    registry reg;
    System sys;

    auto &velo = reg.register_component<component::velocity>();

    Entity player = reg.spawn_entity();
    reg.add_component<component::velocity>(player, {10, 10});
    reg.add_component<component::attribute>(player, {component::attribute::Player2});
    reg.add_component<component::state>(player, {component::state::stateKey::Alive});

    Entity Shoot = reg.spawn_entity();
    reg.add_component<component::velocity>(Shoot, {10, 10});
    reg.add_component<component::attribute>(Shoot, {component::attribute::Shoot});
    reg.add_component<component::state>(Shoot, {component::state::stateKey::Alive});
    reg.add_component<component::idPlayer>(Shoot, {player.get_id()});

    sys.reset_shoot_velocity_p2(reg);
    auto &vel = velo[Shoot.get_id()];

    cr_assert_eq(vel.x, 5, "Expected velocity x to be 5, but got %d", vel.x);
    cr_assert_eq(vel.y, 5, "Expected velocity y to be 5, but got %d", vel.y);
}

Test(system, reset_shoot_player3) {
    registry reg;
    System sys;

    auto &velo = reg.register_component<component::velocity>();

    Entity player = reg.spawn_entity();
    reg.add_component<component::velocity>(player, {10, 10});
    reg.add_component<component::attribute>(player, {component::attribute::Player3});
    reg.add_component<component::state>(player, {component::state::stateKey::Alive});

    Entity Shoot = reg.spawn_entity();
    reg.add_component<component::velocity>(Shoot, {10, 10});
    reg.add_component<component::attribute>(Shoot, {component::attribute::Shoot});
    reg.add_component<component::state>(Shoot, {component::state::stateKey::Alive});
    reg.add_component<component::idPlayer>(Shoot, {player.get_id()});

    sys.reset_shoot_velocity_p3(reg);
    auto &vel = velo[Shoot.get_id()];

    cr_assert_eq(vel.x, 5, "Expected velocity x to be 5, but got %d", vel.x);
    cr_assert_eq(vel.y, 5, "Expected velocity y to be 5, but got %d", vel.y);
}

Test(system, reset_shoot_player4) {
    registry reg;
    System sys;

    auto &velo = reg.register_component<component::velocity>();

    Entity player = reg.spawn_entity();
    reg.add_component<component::velocity>(player, {10, 10});
    reg.add_component<component::attribute>(player, {component::attribute::Player4});
    reg.add_component<component::state>(player, {component::state::stateKey::Alive});

    Entity Shoot = reg.spawn_entity();
    reg.add_component<component::velocity>(Shoot, {10, 10});
    reg.add_component<component::attribute>(Shoot, {component::attribute::Shoot});
    reg.add_component<component::state>(Shoot, {component::state::stateKey::Alive});
    reg.add_component<component::idPlayer>(Shoot, {player.get_id()});

    sys.reset_shoot_velocity_p4(reg);
    auto &vel = velo[Shoot.get_id()];

    cr_assert_eq(vel.x, 5, "Expected velocity x to be 5, but got %d", vel.x);
    cr_assert_eq(vel.y, 5, "Expected velocity y to be 5, but got %d", vel.y);
}
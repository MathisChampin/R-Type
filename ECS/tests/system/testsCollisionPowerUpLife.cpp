#include <criterion/criterion.h>
#include "position.hpp"
#include "size.hpp"
#include "system.hpp"
#include "attribute.hpp"
#include "state.hpp"
#include "Registry.hpp"
#include "velocity.hpp"
#include "life.hpp"

Test(system, collision_system_player_powerup_detects_life_collision) {
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
    reg.add_component<component::attribute>(powerUp, {component::attribute::PowerUpLife});
    reg.add_component<component::state>(powerUp, {component::state::stateKey::Alive});

    bool result = sys.collision_power_up(reg);
    cr_assert(result, "Expected collision_system_player_powerup to return true for collision");
}

Test(system, collision_system_player_powerup_no_collision_life) {
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
    reg.add_component<component::attribute>(powerUp, {component::attribute::PowerUpLife});
    reg.add_component<component::state>(powerUp, {component::state::stateKey::Alive});

    bool result = sys.collision_power_up(reg);
    cr_assert_not(result, "Expected collision_system_player_powerup to return false for no collision");
}

Test(system, life_player1) {
    registry reg;
    System sys;

    auto &life = reg.register_component<component::life>();

    Entity player = reg.spawn_entity();
    reg.add_component<component::life>(player, {10});
    reg.add_component<component::attribute>(player, {component::attribute::Player1});
    reg.add_component<component::state>(player, {component::state::stateKey::Alive});

    sys.power_up_life_p1(reg);
    auto &l = life[player.get_id()];

    cr_assert_eq(l.life, 11, "Expected life to be 11, but got %d", l.life);
}

Test(system, life_player2) {
    registry reg;
    System sys;

    auto &life = reg.register_component<component::life>();

    Entity player = reg.spawn_entity();
    reg.add_component<component::life>(player, {10});
    reg.add_component<component::attribute>(player, {component::attribute::Player2});
    reg.add_component<component::state>(player, {component::state::stateKey::Alive});

    sys.power_up_life_p2(reg);
    auto &l = life[player.get_id()];

    cr_assert_eq(l.life, 11, "Expected life to be 11, but got %d", l.life);
}

Test(system, life_player3) {
    registry reg;
    System sys;

    auto &life = reg.register_component<component::life>();

    Entity player = reg.spawn_entity();
    reg.add_component<component::life>(player, {10});
    reg.add_component<component::attribute>(player, {component::attribute::Player3});
    reg.add_component<component::state>(player, {component::state::stateKey::Alive});

    sys.power_up_life_p3(reg);
    auto &l = life[player.get_id()];

    cr_assert_eq(l.life, 11, "Expected life to be 11, but got %d", l.life);
}

Test(system, life_player4) {
    registry reg;
    System sys;

    auto &life = reg.register_component<component::life>();

    Entity player = reg.spawn_entity();
    reg.add_component<component::life>(player, {10});
    reg.add_component<component::attribute>(player, {component::attribute::Player4});
    reg.add_component<component::state>(player, {component::state::stateKey::Alive});

    sys.power_up_life_p4(reg);
    auto &l = life[player.get_id()];

    cr_assert_eq(l.life, 11, "Expected life to be 11, but got %d", l.life);
}
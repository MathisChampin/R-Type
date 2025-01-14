#include <criterion/criterion.h>
#include <chrono>
#include <thread>
#include "Registry.hpp"
#include "system.hpp"
#include "attribute.hpp"
#include "position.hpp"
#include "size.hpp"
#include "score.hpp"
#include "state.hpp"
#include "life.hpp"
#include "idPlayer.hpp"

Test(spawn_power_up, creates_power_up_every_5_seconds) {

    registry reg;
    System sys;
    int i = 0;

    for (; i < 2; ++i) {
        sys.spawn_power_up(reg);
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    cr_assert_eq(i, 2, "Expected 2 entities, but got %zu", i);
}

Test(spawn_power_up, creates_power_up_life) {
    registry reg;
    System sys;
    Entity tmp;

    auto &pos = reg.register_component<component::position>();
    reg.register_component<component::size>();
    auto &attribute = reg.register_component<component::attribute>();
    reg.register_component<component::score>();
    reg.register_component<component::idPlayer>();
    reg.register_component<component::state>();

    Entity player = reg.spawn_entity();
    reg.add_component<component::position>(player, {10, 10});
    reg.add_component<component::size>(player, {5, 5});
    reg.add_component<component::attribute>(player, {component::attribute::Player1});
    reg.add_component<component::life>(player, {3});
    reg.add_component<component::score>(player, {0});
    reg.add_component<component::state>(player, {component::state::stateKey::Alive});

    Entity enemy = reg.spawn_entity();
    reg.add_component<component::position>(enemy, {20, 20});
    reg.add_component<component::size>(enemy, {5, 5});
    reg.add_component<component::attribute>(enemy, {component::attribute::Ennemies});
    reg.add_component<component::life>(enemy, {1});
    reg.add_component<component::state>(enemy, {component::state::stateKey::Alive});

    Entity shoot = reg.spawn_entity();
    reg.add_component<component::position>(shoot, {20, 22});
    reg.add_component<component::size>(shoot, {1, 1});
    reg.add_component<component::attribute>(shoot, {component::attribute::Shoot});
    reg.add_component<component::idPlayer>(shoot, {player.get_id()});
    reg.add_component<component::state>(shoot, {component::state::stateKey::Alive});

    sys.collision_system(reg);
    sys.spawn_power_up_life(reg);

    for (size_t i = 0; i < attribute.size(); i++) {
        if (attribute[i]._type == component::attribute::PowerUpLife) {
            tmp = reg.get_entity(i);

        }
    }

    cr_assert_eq(attribute[tmp.get_id()]._type, 16, "L'attrbut de power up devrait être 16 but got %d.", attribute[tmp.get_id()]._type);
    cr_assert_eq(pos[tmp.get_id()].x, 20, "L'attrbut de power up devrait être 20 but got %d.", pos[tmp.get_id()].x);
    cr_assert_eq(pos[tmp.get_id()].y, 20, "L'attrbut de power up devrait être 20 but got %d.", pos[tmp.get_id()].y);
}

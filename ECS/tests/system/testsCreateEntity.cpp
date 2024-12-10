#include "Registry.hpp"
#include "system.hpp"
#include "attribute.hpp"
#include "controllable.hpp"
#include "level.hpp"
#include "life.hpp"
#include "position.hpp"
#include "score.hpp"
#include "size.hpp"
#include "state.hpp"
#include "velocity.hpp"
#include "Entity.hpp"

#include <criterion/criterion.h>

Test(PlayerSystem, tests_registry_player) {
    registry reg;
    System sys;

    sys.registry_system(reg);
    sys.player_system(reg);
    sys.ennemies_system(reg);

    auto &attributes = reg.get_components<component::attribute>();
    auto &positions = reg.get_components<component::position>();
    auto &velocity = reg.get_components<component::velocity>();
    auto &controllable = reg.get_components<component::controllable>();
    auto &level = reg.get_components<component::level>();
    auto &life = reg.get_components<component::life>();
    auto &score = reg.get_components<component::score>();
    auto &size = reg.get_components<component::size>();
    auto &state = reg.get_components<component::state>();
    Entity player;

    for (size_t i = 0; i < attributes.size(); i++) {
        auto &a = attributes[i];
        if (a._type == component::attribute::Player) {
            player = reg.get_entity(i);
        }
    }

    auto &pos = positions[player.get_id()];
    auto &vel = velocity[player.get_id()];
    auto &ctrl = controllable[player.get_id()];
    auto &l = level[player.get_id()];
    auto &lf = life[player.get_id()];
    auto &s = score[player.get_id()];
    auto &sz = size[player.get_id()];
    auto &st = state[player.get_id()];

    cr_assert_eq(vel.x, 0, "Expected velocity x to be 0, but got %d", vel.x);
    cr_assert_eq(vel.y, 0, "Expected velocity y to be 0, but got %d", vel.y);
    cr_assert_eq(pos.x, 50, "Expected position x to be 50, but got %d", pos.x);
    cr_assert_eq(pos.y, 500, "Expected position y to be 500, but got %d", pos.y);
    cr_assert_eq(ctrl.active_key, 4, "Expected controllable to be 4, but got %d", ctrl.active_key);
    cr_assert_eq(l._levelKey, 0, "Expected level to be 0, but got %d", l._levelKey);
    cr_assert_eq(lf.life, 4, "Expected life to be 4, but got %d", lf.life);
    cr_assert_eq(s.score, 0, "Expected score to be 0, but got %d", s.score);
    cr_assert_eq(sz.x, 32, "Expected life to be 32, but got %d", sz.x);
    cr_assert_eq(sz.y, 14, "Expected life to be 14, but got %d", sz.y);
    cr_assert_eq(st._stateKey, 1, "Expected state to be 1, but got %d", st._stateKey);
}

Test(PlayerSystem, tests_registry_ennemies) {
    registry reg;
    System sys;

    sys.registry_system(reg);
    sys.player_system(reg);
    sys.ennemies_system(reg);

    auto &attributes = reg.get_components<component::attribute>();
    auto &positions = reg.get_components<component::position>();
    auto &velocity = reg.get_components<component::velocity>();
    auto &level = reg.get_components<component::level>();
    auto &life = reg.get_components<component::life>();
    auto &size = reg.get_components<component::size>();
    auto &state = reg.get_components<component::state>();
    Entity ennemies;

    for (size_t i = 0; i < attributes.size(); i++) {
        auto &a = attributes[i];
        if (a._type == component::attribute::Ennemies) {
            ennemies = reg.get_entity(i);
        }
    }

    auto &pos = positions[ennemies.get_id()];
    auto &vel = velocity[ennemies.get_id()];
    auto &l = level[ennemies.get_id()];
    auto &lf = life[ennemies.get_id()];
    auto &sz = size[ennemies.get_id()];
    auto &st = state[ennemies.get_id()];

    cr_assert_eq(vel.x, 20, "Expected velocity x to be 20, but got %d", vel.x);
    cr_assert_eq(vel.y, 0, "Expected velocity y to be 0, but got %d", vel.y);
    cr_assert_eq(pos.x, 1920, "Expected position x to be 1920, but got %d", pos.x);
    cr_assert_eq(l._levelKey, 0, "Expected level to be 0, but got %d", l._levelKey);
    cr_assert_eq(lf.life, 1, "Expected life to be 1, but got %d", lf.life);
    cr_assert_eq(sz.x, 32, "Expected life to be 32, but got %d", sz.x);
    cr_assert_eq(sz.y, 14, "Expected life to be 14, but got %d", sz.y);
    cr_assert_eq(st._stateKey, 1, "Expected state to be 1, but got %d", st._stateKey);
}

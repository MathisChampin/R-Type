#include <criterion/criterion.h>
#include "system.hpp"
#include "controllable.hpp"
#include "velocity.hpp"
#include "position.hpp"
#include "idPlayer.hpp"
#include "attribute.hpp"
#include "size.hpp"

Test(ControlSystem, MoveRight) {
    registry reg;
    System sys;

    auto &velocities = reg.register_component<component::velocity>();
    reg.register_component<component::controllable>();

    Entity entity = reg.spawn_entity();
    reg.add_component<component::velocity>(entity, {0, 0});
    reg.add_component<component::controllable>(entity, {component::controllable::Right});

    sys.control_system(reg);

    const auto &vel = velocities[entity.get_id()];
    cr_assert_eq(vel.x, 1, "Expected velocity x to be 1, but got %d", vel.x);
    cr_assert_eq(vel.y, 0, "Expected velocity y to be 0, but got %d", vel.y);
}

Test(ControlSystem, MoveUp) {
    registry reg;
    System sys;

    auto &velocities = reg.register_component<component::velocity>();
    reg.register_component<component::controllable>();

    Entity entity = reg.spawn_entity();
    reg.add_component<component::velocity>(entity, {0, 0});
    reg.add_component<component::controllable>(entity, {component::controllable::Up});

    sys.control_system(reg);

    const auto &vel = velocities[entity.get_id()];
    cr_assert_eq(vel.x, 0, "Expected velocity x to be 0, but got %d", vel.x);
    cr_assert_eq(vel.y, -1, "Expected velocity y to be -1, but got %d", vel.y);
}

Test(ControlSystem, MoveDown) {
    registry reg;
    System sys;

    auto &velocities = reg.register_component<component::velocity>();
    reg.register_component<component::controllable>();

    Entity entity = reg.spawn_entity();
    reg.add_component<component::velocity>(entity, {0, 0});
    reg.add_component<component::controllable>(entity, {component::controllable::Down});

    sys.control_system(reg);

    const auto &vel = velocities[entity.get_id()];
    cr_assert_eq(vel.x, 0, "Expected velocity x to be 0, but got %d", vel.x);
    cr_assert_eq(vel.y, 1, "Expected velocity y to be 1, but got %d", vel.y);
}

Test(ControlSystem, MoveLeft) {
    registry reg;
    System sys;

    auto &velocities = reg.register_component<component::velocity>();
    reg.register_component<component::controllable>();

    Entity entity = reg.spawn_entity();
    reg.add_component<component::velocity>(entity, {0, 0});
    reg.add_component<component::controllable>(entity, {component::controllable::Left});

    sys.control_system(reg);

    const auto &vel = velocities[entity.get_id()];
    cr_assert_eq(vel.x, -1, "Expected velocity x to be -1, but got %d", vel.x);
    cr_assert_eq(vel.y, 0, "Expected velocity y to be 0, but got %d", vel.y);
}

Test(ControlSystem, MoveShoot) {
    registry reg;
    System sys;

    reg.register_component<component::controllable>();
    auto &posi = reg.register_component<component::position>();
    auto &att = reg.register_component<component::attribute>();
    auto &idP = reg.register_component<component::idPlayer>();

    Entity player = reg.spawn_entity();
    reg.add_component<component::position>(player, {20, 10});
    reg.add_component<component::controllable>(player, {component::controllable::NoKey});

    Entity player1 = reg.spawn_entity();
    reg.add_component<component::position>(player1, {20, 10});
    reg.add_component<component::controllable>(player1, {component::controllable::Shoot});

    sys.shoot_system(reg);

    Entity shoot;
    for (size_t i = 0; i < att.size(); i++) {
        const auto &attr = att[i];
        if (attr._type == component::attribute::Shoot) {
            shoot = reg.get_entity(i);
            break;
        }
    }

    const auto &pos = posi[shoot.get_id()];
    const auto &id = idP[shoot.get_id()];

    cr_assert_eq(pos.x, 20, "Expected shoot position x to be 20, but got %d", pos.x);
    cr_assert_eq(pos.y, 10, "Expected shoot position y to be 10, but got %d", pos.y);
    cr_assert_eq(player1.get_id(), 1, "Expected shoot id 1 to be %d, but got %d", id);
    cr_assert_eq(vel.x, 10, "Expected shoot velocity x to be 10, but got %d", vel.x);
    cr_assert_eq(vel.y, 0, "Expected shoot velocity y to be 0, but got %d", vel.y);
}



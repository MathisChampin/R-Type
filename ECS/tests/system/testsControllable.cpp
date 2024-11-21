#include <criterion/criterion.h>
#include "system.hpp"
#include "controllable.hpp"
#include "velocity.hpp"

Test(ControlSystem, MoveRight) {
    registry reg;
    System sys;

    auto &velocities = reg.register_component<component::velocity>();
    reg.register_component<component::controllable>();

    entity_t entity = reg.spawn_entity();
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

    entity_t entity = reg.spawn_entity();
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

    entity_t entity = reg.spawn_entity();
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

    entity_t entity = reg.spawn_entity();
    reg.add_component<component::velocity>(entity, {0, 0});
    reg.add_component<component::controllable>(entity, {component::controllable::Left});

    sys.control_system(reg);

    const auto &vel = velocities[entity.get_id()];
    cr_assert_eq(vel.x, -1, "Expected velocity x to be -1, but got %d", vel.x);
    cr_assert_eq(vel.y, 0, "Expected velocity y to be 0, but got %d", vel.y);
}

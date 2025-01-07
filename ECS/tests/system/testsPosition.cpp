#include <criterion/criterion.h>
#include "system.hpp"
#include "position.hpp"
#include "velocity.hpp"
#include "attribute.hpp"

Test(PositionSystem, UpdatePositionEnnemies1) {
    registry reg;
    System sys;

    auto& positions = reg.register_component<component::position>();
    reg.register_component<component::velocity>();

    Entity entity = reg.spawn_entity();
    reg.add_component<component::position>(entity, {10, 20});
    reg.add_component<component::velocity>(entity, {5, 0});
    reg.add_component<component::attribute>(entity, {component::attribute::Ennemies});

    sys.position_system(reg);

    const auto& pos = positions[entity.get_id()];
    cr_assert_eq(pos.x, 15, "Expected position x to be 15, but got %d", pos.x);
    cr_assert_eq(pos.y, 20, "Expected position y to remain 20, but got %d", pos.y);
}

Test(PositionSystem, UpdatePositionEnnemies2) {
    registry reg;
    System sys;

    auto& positions = reg.register_component<component::position>();
    reg.register_component<component::velocity>();

    Entity entity = reg.spawn_entity();
    reg.add_component<component::position>(entity, {30, 40});
    reg.add_component<component::velocity>(entity, {0, -5});
    reg.add_component<component::attribute>(entity, {component::attribute::Ennemies2});

    sys.position_system(reg);

    const auto& pos = positions[entity.get_id()];
    cr_assert_eq(pos.x, 30, "Expected position x to remain 30, but got %d", pos.x);
    cr_assert_eq(pos.y, 35, "Expected position y to be 35, but got %d", pos.y);
}

Test(PositionSystem, UpdatePositionEnnemies3) {
    registry reg;
    System sys;

    auto& positions = reg.register_component<component::position>();
    auto& velocities = reg.register_component<component::velocity>();
    reg.register_component<component::attribute>();

    Entity entity = reg.spawn_entity();
    reg.add_component<component::position>(entity, {50, 100});
    reg.add_component<component::velocity>(entity, {3, 4});
    reg.add_component<component::attribute>(entity, {component::attribute::Ennemies3});

    sys.position_system(reg);

    const auto& pos = positions[entity.get_id()];
    const auto& vel = velocities[entity.get_id()];
    cr_assert_eq(pos.x, 53, "Expected position x to be 53, but got %d", pos.x);
    cr_assert_eq(pos.y, 104, "Expected position y to be 104, but got %d", pos.y);

    positions[entity.get_id()].y = 1080;
    sys.position_system(reg);
    cr_assert_eq(vel.y, -4, "Expected velocity y to change to -4 when reaching the bottom, but got %d", vel.y);

    positions[entity.get_id()].y = 0;
    sys.position_system(reg);
    cr_assert_eq(vel.y, 4, "Expected velocity y to change to 4 when reaching the top, but got %d", vel.y);
}

Test(PositionSystem, UpdatePositionEnnemies4) {
    registry reg;
    System sys;

    auto& positions = reg.register_component<component::position>();
    auto& velocities = reg.register_component<component::velocity>();
    reg.register_component<component::attribute>();

    Entity entity = reg.spawn_entity();
    reg.add_component<component::position>(entity, {100, 500});
    reg.add_component<component::velocity>(entity, {2, -5});
    reg.add_component<component::attribute>(entity, {component::attribute::Ennemies4});

    sys.position_system(reg);

    const auto& pos = positions[entity.get_id()];
    const auto& vel = velocities[entity.get_id()];
    cr_assert_eq(pos.x, 102, "Expected position x to be 102, but got %d", pos.x);
    cr_assert_eq(pos.y, 495, "Expected position y to be 495, but got %d", pos.y);

    positions[entity.get_id()].y = 0;
    sys.position_system(reg);
    cr_assert_eq(vel.y, 5, "Expected velocity y to change to 5 when reaching the top, but got %d", vel.y);

    positions[entity.get_id()].y = 1080;
    sys.position_system(reg);
    cr_assert_eq(vel.y, -5, "Expected velocity y to change to -5 when reaching the bottom, but got %d", vel.y);
}

Test(PositionSystem, UpdatePositionEnnemies5) {
    registry reg;
    System sys;

    auto& positions = reg.register_component<component::position>();
    reg.register_component<component::velocity>();
    reg.register_component<component::attribute>();

    Entity entity = reg.spawn_entity();
    reg.add_component<component::position>(entity, {200, 300});
    reg.add_component<component::velocity>(entity, {0, 0});
    reg.add_component<component::attribute>(entity, {component::attribute::Ennemies5});

    sys.position_system(reg);

    const auto& pos = positions[entity.get_id()];
    cr_assert_eq(pos.x, 200, "Expected position x to remain 200, but got %d", pos.x);
    cr_assert_eq(pos.y, 300, "Expected position y to remain 300, but got %d", pos.y);
}

Test(PositionSystem, UpdatePositionShoot) {
    registry reg;
    System sys;

    auto& positions = reg.register_component<component::position>();
    reg.register_component<component::velocity>();
    reg.register_component<component::attribute>();

    Entity entity1 = reg.spawn_entity();
    reg.add_component<component::position>(entity1, {10, 20});
    reg.add_component<component::velocity>(entity1, {5, 0});
    reg.add_component<component::attribute>(entity1, {component::attribute::Shoot});

    sys.position_system(reg);

    const auto& pos1 = positions[entity1.get_id()];
    cr_assert_eq(pos1.x, 15, "Expected position x to be 15, but got %d", pos1.x);
    cr_assert_eq(pos1.y, 20, "Expected position y to remain 20, but got %d", pos1.y);

    Entity entity2 = reg.spawn_entity();
    reg.add_component<component::position>(entity2, {30, 40});
    reg.add_component<component::velocity>(entity2, {0, -5});
    reg.add_component<component::attribute>(entity2, {component::attribute::Shoot2});

    sys.position_system(reg);

    const auto& pos2 = positions[entity2.get_id()];
    cr_assert_eq(pos2.x, 30, "Expected position x to remain 30, but got %d", pos2.x);
    cr_assert_eq(pos2.y, 40, "Expected position y to be 40, but got %d", pos2.y);

    Entity entity3 = reg.spawn_entity();
    reg.add_component<component::position>(entity3, {50, 100});
    reg.add_component<component::velocity>(entity3, {3, 4});
    reg.add_component<component::attribute>(entity3, {component::attribute::Shoot3});

    sys.position_system(reg);

    const auto& pos3 = positions[entity3.get_id()];
    cr_assert_eq(pos3.x, 53, "Expected position x to be 53, but got %d", pos3.x);
    cr_assert_eq(pos3.y, 104, "Expected position y to be 104, but got %d", pos3.y);

    positions[entity3.get_id()].y = 1080;
    sys.position_system(reg);
    cr_assert_eq(positions[entity3.get_id()].y, 1076, "Expected position y to remain 1076, but got %d", positions[entity3.get_id()].y);

    positions[entity3.get_id()].y = 0;
    sys.position_system(reg);
    cr_assert_eq(positions[entity3.get_id()].y, 4, "Expected position y to remain 4, but got %d", positions[entity3.get_id()].y);

    Entity entity5 = reg.spawn_entity();
    reg.add_component<component::position>(entity5, {200, 300});
    reg.add_component<component::velocity>(entity5, {2, -3});
    reg.add_component<component::attribute>(entity5, {component::attribute::Shoot5});

    sys.position_system(reg);

    const auto& pos5 = positions[entity5.get_id()];
    cr_assert_eq(pos5.x, 202, "Expected position x to be 202, but got %d", pos5.x);
    cr_assert_eq(pos5.y, 297, "Expected position y to be 297, but got %d", pos5.y);

    positions[entity5.get_id()].y = 1080;
    sys.position_system(reg);
    cr_assert_eq(positions[entity5.get_id()].y, 1077, "Expected position y to remain 1077, but got %d", positions[entity5.get_id()].y);

    positions[entity5.get_id()].y = 0;
    sys.position_system(reg);
    cr_assert_eq(positions[entity5.get_id()].y, 3, "Expected position y to remain 3, but got %d", positions[entity5.get_id()].y);
}

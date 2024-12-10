#include <criterion/criterion.h>
#include "system.hpp"
#include "position.hpp"
#include "velocity.hpp"
#include "attribute.hpp"

Test(PositionSystem, UpdatePositionSingleEntity) {
    registry reg;
    System sys;

    auto& positions = reg.register_component<component::position>();
    reg.register_component<component::velocity>();

    Entity entity = reg.spawn_entity();
    reg.add_component<component::position>(entity, {10, 20});
    reg.add_component<component::velocity>(entity, {5, -3});
    reg.add_component<component::attribute>(entity, {component::attribute::Ennemies});
    sys.position_system(reg);

    const auto& pos = positions[entity.get_id()];
    cr_assert_eq(pos.x, 15, "Expected position x to be 15, but got %d", pos.x);
    cr_assert_eq(pos.y, 20, "Expected position y to be 20, but got %d", pos.y);
}

Test(PositionSystem, UpdatePositionMultipleEntities) {
    registry reg;
    System sys;

    auto& positions = reg.register_component<component::position>();
    reg.register_component<component::velocity>();

    Entity entity1 = reg.spawn_entity();
    reg.add_component<component::position>(entity1, {10, 20});
    reg.add_component<component::velocity>(entity1, {5, 5});
    reg.add_component<component::attribute>(entity1, {component::attribute::Ennemies});
    Entity entity2 = reg.spawn_entity();
    reg.add_component<component::position>(entity2, {12, 30});
    reg.add_component<component::velocity>(entity2, {-3, 2});
    reg.add_component<component::attribute>(entity2, {component::attribute::Ennemies});

    sys.position_system(reg);

    const auto& pos1 = positions[entity1.get_id()];
    const auto& pos2 = positions[entity2.get_id()];

    cr_assert_eq(pos1.x, 15, "Expected position x for entity1 to be 15, but got %d", pos1.x);
    cr_assert_eq(pos1.y, 20, "Expected position y for entity1 to be 20, but got %d", pos1.y);

    cr_assert_eq(pos2.x, 9, "Expected position x for entity2 to be 9, but got %d", pos2.x);
    cr_assert_eq(pos2.y, 30, "Expected position y for entity2 to be 30, but got %d", pos2.y);
}

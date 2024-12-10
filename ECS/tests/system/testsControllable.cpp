#include <criterion/criterion.h>
#include "system.hpp"
#include "controllable.hpp"
#include "position.hpp"
#include "idPlayer.hpp"
#include "attribute.hpp"
#include "size.hpp"

Test(ControlSystem, MoveRight) {
    registry reg;
    System sys;

    auto &positions = reg.register_component<component::position>();
    reg.register_component<component::controllable>();

    Entity entity = reg.spawn_entity();
    reg.add_component<component::position>(entity, {0, 0});
    reg.add_component<component::controllable>(entity, {component::controllable::Right});

    sys.control_system(reg);

    const auto &pos = positions[entity.get_id()];
    cr_assert_eq(pos.x, 1, "Expected position x to be 1, but got %d", pos.x);
    cr_assert_eq(pos.y, 0, "Expected position y to be 0, but got %d", pos.y);
}

Test(ControlSystem, MoveUp) {
    registry reg;
    System sys;

    auto &positions = reg.register_component<component::position>();
    reg.register_component<component::controllable>();

    Entity entity = reg.spawn_entity();
    reg.add_component<component::position>(entity, {0, 0});
    reg.add_component<component::controllable>(entity, {component::controllable::Up});

    sys.control_system(reg);

    const auto &pos = positions[entity.get_id()];
    cr_assert_eq(pos.x, 0, "Expected position x to be 0, but got %d", pos.x);
    cr_assert_eq(pos.y, -1, "Expected position y to be -1, but got %d", pos.y);
}

Test(ControlSystem, MoveDown) {
    registry reg;
    System sys;

    auto &positions = reg.register_component<component::position>();
    reg.register_component<component::controllable>();

    Entity entity = reg.spawn_entity();
    reg.add_component<component::position>(entity, {0, 0});
    reg.add_component<component::controllable>(entity, {component::controllable::Down});

    sys.control_system(reg);

    const auto &pos = positions[entity.get_id()];
    cr_assert_eq(pos.x, 0, "Expected position x to be 0, but got %d", pos.x);
    cr_assert_eq(pos.y, 1, "Expected position y to be 1, but got %d", pos.y);
}

Test(ControlSystem, MoveLeft) {
    registry reg;
    System sys;

    auto &positions = reg.register_component<component::position>();
    reg.register_component<component::controllable>();

    Entity entity = reg.spawn_entity();
    reg.add_component<component::position>(entity, {0, 0});
    reg.add_component<component::controllable>(entity, {component::controllable::Left});

    sys.control_system(reg);

    const auto &pos = positions[entity.get_id()];
    cr_assert_eq(pos.x, -1, "Expected position x to be -1, but got %d", pos.x);
    cr_assert_eq(pos.y, 0, "Expected position y to be 0, but got %d", pos.y);
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

    sys.shoot_system_player(reg);

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
}

Test(System, ShootSystemEnnemies_Single) {
    registry reg;
    System sys;

    auto &att = reg.register_component<component::attribute>();
    auto &posi = reg.register_component<component::position>();
    auto &idP = reg.register_component<component::idPlayer>();

    Entity enemy = reg.spawn_entity();
    reg.add_component<component::attribute>(enemy, {component::attribute::Ennemies});
    reg.add_component<component::position>(enemy, {30, 40});

    sys.shoot_system_ennemies(reg);

    Entity shoot;
    for (size_t i = 0; i < posi.size(); i++) {
        const auto &attr = att[i];
        if (attr._type == component::attribute::Shoot) {
            shoot = reg.get_entity(i);
            break;
        }
    }

    const auto &pos = posi[shoot.get_id()];
    const auto &id = idP[shoot.get_id()];

    cr_assert_eq(pos.x, 30, "Expected shoot position x to be 30, but got %d", pos.x);
    cr_assert_eq(pos.y, 40, "Expected shoot position y to be 40, but got %d", pos.y);
    cr_assert_eq(enemy.get_id(), 0, "Expected shoot id 0 to be %d, but got %d", id);
}

Test(System, ShootSystemEnnemies_Multiple) {
    registry reg;
    System sys;

    int shoot_count = 0;
    auto &att = reg.register_component<component::attribute>();
    auto &posi = reg.register_component<component::position>();
    auto &idP = reg.register_component<component::idPlayer>();

    Entity enemy1 = reg.spawn_entity();
    reg.add_component<component::attribute>(enemy1, {component::attribute::Ennemies});
    reg.add_component<component::position>(enemy1, {50, 60});

    Entity enemy2 = reg.spawn_entity();
    reg.add_component<component::attribute>(enemy2, {component::attribute::Ennemies});
    reg.add_component<component::position>(enemy2, {70, 80});

    sys.shoot_system_ennemies(reg);

    for (size_t i = 0; i < posi.size(); i++) {
        const auto &attr = att[i];
        if (attr._type == component::attribute::Shoot) {
            shoot_count++;
            const auto &pos = posi[i];
            const auto &id = idP[i];
            if (pos.x == 50 && pos.y == 60)
                cr_assert_eq(enemy1.get_id(), 0, "Expected shoot id 0 to be %d, but got %d", id);
            if (pos.x == 70 && pos.y == 80)
                cr_assert_eq(enemy2.get_id(), 1, "Expected shoot id 1 to be %d, but got %d", id);
        }
    }
    cr_assert_eq(shoot_count, 2, "Expected 2 shoot entities, but got %d", shoot_count);
}


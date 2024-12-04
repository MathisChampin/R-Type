#include <criterion/criterion.h>
#include "Registry.hpp"
#include "position.hpp"
#include "velocity.hpp"

Test(RegistryTests, RegisterOneComponent) {
    registry reg;

    auto &positions = reg.register_component<component::position>();

    positions.insert_at(0, {10, 20});
    const auto &pos1 = positions[0];

    cr_assert_eq(10, pos1.x, "La position x n'est pas la bonne valeur. Attendu: %d, Obtenu: %d", 10, pos1.x);
    cr_assert_eq(20, pos1.y, "La position x n'est pas la bonne valeur. Attendu: %d, Obtenu: %d", 20, pos1.y);
}

Test(RegistryTests, RegisterManyComponent) {
    registry reg;

    auto &positions = reg.register_component<component::position>();

    positions.insert_at(0, {10, 20});
    positions.insert_at(1, {30, 25});

    const auto &pos1 = positions[0];
    const auto &pos2 = positions[1];

    cr_assert_eq(10, pos1.x, "La position x n'est pas la bonne valeur. Attendu: %d, Obtenu: %d", 10, pos1.x);
    cr_assert_eq(20, pos1.y, "La position x n'est pas la bonne valeur. Attendu: %d, Obtenu: %d", 20, pos1.y);
    cr_assert_eq(30, pos2.x, "La position x n'est pas la bonne valeur. Attendu: %d, Obtenu: %d", 30, pos2.x);
    cr_assert_eq(25, pos2.y, "La position x n'est pas la bonne valeur. Attendu: %d, Obtenu: %d", 25, pos2.y);
}

Test(RegistryTests, RegisterManyComponentWith2Type) {
    registry reg;

    auto &positions = reg.register_component<component::position>();
    auto &velocity = reg.register_component<component::velocity>();

    positions.insert_at(0, {10, 20});
    positions.insert_at(1, {30, 25});
    velocity.insert_at(0, {15, 60});

    const auto &pos1 = positions[0];
    const auto &pos2 = positions[1];
    const auto &vel1 = velocity[0];

    cr_assert_eq(10, pos1.x, "La position x n'est pas la bonne valeur. Attendu: %d, Obtenu: %d", 10, pos1.x);
    cr_assert_eq(20, pos1.y, "La position y n'est pas la bonne valeur. Attendu: %d, Obtenu: %d", 20, pos1.y);
    cr_assert_eq(30, pos2.x, "La position x n'est pas la bonne valeur. Attendu: %d, Obtenu: %d", 30, pos2.x);
    cr_assert_eq(25, pos2.y, "La position y n'est pas la bonne valeur. Attendu: %d, Obtenu: %d", 25, pos2.y);
    cr_assert_eq(15, vel1.x, "La position vx n'est pas la bonne valeur. Attendu: %d, Obtenu: %d", 15, vel1.x);
    cr_assert_eq(60, vel1.y, "La position vy n'est pas la bonne valeur. Attendu: %d, Obtenu: %d", 60, vel1.y);
}

Test(RegistryTests, GetComponents) {
    registry reg;

    auto &positions = reg.register_component<component::position>();

    positions.insert_at(0, {10, 20});
    positions.insert_at(1, {30, 25});

    auto &getPos = reg.get_components<component::position>();

    const auto &pos1 = getPos[0];
    const auto &pos2 = getPos[1];

    cr_assert_eq(10, pos1.x, "La position x n'est pas la bonne valeur. Attendu: %d, Obtenu: %d", 10, pos1.x);
    cr_assert_eq(20, pos1.y, "La position x n'est pas la bonne valeur. Attendu: %d, Obtenu: %d", 20, pos1.y);
    cr_assert_eq(30, pos2.x, "La position x n'est pas la bonne valeur. Attendu: %d, Obtenu: %d", 30, pos2.x);
    cr_assert_eq(25, pos2.y, "La position x n'est pas la bonne valeur. Attendu: %d, Obtenu: %d", 25, pos2.y);
}

Test(RegistryTests, GetComponentsWithManyTypes) {
    registry reg;

    auto &positions = reg.register_component<component::position>();
    auto &velocity = reg.register_component<component::velocity>();

    positions.insert_at(0, {10, 20});
    positions.insert_at(1, {30, 25});
    velocity.insert_at(0, {15, 60});

    auto &getPos = reg.get_components<component::position>();
    auto &getVel = reg.get_components<component::velocity>();

    const auto &pos1 = getPos[0];
    const auto &pos2 = getPos[1];
    const auto &vel1 = getVel[0];

    cr_assert_eq(10, pos1.x, "La position x n'est pas la bonne valeur. Attendu: %d, Obtenu: %d", 10, pos1.x);
    cr_assert_eq(20, pos1.y, "La position y n'est pas la bonne valeur. Attendu: %d, Obtenu: %d", 20, pos1.y);
    cr_assert_eq(30, pos2.x, "La position x n'est pas la bonne valeur. Attendu: %d, Obtenu: %d", 30, pos2.x);
    cr_assert_eq(25, pos2.y, "La position y n'est pas la bonne valeur. Attendu: %d, Obtenu: %d", 25, pos2.y);
    cr_assert_eq(15, vel1.x, "La position vx n'est pas la bonne valeur. Attendu: %d, Obtenu: %d", 15, vel1.x);
    cr_assert_eq(60, vel1.y, "La position vy n'est pas la bonne valeur. Attendu: %d, Obtenu: %d", 60, vel1.y);
}

Test(RegistryTests, SpawnEntity) {
    registry reg;

    Entity entity1 = reg.spawn_entity();
    Entity entity2 = reg.spawn_entity();

    cr_assert_neq(entity1.get_id(), entity2.get_id(), "Les IDs des entités ne sont pas uniques");

    reg.kill_entity(entity1);
    Entity entity3 = reg.spawn_entity();

    cr_assert_eq(entity1.get_id(), entity3.get_id(), "L'ID de l'entité tuée n'a pas été réutilisé correctement");
}

Test(RegistryTests, KillEntity) {
    registry reg;

    auto &positions = reg.register_component<component::position>();

    Entity entity1 = reg.spawn_entity();
    positions.insert_at(entity1.get_id(), {10, 20});

    const auto &pos1 = positions[entity1.get_id()];
    cr_assert_eq(10, pos1.x);
    cr_assert_eq(20, pos1.y);

    reg.kill_entity(entity1);

    Entity entity2 = reg.spawn_entity();
    cr_assert_eq(entity1.get_id(), entity2.get_id(), "L'entité n'a pas été réutilisée correctement après suppression");
    cr_assert_eq(positions.size(), 0, "Le composant n'a pas été supprimé correctement lors de la suppression de l'entité");
}

Test(RegistryTests, AddComponent) {
    registry reg;

    auto &positions = reg.register_component<component::position>();

    Entity entity1 = reg.spawn_entity();

    auto &pos_ref = reg.add_component<component::position>(entity1, {10, 20});

    const auto &pos1 = positions[entity1.get_id()];
    cr_assert_eq(10, pos1.x);
    cr_assert_eq(20, pos1.y);
    cr_assert_eq(&pos_ref, &positions[entity1.get_id()], "La référence renvoyée par add_component n'est pas correcte");
}

Test(RegistryTests, EmplaceComponent) {
    registry reg;

    auto &positions = reg.register_component<component::position>();

    Entity entity1 = reg.spawn_entity();

    auto &pos_ref = reg.emplace_component<component::position>(entity1, 10, 20);

    const auto &pos1 = positions[entity1.get_id()];
    cr_assert_eq(10, pos1.x);
    cr_assert_eq(20, pos1.y);
    cr_assert_eq(&pos_ref, &positions[entity1.get_id()], "La référence renvoyée par emplace_component n'est pas correcte");
}

Test(RegistryTests, RemoveComponent) {
    registry reg;

    auto &positions = reg.register_component<component::position>();

    Entity entity1 = reg.spawn_entity();
    positions.insert_at(entity1.get_id(), {10, 20});

    const auto &pos1 = positions[entity1.get_id()];
    cr_assert_eq(10, pos1.x);
    cr_assert_eq(20, pos1.y);

    reg.remove_component<component::position>(entity1);
    cr_assert_eq(positions.size(), 0, "Le composant n'a pas été supprimé correctement");
}

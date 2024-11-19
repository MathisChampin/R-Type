#include <criterion/criterion.h>
#include "Registry.hpp"

struct Position {
    float x, y;
};

struct Velocity {
    float vx, vy;
};

Test(RegistryTests, RegisterOneComponent) {
    registry reg;

    auto &positions = reg.register_component<Position>();

    positions.insert_at(0, {10.0f, 20.0f});
    const auto &pos1 = positions[0];

    cr_assert_eq(10.0, pos1.x, "La position x n'est pas la bonne valeur. Attendu: %2f, Obtenu: %2f", 10.0, pos1.x);
    cr_assert_eq(20.0, pos1.y, "La position x n'est pas la bonne valeur. Attendu: %2f, Obtenu: %2f", 20.0, pos1.y);
}

Test(RegistryTests, RegisterManyComponent) {
    registry reg;

    auto &positions = reg.register_component<Position>();

    positions.insert_at(0, {10.0f, 20.0f});
    positions.insert_at(1, {30.0f, 25.0f});

    const auto &pos1 = positions[0];
    const auto &pos2 = positions[1];

    cr_assert_eq(10.0, pos1.x, "La position x n'est pas la bonne valeur. Attendu: %2f, Obtenu: %2f", 10.0, pos1.x);
    cr_assert_eq(20.0, pos1.y, "La position x n'est pas la bonne valeur. Attendu: %2f, Obtenu: %2f", 20.0, pos1.y);
    cr_assert_eq(30.0, pos2.x, "La position x n'est pas la bonne valeur. Attendu: %2f, Obtenu: %2f", 30.0, pos2.x);
    cr_assert_eq(25.0, pos2.y, "La position x n'est pas la bonne valeur. Attendu: %2f, Obtenu: %2f", 25.0, pos2.y);
}

Test(RegistryTests, RegisterManyComponentWith2Type) {
    registry reg;

    auto &positions = reg.register_component<Position>();
    auto &velocity = reg.register_component<Velocity>();

    positions.insert_at(0, {10.0f, 20.0f});
    positions.insert_at(1, {30.0f, 25.0f});
    velocity.insert_at(0, {15.0f, 60.0f});

    const auto &pos1 = positions[0];
    const auto &pos2 = positions[1];
    const auto &vel1 = velocity[0];

    cr_assert_eq(10.0, pos1.x, "La position x n'est pas la bonne valeur. Attendu: %2f, Obtenu: %2f", 10.0, pos1.x);
    cr_assert_eq(20.0, pos1.y, "La position y n'est pas la bonne valeur. Attendu: %2f, Obtenu: %2f", 20.0, pos1.y);
    cr_assert_eq(30.0, pos2.x, "La position x n'est pas la bonne valeur. Attendu: %2f, Obtenu: %2f", 30.0, pos2.x);
    cr_assert_eq(25.0, pos2.y, "La position y n'est pas la bonne valeur. Attendu: %2f, Obtenu: %2f", 25.0, pos2.y);
    cr_assert_eq(15.0, vel1.vx, "La position vx n'est pas la bonne valeur. Attendu: %2f, Obtenu: %2f", 15.0, vel1.vx);
    cr_assert_eq(60.0, vel1.vy, "La position vy n'est pas la bonne valeur. Attendu: %2f, Obtenu: %2f", 60.0, vel1.vy);
}

Test(RegistryTests, GetComponents) {
    registry reg;

    auto &positions = reg.register_component<Position>();

    positions.insert_at(0, {10.0f, 20.0f});
    positions.insert_at(1, {30.0f, 25.0f});

    auto &getPos = reg.get_components<Position>();

    const auto &pos1 = getPos[0];
    const auto &pos2 = getPos[1];

    cr_assert_eq(10.0, pos1.x, "La position x n'est pas la bonne valeur. Attendu: %2f, Obtenu: %2f", 10.0, pos1.x);
    cr_assert_eq(20.0, pos1.y, "La position x n'est pas la bonne valeur. Attendu: %2f, Obtenu: %2f", 20.0, pos1.y);
    cr_assert_eq(30.0, pos2.x, "La position x n'est pas la bonne valeur. Attendu: %2f, Obtenu: %2f", 30.0, pos2.x);
    cr_assert_eq(25.0, pos2.y, "La position x n'est pas la bonne valeur. Attendu: %2f, Obtenu: %2f", 25.0, pos2.y);
}

Test(RegistryTests, GetComponentsWithManyTypes) {
    registry reg;

    auto &positions = reg.register_component<Position>();
    auto &velocity = reg.register_component<Velocity>();

    positions.insert_at(0, {10.0f, 20.0f});
    positions.insert_at(1, {30.0f, 25.0f});
    velocity.insert_at(0, {15.0f, 60.0f});

    auto &getPos = reg.get_components<Position>();
    auto &getVel = reg.get_components<Velocity>();

    const auto &pos1 = getPos[0];
    const auto &pos2 = getPos[1];
    const auto &vel1 = getVel[0];

    cr_assert_eq(10.0, pos1.x, "La position x n'est pas la bonne valeur. Attendu: %2f, Obtenu: %2f", 10.0, pos1.x);
    cr_assert_eq(20.0, pos1.y, "La position y n'est pas la bonne valeur. Attendu: %2f, Obtenu: %2f", 20.0, pos1.y);
    cr_assert_eq(30.0, pos2.x, "La position x n'est pas la bonne valeur. Attendu: %2f, Obtenu: %2f", 30.0, pos2.x);
    cr_assert_eq(25.0, pos2.y, "La position y n'est pas la bonne valeur. Attendu: %2f, Obtenu: %2f", 25.0, pos2.y);
    cr_assert_eq(15.0, vel1.vx, "La position vx n'est pas la bonne valeur. Attendu: %2f, Obtenu: %2f", 15.0, vel1.vx);
    cr_assert_eq(60.0, vel1.vy, "La position vy n'est pas la bonne valeur. Attendu: %2f, Obtenu: %2f", 60.0, vel1.vy);
}

Test(RegistryTests, SpawnEntity) {
    registry reg;

    entity_t entity1 = reg.spawn_entity();
    entity_t entity2 = reg.spawn_entity();

    cr_assert_neq(entity1.get_id(), entity2.get_id(), "Les IDs des entités ne sont pas uniques");

    reg.kill_entity(entity1);
    entity_t entity3 = reg.spawn_entity();

    cr_assert_eq(entity1.get_id(), entity3.get_id(), "L'ID de l'entité tuée n'a pas été réutilisé correctement");
}

Test(RegistryTests, KillEntity) {
    registry reg;

    auto &positions = reg.register_component<Position>();

    entity_t entity1 = reg.spawn_entity();
    positions.insert_at(entity1.get_id(), {10.0f, 20.0f});

    const auto &pos1 = positions[entity1.get_id()];
    cr_assert_eq(10.0, pos1.x);
    cr_assert_eq(20.0, pos1.y);

    reg.kill_entity(entity1);

    entity_t entity2 = reg.spawn_entity();
    cr_assert_eq(entity1.get_id(), entity2.get_id(), "L'entité n'a pas été réutilisée correctement après suppression");
    cr_assert_eq(positions.size(), 0, "Le composant n'a pas été supprimé correctement lors de la suppression de l'entité");
}

Test(RegistryTests, AddComponent) {
    registry reg;

    auto &positions = reg.register_component<Position>();

    entity_t entity1 = reg.spawn_entity();

    auto &pos_ref = reg.add_component<Position>(entity1, {10.0f, 20.0f});

    const auto &pos1 = positions[entity1.get_id()];
    cr_assert_eq(10.0, pos1.x);
    cr_assert_eq(20.0, pos1.y);
    cr_assert_eq(&pos_ref, &positions[entity1.get_id()], "La référence renvoyée par add_component n'est pas correcte");
}

Test(RegistryTests, EmplaceComponent) {
    registry reg;

    auto &positions = reg.register_component<Position>();

    entity_t entity1 = reg.spawn_entity();

    auto &pos_ref = reg.emplace_component<Position>(entity1, 10.0f, 20.0f);

    const auto &pos1 = positions[entity1.get_id()];
    cr_assert_eq(10.0, pos1.x);
    cr_assert_eq(20.0, pos1.y);
    cr_assert_eq(&pos_ref, &positions[entity1.get_id()], "La référence renvoyée par emplace_component n'est pas correcte");
}

Test(RegistryTests, RemoveComponent) {
    registry reg;

    auto &positions = reg.register_component<Position>();

    entity_t entity1 = reg.spawn_entity();
    positions.insert_at(entity1.get_id(), {10.0f, 20.0f});

    const auto &pos1 = positions[entity1.get_id()];
    cr_assert_eq(10.0, pos1.x);
    cr_assert_eq(20.0, pos1.y);

    reg.remove_component<Position>(entity1);
    cr_assert_eq(positions.size(), 0, "Le composant n'a pas été supprimé correctement");
}

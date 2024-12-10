#include <criterion/criterion.h>
#include "Registry.hpp"
#include "Entity.hpp"
#include "position.hpp"
#include "size.hpp"
#include "velocity.hpp"
#include "idPlayer.hpp"
#include "controllable.hpp"
#include "attribute.hpp"
#include "system.hpp"

Test(ShootSystemTest, CreateShoot_Player) {
    registry reg;

    Entity player = reg.spawn_entity();
    reg.add_component<component::position>(player, {100, 100});
    reg.add_component<component::controllable>(player, {component::controllable::Shoot});
    reg.add_component<component::attribute>(player, {component::attribute::Player1});

    System sys;
    sys.shoot_system_player(reg);

    auto &positions = reg.get_components<component::position>();
    auto &velocities = reg.get_components<component::velocity>();
    auto &sizes = reg.get_components<component::size>();
    auto &idPlayers = reg.get_components<component::idPlayer>();
    auto &attributes = reg.get_components<component::attribute>();

    cr_assert_eq(positions.size(), 2, "Le nombre d'entités avec des positions devrait être 2.");
    cr_assert_eq(velocities.size(), 2, "Le nombre d'entités avec des vitesses devrait être 2.");
    cr_assert_eq(sizes.size(), 2, "Le nombre d'entités avec des tailles devrait être 2.");
    cr_assert_eq(idPlayers.size(), 2, "Le nombre d'entités avec des idPlayer devrait être 2.");
    cr_assert_eq(attributes.size(), 2, "Le nombre d'entités avec des attributs devrait être 2.");

    cr_assert_eq(attributes[1]._type, component::attribute::Shoot, "Le type d'attribut de l'entité 1 devrait être Shoot.");
    cr_assert_eq(positions[1].x, 100, "La position X du tir devrait être 100.");
    cr_assert_eq(positions[1].y, 100, "La position Y du tir devrait être 100.");
    cr_assert_eq(velocities[1].x, 10, "La vitesse X du tir devrait être 10.");
    cr_assert_eq(velocities[1].y, 0, "La vitesse Y du tir devrait être 0.");
    cr_assert_eq(sizes[1].x, 10, "La taille X du tir devrait être 10.");
    cr_assert_eq(sizes[1].y, 10, "La taille Y du tir devrait être 10.");
    cr_assert_eq(idPlayers[1].id, player.get_id(), "L'ID du joueur dans le tir devrait correspondre à l'ID du joueur.");
}

Test(ShootSystemTest, CreateShoot_Ennemy) {
    registry reg;

    Entity enemy = reg.spawn_entity();
    reg.add_component<component::position>(enemy, {200, 200});
    reg.add_component<component::attribute>(enemy, {component::attribute::Ennemies});

    System sys;
    sys.shoot_system_ennemies(reg);

    auto &positions = reg.get_components<component::position>();
    auto &velocities = reg.get_components<component::velocity>();
    auto &sizes = reg.get_components<component::size>();
    auto &idPlayers = reg.get_components<component::idPlayer>();
    auto &attributes = reg.get_components<component::attribute>();

    cr_assert_eq(positions.size(), 2, "Le nombre d'entités avec des positions devrait être 2.");
    cr_assert_eq(velocities.size(), 2, "Le nombre d'entités avec des vitesses devrait être 2.");
    cr_assert_eq(sizes.size(), 2, "Le nombre d'entités avec des tailles devrait être 2.");
    cr_assert_eq(idPlayers.size(), 2, "Le nombre d'entités avec des idPlayer devrait être 2.");
    cr_assert_eq(attributes.size(), 2, "Le nombre d'entités avec des attributs devrait être 2.");

    cr_assert_eq(attributes[1]._type, component::attribute::Shoot, "Le type d'attribut de l'entité 1 devrait être Shoot.");
    cr_assert_eq(positions[1].x, 200, "La position X du tir ennemi devrait être 200.");
    cr_assert_eq(positions[1].y, 200, "La position Y du tir ennemi devrait être 200.");
    cr_assert_eq(velocities[1].x, 10, "La vitesse X du tir ennemi devrait être 10.");
    cr_assert_eq(velocities[1].y, 0, "La vitesse Y du tir ennemi devrait être 0.");
    cr_assert_eq(sizes[1].x, -10, "La taille X du tir ennemi devrait être -10.");
    cr_assert_eq(sizes[1].y, 10, "La taille Y du tir ennemi devrait être 10.");
    cr_assert_eq(idPlayers[1].id, enemy.get_id(), "L'ID de l'ennemi dans le tir devrait correspondre à l'ID de l'ennemi.");
}

Test(ShootSystemTest, PlayerShootsWhenKeyPressed) {
    registry reg;

    Entity player = reg.spawn_entity();
    reg.add_component<component::position>(player, {150, 150});
    reg.add_component<component::controllable>(player, {component::controllable::Shoot});
    reg.add_component<component::attribute>(player, {component::attribute::Player1});

    System sys;
    sys.shoot_system_player(reg);

    auto &positions = reg.get_components<component::position>();
    cr_assert_eq(positions.size(), 2, "Le joueur et son tir doivent être créés.");
    cr_assert_eq(positions[1].x, 150, "La position X du tir devrait être 150.");
    cr_assert_eq(positions[1].y, 150, "La position Y du tir devrait être 150.");
}


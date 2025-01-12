#include <criterion/criterion.h>
#include "Registry.hpp"
#include "Entity.hpp"
#include "position.hpp"
#include "size.hpp"
#include "velocity.hpp"
#include "idPlayer.hpp"
#include "controllable.hpp"
#include "attribute.hpp"
#include "state.hpp"
#include "system.hpp"

Test(ShootSystemTest, CreateShoot_Player) {
    registry reg;

    Entity player = reg.spawn_entity();
    reg.add_component<component::position>(player, {100, 100});
    reg.add_component<component::controllable>(player, {component::controllable::Shoot});
    reg.add_component<component::attribute>(player, {component::attribute::Player1});
    reg.add_component<component::state>(player, {component::state::stateKey::Alive});

    System sys;
    sys.shoot_system_player(reg);

    auto &positions = reg.get_components<component::position>();
    auto &velocities = reg.get_components<component::velocity>();
    auto &sizes = reg.get_components<component::size>();
    auto &idPlayers = reg.get_components<component::idPlayer>();
    auto &attributes = reg.get_components<component::attribute>();

    cr_assert_eq(positions.size(), 2, "Le joueur et un tir doivent être présents.");
    cr_assert_eq(velocities[1].x, 10, "La vitesse X du tir du joueur devrait être 10.");
    cr_assert_eq(velocities[1].y, 0, "La vitesse Y du tir du joueur devrait être 0.");
    cr_assert_eq(sizes[1].x, 9, "La taille X du tir devrait être 9.");
    cr_assert_eq(sizes[1].y, 9, "La taille Y du tir devrait être 9.");
    cr_assert_eq(attributes[1]._type, component::attribute::Shoot, "L'attribut devrait être 'Shoot'.");
    cr_assert_eq(idPlayers[1].id, player.get_id(), "L'ID du joueur doit être correctement associé au tir.");
}

Test(ShootSystemTest, CreateShoot_Ennemy1) {
    registry reg;

    Entity enemy = reg.spawn_entity();
    reg.add_component<component::position>(enemy, {200, 200});
    reg.add_component<component::attribute>(enemy, {component::attribute::Ennemies});
    reg.add_component<component::state>(enemy, {component::state::stateKey::Alive});

    System sys;
    sys.shoot_system_ennemies(reg);

    auto &positions = reg.get_components<component::position>();
    auto &velocities = reg.get_components<component::velocity>();
    auto &sizes = reg.get_components<component::size>();
    auto &attributes = reg.get_components<component::attribute>();

    cr_assert_eq(positions[1].x, 200, "La position X du tir ennemi devrait être 200.");
    cr_assert_eq(velocities[1].x, -5, "La vitesse X du tir ennemi devrait être -5.");
    cr_assert_eq(attributes[1]._type, component::attribute::Shoot, "Le type d'attribut devrait être 'Shoot'.");
    cr_assert_eq(sizes[1].x, 9, "La taille X du tir ennemi devrait être 9.");
}

Test(ShootSystemTest, CreateShoot_Ennemy2) {
    registry reg;

    Entity enemy = reg.spawn_entity();
    reg.add_component<component::position>(enemy, {300, 300});
    reg.add_component<component::attribute>(enemy, {component::attribute::Ennemies2});
    reg.add_component<component::state>(enemy, {component::state::stateKey::Alive});

    System sys;
    sys.shoot_system_ennemies(reg);

    auto &velocities = reg.get_components<component::velocity>();
    cr_assert_eq(velocities[1].x, -25, "La vitesse X du tir ennemi2 devrait être -25.");
}

Test(ShootSystemTest, CreateShoot_Ennemy34) {
    registry reg;

    Entity enemy = reg.spawn_entity();
    reg.add_component<component::position>(enemy, {400, 400});
    reg.add_component<component::attribute>(enemy, {component::attribute::Ennemies3});
    reg.add_component<component::state>(enemy, {component::state::stateKey::Alive});

    System sys;
    sys.shoot_system_ennemies(reg);

    auto &sizes = reg.get_components<component::size>();
    cr_assert_eq(sizes[1].x, 11, "La taille X du tir ennemi3 devrait être 11.");
}

Test(ShootSystemTest, CreateShoot_Ennemy5) {
    registry reg;

    Entity enemy = reg.spawn_entity();
    reg.add_component<component::position>(enemy, {500, 500});
    reg.add_component<component::attribute>(enemy, {component::attribute::Ennemies5});
    reg.add_component<component::state>(enemy, {component::state::stateKey::Alive});

    System sys;
    sys.shoot_system_ennemies(reg);

    auto &velocities = reg.get_components<component::velocity>();
    auto &sizes = reg.get_components<component::size>();

    cr_assert_eq(velocities[1].x, -40, "La vitesse X du tir ennemi5 devrait être -40.");
    cr_assert_eq(sizes[1].x, 15, "La taille X du tir ennemi5 devrait être 15.");
    cr_assert_eq(sizes[1].y, 15, "La taille Y du tir ennemi5 devrait être 15.");
}

Test(ShootSystemTest, PlayerDoesNotShootWhenKeyNotPressed) {
    registry reg;

    Entity player = reg.spawn_entity();
    reg.add_component<component::position>(player, {150, 150});
    reg.add_component<component::controllable>(player, {component::controllable::NoKey});
    reg.add_component<component::state>(player, {component::state::stateKey::Alive});

    System sys;
    sys.shoot_system_player(reg);

    auto &positions = reg.get_components<component::position>();
    cr_assert_eq(positions.size(), 1, "Aucun tir ne doit être créé si la touche n'est pas pressée.");
}

Test(ShootSystemTest, EnnemyDoesNotShootWhenDead) {
    registry reg;

    Entity enemy = reg.spawn_entity();
    reg.add_component<component::position>(enemy, {250, 250});
    reg.add_component<component::attribute>(enemy, {component::attribute::Ennemies});
    reg.add_component<component::state>(enemy, {component::state::stateKey::Dead});

    System sys;
    sys.shoot_system_ennemies(reg);

    auto &positions = reg.get_components<component::position>();
    cr_assert_eq(positions.size(), 1, "Aucun tir ne doit être créé pour un ennemi mort.");
}

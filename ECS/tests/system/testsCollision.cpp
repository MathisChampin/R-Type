#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "Registry.hpp"
#include "position.hpp"
#include "size.hpp"
#include "attribute.hpp"
#include "system.hpp"

Test(collision_system, player_vs_enemy_collision)
{
    cr_redirect_stdout();

    registry reg;
    System sys;

    reg.register_component<component::position>();
    reg.register_component<component::size>();
    reg.register_component<component::attribute>();

    Entity player = reg.spawn_entity();
    Entity enemy = reg.spawn_entity();

    reg.add_component<component::position>(player, {10.0, 20.0});
    reg.add_component<component::size>(player, {5.0, 5.0});
    reg.add_component<component::attribute>(player, {component::attribute::Player});

    reg.add_component<component::position>(enemy, {12.0, 22.0});
    reg.add_component<component::size>(enemy, {5.0, 5.0});
    reg.add_component<component::attribute>(enemy, {component::attribute::Ennemies});

    sys.collision_system(reg);

    cr_assert_stdout_eq_str("Collision detected between entity 0 and entity 1\n");
}

Test(collision_system, no_collision)
{
    cr_redirect_stdout();

    registry reg;
    System sys;

    reg.register_component<component::position>();
    reg.register_component<component::size>();
    reg.register_component<component::attribute>();

    Entity player = reg.spawn_entity();
    Entity enemy = reg.spawn_entity();

    reg.add_component<component::position>(player, {10.0, 20.0});
    reg.add_component<component::size>(player, {5.0, 5.0});
    reg.add_component<component::attribute>(player, {component::attribute::Player});

    reg.add_component<component::position>(enemy, {30.0, 40.0}); // Pas de chevauchement
    reg.add_component<component::size>(enemy, {5.0, 5.0});
    reg.add_component<component::attribute>(enemy, {component::attribute::Ennemies});

    sys.collision_system(reg);

    cr_assert_stdout_eq_str("No collision find\n");
}

Test(collision_system, no_collision_same_type)
{
    cr_redirect_stdout();

    registry reg;
    System sys;

    reg.register_component<component::position>();
    reg.register_component<component::size>();
    reg.register_component<component::attribute>();

    Entity player = reg.spawn_entity();
    Entity player2 = reg.spawn_entity();

    reg.add_component<component::position>(player, {10.0, 20.0});
    reg.add_component<component::size>(player, {5.0, 5.0});
    reg.add_component<component::attribute>(player, {component::attribute::Player});

    reg.add_component<component::position>(player2, {30.0, 40.0});
    reg.add_component<component::size>(player2, {5.0, 5.0});
    reg.add_component<component::attribute>(player2, {component::attribute::Player});

    sys.collision_system(reg);

    cr_assert_stdout_eq_str("No collision beetween same type\n");
}

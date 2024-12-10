#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "Registry.hpp"
#include "score.hpp"
#include "level.hpp"
#include "system.hpp"

Test(level_system, test_level_1)
{
    cr_redirect_stdout();

    registry reg;
    System sys;

    reg.register_component<component::score>();
    auto &levels = reg.register_component<component::level>();

    Entity player = reg.spawn_entity();

    reg.add_component<component::score>(player, {100});
    reg.add_component<component::level>(player, {component::level::Level0});
    auto &level = levels[player.get_id()];

    sys.level_system(reg);

    cr_assert_eq(level._levelKey, 1, "Expected level to be 1, but got %d", level._levelKey);
}

Test(level_system, test_level_2)
{
    cr_redirect_stdout();

    registry reg;
    System sys;

    reg.register_component<component::score>();
    auto &levels = reg.register_component<component::level>();

    Entity player = reg.spawn_entity();

    reg.add_component<component::score>(player, {200});
    reg.add_component<component::level>(player, {component::level::Level0});
    auto &level = levels[player.get_id()];

    sys.level_system(reg);

    cr_assert_eq(level._levelKey, 2, "Expected level to be 2, but got %d", level._levelKey);
}

Test(level_system, test_level_3)
{
    cr_redirect_stdout();

    registry reg;
    System sys;

    reg.register_component<component::score>();
    auto &levels = reg.register_component<component::level>();

    Entity player = reg.spawn_entity();

    reg.add_component<component::score>(player, {300});
    reg.add_component<component::level>(player, {component::level::Level0});
    auto &level = levels[player.get_id()];

    sys.level_system(reg);

    cr_assert_eq(level._levelKey, 3, "Expected level to be 3, but got %d", level._levelKey);
}

Test(level_system, test_level_4)
{
    cr_redirect_stdout();

    registry reg;
    System sys;

    reg.register_component<component::score>();
    auto &levels = reg.register_component<component::level>();

    Entity player = reg.spawn_entity();

    reg.add_component<component::score>(player, {400});
    reg.add_component<component::level>(player, {component::level::Level0});
    auto &level = levels[player.get_id()];

    sys.level_system(reg);

    cr_assert_eq(level._levelKey, 4, "Expected level to be 4, but got %d", level._levelKey);
}

Test(level_system, test_level_5)
{
    cr_redirect_stdout();

    registry reg;
    System sys;

    reg.register_component<component::score>();
    auto &levels = reg.register_component<component::level>();

    Entity player = reg.spawn_entity();

    reg.add_component<component::score>(player, {500});
    reg.add_component<component::level>(player, {component::level::Level0});
    auto &level = levels[player.get_id()];

    sys.level_system(reg);

    cr_assert_eq(level._levelKey, 5, "Expected level to be 5, but got %d", level._levelKey);
}
#include <criterion/criterion.h>
#include "system.hpp"
#include "Registry.hpp"
#include "state.hpp"
#include "level.hpp"

Test(WinSystem, Level8WinState)
{
    registry reg;
    System sys;

    auto &states = reg.register_component<component::state>();
    reg.register_component<component::level>();

    Entity player = reg.spawn_entity();

    reg.add_component<component::state>(player, {component::state::stateKey::Alive});
    reg.add_component<component::level>(player, {component::level::Level7});
    sys.win_system(reg);

    const auto &player_state = states[player.get_id()];
    cr_assert_eq(player_state._stateKey, component::state::stateKey::Alive, 
                 "Expected player state to remain Alive, but got %d", player_state._stateKey);

    reg.add_component<component::level>(player, {component::level::Level8});
    sys.win_system(reg);

    const auto &updated_player_state = states[player.get_id()];
    cr_assert_eq(updated_player_state._stateKey, component::state::stateKey::Win, 
                 "Expected player state to be Win after reaching Level8, but got %d", updated_player_state._stateKey);
}

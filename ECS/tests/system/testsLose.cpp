#include <criterion/criterion.h>
#include "system.hpp"
#include "Registry.hpp"
#include "state.hpp"
#include "attribute.hpp"

Test(LoseSystem, PlayerDeadLoseState)
{
    registry reg;
    System sys;

    auto &states = reg.register_component<component::state>();
    reg.register_component<component::attribute>();

    Entity player = reg.spawn_entity();

    reg.add_component<component::state>(player, {component::state::stateKey::Alive});
    reg.add_component<component::attribute>(player, {component::attribute::Player1});

    sys.lose_system(reg);

    const auto &player_state = states[player.get_id()];
    cr_assert_eq(player_state._stateKey, component::state::stateKey::Alive, 
                 "Expected player state to remain Alive, but got %d", player_state._stateKey);

    reg.add_component<component::state>(player, {component::state::stateKey::Dead});

    sys.lose_system(reg);

    const auto &updated_player_state = states[player.get_id()];
    cr_assert_eq(updated_player_state._stateKey, component::state::stateKey::Lose, 
                 "Expected player state to be Lose after being Dead, but got %d", updated_player_state._stateKey);
}

Test(LoseSystem, NonPlayerEntitiesRemainAlive)
{
    registry reg;
    System sys;

    auto &states = reg.register_component<component::state>();
    reg.register_component<component::attribute>();

    Entity enemy = reg.spawn_entity();

    reg.add_component<component::state>(enemy, {component::state::stateKey::Dead});
    reg.add_component<component::attribute>(enemy, {component::attribute::Ennemies});

    sys.lose_system(reg);

    const auto &enemy_state = states[enemy.get_id()];
    cr_assert_eq(enemy_state._stateKey, component::state::stateKey::Dead, 
                 "Expected enemy state to remain Dead, but got %d", enemy_state._stateKey);
}

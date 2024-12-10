#include "attribute.hpp"
#include "controllable.hpp"
#include "level.hpp"
#include "life.hpp"
#include "position.hpp"
#include "score.hpp"
#include "size.hpp"
#include "state.hpp"
#include "velocity.hpp"
#include "system.hpp"
#include "Registry.hpp"

void System::player_system(registry &reg)
{
    Entity player = reg.spawn_entity();

    reg.add_component<component::attribute>(player, {component::attribute::Player});
    reg.add_component<component::controllable>(player, {component::controllable::NoKey});
    reg.add_component<component::level>(player, {component::level::Level0});
    reg.add_component<component::life>(player, {4});
    reg.add_component<component::position>(player, {50, 500});
    reg.add_component<component::score>(player, {0});
    reg.add_component<component::size>(player, {32, 14});
    reg.add_component<component::state>(player, {component::state::Alive});
    reg.add_component<component::velocity>(player, {0, 0});
}

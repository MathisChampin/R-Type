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

void System::registry_system(registry &reg)
{
    reg.register_component<component::attribute>();
    reg.register_component<component::controllable>();
    reg.register_component<component::level>();
    reg.register_component<component::life>();
    reg.register_component<component::position>();
    reg.register_component<component::score>();
    reg.register_component<component::size>();
    reg.register_component<component::state>();
    reg.register_component<component::velocity>();
}

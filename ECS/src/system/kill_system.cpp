#include "system.hpp"
#include "state.hpp"
#include "attribute.hpp"
#include "Registry.hpp"

void System::kill_system(registry &reg)
{
    auto &states = reg.get_components<component::state>();
    auto &attributes = reg.get_components<component::attribute>();

    for (size_t i = 0; i < states.size(); i++) {
        auto &state = states[i];
        auto &att = attributes[i];
        if (state._stateKey == component::state::stateKey::Dead && att._type == component::attribute::Shoot) {
            auto Entity = reg.get_entity(i);
            reg.kill_entity(Entity);
        }
    }
}

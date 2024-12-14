#include "system.hpp"
#include "state.hpp"
#include "Registry.hpp"

void System::kill_system(registry &reg)
{
    auto &states = reg.get_components<component::state>();

    for (size_t i = 0; i < states.size(); i++) {
        auto &state = states[i];
        if (state._stateKey == component::state::stateKey::Dead) {
            auto Entity = reg.get_entity(i);
            reg.kill_entity(Entity);
        }
    }
}

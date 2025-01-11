#include "state.hpp"
#include "level.hpp"
#include "Registry.hpp"
#include "system.hpp"

void System::win_system(registry &reg)
{
    auto &states = reg.get_components<component::state>();
    auto &levels = reg.get_components<component::level>();

    for (size_t i = 0; i < levels.size() && i < states.size(); ++i) {
        auto &l = levels[i];
        auto &s = states[i];
        if (l._levelKey == component::level::Level8)
            s._stateKey = component::state::Win;
    }
}

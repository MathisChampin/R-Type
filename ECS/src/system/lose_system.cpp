#include "state.hpp"
#include "attribute.hpp"
#include "Registry.hpp"
#include "system.hpp"

void System::lose_system(registry &reg)
{
    auto &states = reg.get_components<component::state>();
    auto &attributes = reg.get_components<component::attribute>();

    for (size_t i = 0; i < attributes.size() && i < states.size(); ++i) {
        auto &a = attributes[i];
        auto &s = states[i];
        if ((a._type == component::attribute::Player1 ||
        a._type == component::attribute::Player2 ||
        a._type == component::attribute::Player3 ||
        a._type == component::attribute::Player4) && s._stateKey == component::state::Dead)
            s._stateKey = component::state::Lose;
    }
}

#include "controllable.hpp"
#include "position.hpp"
#include "system.hpp"
#include <iostream>
#include <map>

void System::control_system(registry& reg)
{
    std::map<component::controllable::Key, std::pair<int, int>> inputs = {
        {component::controllable::Up, {0, -1}},
        {component::controllable::Down, {0, 1}},
        {component::controllable::Left, {-1, 0}},
        {component::controllable::Right, {1, 0}}
    };

    auto& positions = reg.get_components<component::position>();
    auto& controllables = reg.get_components<component::controllable>();

    for (size_t i = 0; i < positions.size() && i < controllables.size(); ++i) {
        auto &ctl = controllables[i];
        auto &pos = positions[i];
        pos.x += inputs[ctl.active_key].first;
        pos.y += inputs[ctl.active_key].second;
    }
}

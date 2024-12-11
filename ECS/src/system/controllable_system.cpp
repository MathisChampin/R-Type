#include "controllable.hpp"
#include "position.hpp"
#include "system.hpp"
#include <iostream>
#include <map>

void System::control_system(registry& reg)
{
    std::map<component::controllable::Key, std::pair<int, int>> inputs = {
        {component::controllable::Key::Up, {0, -10}},
        {component::controllable::Key::Down, {0, 10}},
        {component::controllable::Key::Left, {-10, 0}},
        {component::controllable::Key::Right, {10, 0}}
    };
    auto& positions = reg.get_components<component::position>();
    auto& controllables = reg.get_components<component::controllable>();

    for (size_t i = 0; i < controllables.size(); ++i) {
        auto &ctl = controllables[i];
        auto &pos = positions[i];
        pos.x += inputs[ctl.active_key].first;
        pos.y += inputs[ctl.active_key].second;
    }
}

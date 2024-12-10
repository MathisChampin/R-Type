#include "controllable.hpp"
#include "velocity.hpp"
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

    auto& velocities = reg.get_components<component::velocity>();
    auto& controllables = reg.get_components<component::controllable>();

    for (size_t i = 0; i < velocities.size() && i < controllables.size(); ++i) {
        auto &ctl = controllables[i];
        auto &vel = velocities[i];
        vel.x = inputs[ctl.active_key].first;
        vel.y = inputs[ctl.active_key].second;
        std::cout << "velx: " << vel.x << " vely: " << vel.y << std::endl;
    }
}

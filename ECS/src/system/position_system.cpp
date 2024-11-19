#include "position.hpp"
#include "velocity.hpp"
#include "system.hpp"
#include <iostream>

void System::position_system(registry &reg)
{
    auto& positions = reg.get_components<component::position>();
    auto& velocities = reg.get_components<component::velocity>();

    for (size_t i = 0; i < positions.size() && i < velocities.size(); i++) {        
        auto& pos = positions[i];
        const auto& vel = velocities[i];

        pos.x += vel.x;
        pos.y += vel.y;
    }
}


#include "controllable.hpp"
#include "position.hpp"
#include "system.hpp"
#include <iostream>
#include <map>

int check_position_x(int posx, int input)
{
    if (posx += input >= 1920)
        posx = 1920;
    else if (posx += input <= 0)
        posx = 0;
    else
        posx += input;
    return posx;
}

int check_position_y(int posy, int input)
{
    if (posy += input >= 1080)
        posy = 1080;
    else if (posy += input <= 0)
        posy = 0;
    else
        posy += input;   
    return posy;
}

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
        pos.x = check_position_x(pos.x, inputs[ctl.active_key].first);
        pos.y = check_position_y(pos.y, inputs[ctl.active_key].second);
    }
}

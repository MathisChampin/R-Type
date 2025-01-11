#include "controllable.hpp"
#include "position.hpp"
#include "system.hpp"
#include "attribute.hpp"
#include <iostream>
#include <map>

int check_position_x(int posx, int input)
{
    posx += input;
    if (posx >= 1870)
        posx = 1870;
    if (posx <= 30)
        posx = 30;
    return posx;
}

int check_position_y(int posy, int input)
{
    posy += input;
    if (posy >= 1030)
        posy = 1030;
    if (posy <= 20)
        posy = 20;
    return posy;
}

void System::control_system(registry& reg)
{
    std::map<component::controllable::Key, std::pair<int, int>> inputs = {
        {component::controllable::Key::Up, {0, -10}},
        {component::controllable::Key::Down, {0, 10}},
        {component::controllable::Key::Left, {-10, 0}},
        {component::controllable::Key::Right, {10, 0}},
    };

    auto &positions = reg.get_components<component::position>();
    auto &controllables = reg.get_components<component::controllable>();
    auto &attributes = reg.get_components<component::attribute>();

    for (size_t i = 0; i < attributes.size(); ++i) {
        if (attributes[i]._type == component::attribute::Player1 ||
            attributes[i]._type == component::attribute::Player2 ||
            attributes[i]._type == component::attribute::Player3 ||
            attributes[i]._type == component::attribute::Player4) {
            auto &ctl = controllables[i];
            auto &pos = positions[i];

            if (ctl.active_key == component::controllable::Shoot)
                shoot_system_player(reg);
            if (ctl.active_key == component::controllable::Key::Clear) {
               attributes[i]._type = component::attribute::Clear;
            }

            pos.x = check_position_x(pos.x, inputs[ctl.active_key].first);
            pos.y = check_position_y(pos.y, inputs[ctl.active_key].second);
        }
    }
}



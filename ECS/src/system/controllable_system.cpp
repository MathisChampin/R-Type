#include "controllable.hpp"
#include "position.hpp"
#include "system.hpp"
#include "attribute.hpp"
#include "velocity.hpp"

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

void move_player(component::controllable::Key key, int velx, int vely, int posx, int posy)
{
    if (key == component::controllable::Down)
        posy += vely;
    if (key == component::controllable::Up)
        posy -= vely;
    if (key == component::controllable::Left)
        posx -= velx;
    if (key == component::controllable::Right)
        posx -= velx;
}

void System::control_system_p1(registry& reg)
{
    auto &positions = reg.get_components<component::position>();
    auto &controllables = reg.get_components<component::controllable>();
    auto &attributes = reg.get_components<component::attribute>();
    auto &velocity = reg.get_components<component::velocity>();

    for (size_t i = 0; i < attributes.size(); ++i) {
        if (attributes[i]._type == component::attribute::Player1) {
            auto &ctl = controllables[i];
            auto &pos = positions[i];
            auto &vel = velocity[i];

            if (ctl.active_key == component::controllable::Shoot)
                shoot_system_player(reg);
            if (ctl.active_key == component::controllable::Key::Clear) {
               attributes[i]._type = component::attribute::Clear;
            }

            move_player(ctl.active_key, vel.x, vel.y, pos.x, pos.y);
        }
    }
}

void System::control_system_p2(registry& reg)
{
    auto &positions = reg.get_components<component::position>();
    auto &controllables = reg.get_components<component::controllable>();
    auto &attributes = reg.get_components<component::attribute>();
    auto &velocity = reg.get_components<component::velocity>();

    for (size_t i = 0; i < attributes.size(); ++i) {
        if (attributes[i]._type == component::attribute::Player2) {
            auto &ctl = controllables[i];
            auto &pos = positions[i];
            auto &vel = velocity[i];

            if (ctl.active_key == component::controllable::Shoot)
                shoot_system_player(reg);
            if (ctl.active_key == component::controllable::Key::Clear) {
               attributes[i]._type = component::attribute::Clear;
            }

            move_player(ctl.active_key, vel.x, vel.y, pos.x, pos.y);
        }
    }
}

void System::control_system_p3(registry& reg)
{
    auto &positions = reg.get_components<component::position>();
    auto &controllables = reg.get_components<component::controllable>();
    auto &attributes = reg.get_components<component::attribute>();
    auto &velocity = reg.get_components<component::velocity>();

    for (size_t i = 0; i < attributes.size(); ++i) {
        if (attributes[i]._type == component::attribute::Player3) {
            auto &ctl = controllables[i];
            auto &pos = positions[i];
            auto &vel = velocity[i];

            if (ctl.active_key == component::controllable::Shoot)
                shoot_system_player(reg);
            if (ctl.active_key == component::controllable::Key::Clear) {
               attributes[i]._type = component::attribute::Clear;
            }

            move_player(ctl.active_key, vel.x, vel.y, pos.x, pos.y);
        }
    }
}

void System::control_system_p4(registry& reg)
{
    auto &positions = reg.get_components<component::position>();
    auto &controllables = reg.get_components<component::controllable>();
    auto &attributes = reg.get_components<component::attribute>();
    auto &velocity = reg.get_components<component::velocity>();

    for (size_t i = 0; i < attributes.size(); ++i) {
        if (attributes[i]._type == component::attribute::Player4) {
            auto &ctl = controllables[i];
            auto &pos = positions[i];
            auto &vel = velocity[i];

            if (ctl.active_key == component::controllable::Shoot)
                shoot_system_player(reg);
            if (ctl.active_key == component::controllable::Key::Clear) {
               attributes[i]._type = component::attribute::Clear;
            }

            move_player(ctl.active_key, vel.x, vel.y, pos.x, pos.y);
        }
    }
}

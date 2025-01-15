#include "controllable.hpp"
#include "position.hpp"
#include "system.hpp"
#include "attribute.hpp"
#include "velocity.hpp"
#include "shoot_type.hpp"
#include "level.hpp"
#include <iostream>
#include <map>

int move_player_x(component::controllable::Key key, int velx, int posx)
{
    if (key == component::controllable::Left) {
        posx -= velx;
        if (posx <= -30)
            posx = 1870;
    }
    if (key == component::controllable::Right) {
        posx += velx;
        if (posx >= 1870)
            posx = -30;
    }
    return posx;
}

int move_player_y(component::controllable::Key key, int vely, int posy)
{
    if (key == component::controllable::Down) {
        posy += vely;
        if (posy >= 1100)
            posy = -30;
    }
    if (key == component::controllable::Up) {
        posy -= vely;
        if (posy <= -30)
            posy = 1100;
    }
    return posy;
}

void System::control_system_p1(registry& reg) {
    auto &positions = reg.get_components<component::position>();
    auto &controllables = reg.get_components<component::controllable>();
    auto &attributes = reg.get_components<component::attribute>();
    auto &velocity = reg.get_components<component::velocity>();
    auto &shootTypes = reg.get_components<component::shoot_type>();
    auto &level = reg.get_components<component::level>();

    for (size_t i = 0; i < attributes.size(); ++i) {
        if (attributes[i]._type == component::attribute::Player1) {
            auto &ctl = controllables[i];
            auto &pos = positions[i];
            auto &vel = velocity[i];
            auto &type = shootTypes[i];
            auto &lvl = level[i];

            if (lvl._levelKey >= component::level::Level6) {
                if (ctl.active_key == component::controllable::Shoot5)
                    type.value = component::attribute::Shoot6;
            }
            if (lvl._levelKey >= component::level::Level5) {
                if (ctl.active_key == component::controllable::Shoot4)
                    type.value = component::attribute::Shoot5;
            }
            if (lvl._levelKey >= component::level::Level4) {
                if (ctl.active_key == component::controllable::Shoot3)
                    type.value = component::attribute::Shoot4;
            }
            if (lvl._levelKey >= component::level::Level3) {
                if (ctl.active_key == component::controllable::Shoot2)
                    type.value = component::attribute::Shoot3;
            }

            if (lvl._levelKey >= component::level::Level0) {
                if (ctl.active_key == component::controllable::Shoot1)
                    type.value = component::attribute::Shoot;
            }
            if (ctl.active_key == component::controllable::Shoot) {
                if (type.value == component::attribute::Shoot6)
                    shoot_system_player_5(reg, i);
                if (type.value == component::attribute::Shoot)
                    shoot_system_player_1(reg, i);
                if (type.value == component::attribute::Shoot3)
                    shoot_system_player_2(reg, i); 
                if (type.value == component::attribute::Shoot4)
                    shoot_system_player_3(reg, i); 
                if (type.value == component::attribute::Shoot5)
                    shoot_system_player_4(reg, i);
            }
            pos.x = move_player_x(ctl.active_key, vel.x, pos.x);
            pos.y = move_player_y(ctl.active_key, vel.y, pos.y);
        }
    }
}


void System::control_system_p2(registry& reg)
{
    auto &positions = reg.get_components<component::position>();
    auto &controllables = reg.get_components<component::controllable>();
    auto &attributes = reg.get_components<component::attribute>();
    auto &velocity = reg.get_components<component::velocity>();
    auto &shootTypes = reg.get_components<component::shoot_type>();
    auto &level = reg.get_components<component::level>();

    for (size_t i = 0; i < attributes.size(); ++i) {
        if (attributes[i]._type == component::attribute::Player2) {
            auto &ctl = controllables[i];
            auto &pos = positions[i];
            auto &vel = velocity[i];
            auto &type = shootTypes[i];
            auto &lvl = level[i]; 

            if (lvl._levelKey >= component::level::Level6) {
                if (ctl.active_key == component::controllable::Shoot5)
                    type.value = component::attribute::Shoot6;
            }
            if (lvl._levelKey >= component::level::Level5) {
                if (ctl.active_key == component::controllable::Shoot5)
                    type.value = component::attribute::Shoot5;
            }
            if (lvl._levelKey >= component::level::Level4) {
                if (ctl.active_key == component::controllable::Shoot4)
                    type.value = component::attribute::Shoot4;
            }
            if (lvl._levelKey >= component::level::Level3) {
                if (ctl.active_key == component::controllable::Shoot3)
                    type.value = component::attribute::Shoot3;
            }

            if (lvl._levelKey >= component::level::Level0) {
                if (ctl.active_key == component::controllable::Shoot)
                    type.value = component::attribute::Shoot;
            }
            if (ctl.active_key == component::controllable::Shoot) {
                if (type.value == component::attribute::Shoot6)
                    shoot_system_player_5(reg, i);
                if (type.value == component::attribute::Shoot)
                    shoot_system_player_1(reg, i);  
                if (type.value == component::attribute::Shoot3)
                    shoot_system_player_2(reg, i); 
                if (type.value == component::attribute::Shoot4)
                    shoot_system_player_3(reg, i); 
                if (type.value == component::attribute::Shoot5)
                    shoot_system_player_4(reg, i);
            }
            if (ctl.active_key == component::controllable::Key::Clear) {
                attributes[i]._type = component::attribute::Clear;
            }
            pos.x = move_player_x(ctl.active_key, vel.x, pos.x);
            pos.y = move_player_y(ctl.active_key, vel.y, pos.y);
        }
    }
}

void System::control_system_p3(registry& reg)
{
    auto &positions = reg.get_components<component::position>();
    auto &controllables = reg.get_components<component::controllable>();
    auto &attributes = reg.get_components<component::attribute>();
    auto &velocity = reg.get_components<component::velocity>();
    auto &shootTypes = reg.get_components<component::shoot_type>();
    auto &level = reg.get_components<component::level>();

    for (size_t i = 0; i < attributes.size(); ++i) {
        if (attributes[i]._type == component::attribute::Player3) {
            auto &ctl = controllables[i];
            auto &pos = positions[i];
            auto &vel = velocity[i];
            auto &type = shootTypes[i];
            auto &lvl = level[i]; 

            if (lvl._levelKey >= component::level::Level6) {
                if (ctl.active_key == component::controllable::Shoot5)
                    type.value = component::attribute::Shoot6;
            }
            if (lvl._levelKey >= component::level::Level5) {
                if (ctl.active_key == component::controllable::Shoot5)
                    type.value = component::attribute::Shoot5;
            }
            if (lvl._levelKey >= component::level::Level4) {
                if (ctl.active_key == component::controllable::Shoot4)
                    type.value = component::attribute::Shoot4;
            }
            if (lvl._levelKey >= component::level::Level3) {
                if (ctl.active_key == component::controllable::Shoot3)
                    type.value = component::attribute::Shoot3;
            }

            if (lvl._levelKey >= component::level::Level0) {
                if (ctl.active_key == component::controllable::Shoot)
                    type.value = component::attribute::Shoot;
            }
            if (ctl.active_key == component::controllable::Shoot) {
                if (type.value == component::attribute::Shoot6)
                    shoot_system_player_5(reg, i);
                if (type.value == component::attribute::Shoot)
                    shoot_system_player_1(reg, i);  
                if (type.value == component::attribute::Shoot3)
                    shoot_system_player_2(reg, i); 
                if (type.value == component::attribute::Shoot4)
                    shoot_system_player_3(reg, i); 
                if (type.value == component::attribute::Shoot5)
                    shoot_system_player_4(reg, i);
            }
            if (ctl.active_key == component::controllable::Key::Clear) {
                attributes[i]._type = component::attribute::Clear;
            }
            pos.x = move_player_x(ctl.active_key, vel.x, pos.x);
            pos.y = move_player_y(ctl.active_key, vel.y, pos.y);
        }
    }
}

void System::control_system_p4(registry& reg)
{
    auto &positions = reg.get_components<component::position>();
    auto &controllables = reg.get_components<component::controllable>();
    auto &attributes = reg.get_components<component::attribute>();
    auto &velocity = reg.get_components<component::velocity>();
    auto &shootTypes = reg.get_components<component::shoot_type>();
    auto &level = reg.get_components<component::level>();

    for (size_t i = 0; i < attributes.size(); ++i) {
        if (attributes[i]._type == component::attribute::Player4) {
            auto &ctl = controllables[i];
            auto &pos = positions[i];
            auto &vel = velocity[i];
            auto &type = shootTypes[i];
            auto &lvl = level[i]; 

            if (lvl._levelKey >= component::level::Level6) {
                if (ctl.active_key == component::controllable::Shoot5)
                    type.value = component::attribute::Shoot6;
            }
            if (lvl._levelKey >= component::level::Level5) {
                if (ctl.active_key == component::controllable::Shoot5)
                    type.value = component::attribute::Shoot5;
            }
            if (lvl._levelKey >= component::level::Level4) {
                if (ctl.active_key == component::controllable::Shoot4)
                    type.value = component::attribute::Shoot4;
            }
            if (lvl._levelKey >= component::level::Level3) {
                if (ctl.active_key == component::controllable::Shoot3)
                    type.value = component::attribute::Shoot3;
            }

            if (lvl._levelKey >= component::level::Level0) {
                if (ctl.active_key == component::controllable::Shoot)
                    type.value = component::attribute::Shoot;
            }
            if (ctl.active_key == component::controllable::Shoot) {
                if (type.value == component::attribute::Shoot6)
                    shoot_system_player_5(reg, i);
                if (type.value == component::attribute::Shoot)
                    shoot_system_player_1(reg, i);  
                if (type.value == component::attribute::Shoot3)
                    shoot_system_player_2(reg, i); 
                if (type.value == component::attribute::Shoot4)
                    shoot_system_player_3(reg, i); 
                if (type.value == component::attribute::Shoot5)
                    shoot_system_player_4(reg, i);
            }
            if (ctl.active_key == component::controllable::Key::Clear) {
                attributes[i]._type = component::attribute::Clear;
            }
            pos.x = move_player_x(ctl.active_key, vel.x, pos.x);
            pos.y = move_player_y(ctl.active_key, vel.y, pos.y);
        }
    }
}

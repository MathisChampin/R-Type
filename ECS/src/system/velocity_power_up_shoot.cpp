#include "system.hpp"
#include "attribute.hpp"
#include "idPlayer.hpp"
#include "velocity.hpp"

void System::update_shoot_velocity_p1(registry &reg)
{
    auto &velocity = reg.get_components<component::velocity>();
    auto &attributes = reg.get_components<component::attribute>();
    auto &id_player = reg.get_components<component::idPlayer>();

    for (size_t i = 0; i < attributes.size(); i++) {
        if (attributes[i]._type == component::attribute::Player1) {
            for (size_t j = 0; j < attributes.size(); j++) {
                if (attributes[j]._type == component::attribute::Shoot && id_player[j].id == i) {
                    velocity[j].x += 5;
                    velocity[j].y += 5;
                }
            }
        }
    }
}

void System::update_shoot_velocity_p2(registry &reg)
{
    auto &velocity = reg.get_components<component::velocity>();
    auto &attributes = reg.get_components<component::attribute>();
    auto &id_player = reg.get_components<component::idPlayer>();

    for (size_t i = 0; i < attributes.size(); i++) {
        if (attributes[i]._type == component::attribute::Player2) {
            for (size_t j = 0; j < attributes.size(); j++) {
                if (attributes[j]._type == component::attribute::Shoot && id_player[j].id == i) {
                    velocity[j].x += 5;
                    velocity[j].y += 5;
                }
            }
        }
    }
}

void System::update_shoot_velocity_p3(registry &reg)
{
    auto &velocity = reg.get_components<component::velocity>();
    auto &attributes = reg.get_components<component::attribute>();
    auto &id_player = reg.get_components<component::idPlayer>();

    for (size_t i = 0; i < attributes.size(); i++) {
        if (attributes[i]._type == component::attribute::Player3) {
            for (size_t j = 0; j < attributes.size(); j++) {
                if (attributes[j]._type == component::attribute::Shoot && id_player[j].id == i) {
                    velocity[j].x += 5;
                    velocity[j].y += 5;
                }
            }
        }
    }
}

void System::update_shoot_velocity_p4(registry &reg)
{
    auto &velocity = reg.get_components<component::velocity>();
    auto &attributes = reg.get_components<component::attribute>();
    auto &id_player = reg.get_components<component::idPlayer>();

    for (size_t i = 0; i < attributes.size(); i++) {
        if (attributes[i]._type == component::attribute::Player4) {
            for (size_t j = 0; j < attributes.size(); j++) {
                if (attributes[j]._type == component::attribute::Shoot && id_player[j].id == i) {
                    velocity[j].x += 5;
                    velocity[j].y += 5;
                }
            }
        }
    }
}
void System::reset_shoot_velocity_p1(registry &reg)
{
    auto &velocity = reg.get_components<component::velocity>();
    auto &attributes = reg.get_components<component::attribute>();
    auto &id_player = reg.get_components<component::idPlayer>();

    for (size_t i = 0; i < attributes.size(); i++) {
        if (attributes[i]._type == component::attribute::Player1) {
            for (size_t j = 0; j < attributes.size(); j++) {
                if (attributes[j]._type == component::attribute::Shoot && id_player[j].id == i) {
                    velocity[j].x -= 5;
                    velocity[j].y -= 5;
                }
            }
        }
    }
}

void System::reset_shoot_velocity_p2(registry &reg)
{
    auto &velocity = reg.get_components<component::velocity>();
    auto &attributes = reg.get_components<component::attribute>();
    auto &id_player = reg.get_components<component::idPlayer>();

    for (size_t i = 0; i < attributes.size(); i++) {
        if (attributes[i]._type == component::attribute::Player2) {
            for (size_t j = 0; j < attributes.size(); j++) {
                if (attributes[j]._type == component::attribute::Shoot && id_player[j].id == i) {
                    velocity[j].x -= 5;
                    velocity[j].y -= 5;
                }
            }
        }
    }
}

void System::reset_shoot_velocity_p3(registry &reg)
{
    auto &velocity = reg.get_components<component::velocity>();
    auto &attributes = reg.get_components<component::attribute>();
    auto &id_player = reg.get_components<component::idPlayer>();

    for (size_t i = 0; i < attributes.size(); i++) {
        if (attributes[i]._type == component::attribute::Player3) {
            for (size_t j = 0; j < attributes.size(); j++) {
                if (attributes[j]._type == component::attribute::Shoot && id_player[j].id == i) {
                    velocity[j].x -= 5;
                    velocity[j].y -= 5;
                }
            }
        }
    }
}

void System::reset_shoot_velocity_p4(registry &reg)
{
    auto &velocity = reg.get_components<component::velocity>();
    auto &attributes = reg.get_components<component::attribute>();
    auto &id_player = reg.get_components<component::idPlayer>();

    for (size_t i = 0; i < attributes.size(); i++) {
        if (attributes[i]._type == component::attribute::Player4) {
            for (size_t j = 0; j < attributes.size(); j++) {
                if (attributes[j]._type == component::attribute::Shoot && id_player[j].id == i) {
                    velocity[j].x -= 5;
                    velocity[j].y -= 5;
                }
            }
        }
    }
}
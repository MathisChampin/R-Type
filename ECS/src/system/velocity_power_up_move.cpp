#include "system.hpp"
#include "velocity.hpp"
#include "attribute.hpp"

void System::power_up_velocity_p1(registry &reg)
{
    auto &velocity = reg.get_components<component::velocity>();
    auto &attributes = reg.get_components<component::attribute>();

    for (size_t i = 0; i < attributes.size(); i++) {
        if (attributes[i]._type == component::attribute::Player1) {
            velocity[i].x += 15;
            velocity[i].y += 15;
        }
    }
}

void System::power_up_velocity_p2(registry &reg)
{
    auto &velocity = reg.get_components<component::velocity>();
    auto &attributes = reg.get_components<component::attribute>();

    for (size_t i = 0; i < attributes.size(); i++) {
        if (attributes[i]._type == component::attribute::Player2) {
            velocity[i].x += 15;
            velocity[i].y += 15;
        }
    }
}

void System::power_up_velocity_p3(registry &reg)
{
    auto &velocity = reg.get_components<component::velocity>();
    auto &attributes = reg.get_components<component::attribute>();

    for (size_t i = 0; i < attributes.size(); i++) {
        if (attributes[i]._type == component::attribute::Player3) {
            velocity[i].x += 15;
            velocity[i].y += 15;
        }
    }
}

void System::power_up_velocity_p4(registry &reg)
{
    auto &velocity = reg.get_components<component::velocity>();
    auto &attributes = reg.get_components<component::attribute>();

    for (size_t i = 0; i < attributes.size(); i++) {
        if (attributes[i]._type == component::attribute::Player4) {
            velocity[i].x += 15;
            velocity[i].y += 15;
        }
    }
}

void System::reset_velocity_p1(registry &reg)
{
    auto &velocity = reg.get_components<component::velocity>();
    auto &attributes = reg.get_components<component::attribute>();

    for (size_t i = 0; i < attributes.size(); i++) {
        if (attributes[i]._type == component::attribute::Player1) {
            velocity[i].x -= 15;
            velocity[i].y -= 15;
        }
    }
}

void System::reset_velocity_p2(registry &reg)
{
    auto &velocity = reg.get_components<component::velocity>();
    auto &attributes = reg.get_components<component::attribute>();

    for (size_t i = 0; i < attributes.size(); i++) {
        if (attributes[i]._type == component::attribute::Player2) {
            velocity[i].x -= 15;
            velocity[i].y -= 15;
        }
    }
}

void System::reset_velocity_p3(registry &reg)
{
    auto &velocity = reg.get_components<component::velocity>();
    auto &attributes = reg.get_components<component::attribute>();

    for (size_t i = 0; i < attributes.size(); i++) {
        if (attributes[i]._type == component::attribute::Player3) {
            velocity[i].x -= 15;
            velocity[i].y -= 15;
        }
    }
}

void System::reset_velocity_p4(registry &reg)
{
    auto &velocity = reg.get_components<component::velocity>();
    auto &attributes = reg.get_components<component::attribute>();

    for (size_t i = 0; i < attributes.size(); i++) {
        if (attributes[i]._type == component::attribute::Player4) {
            velocity[i].x -= 15;
            velocity[i].y -= 15;
        }
    }
}
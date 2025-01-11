#include "position.hpp"
#include "size.hpp"
#include "system.hpp"
#include "attribute.hpp"
#include "life.hpp"
#include "state.hpp"
#include "score.hpp"
#include "idPlayer.hpp"
#include "velocity.hpp"
#include <iostream>

bool check_collision_power_up_shoot(sparse_array<component::position> &positions,
    sparse_array<component::size> &sizes,
    size_t entity1,
    size_t entity2)
{
    auto &pos1 = positions[entity1];
    auto &size1 = sizes[entity1];
    auto &pos2 = positions[entity2];
    auto &size2 = sizes[entity2];

    bool collision_x = (pos1.x < pos2.x + size2.x) && (pos1.x + size1.x > pos2.x);
    bool collision_y = (pos1.y < pos2.y + size2.y) && (pos1.y + size1.y > pos2.y);

    return collision_x && collision_y;
}

bool Is_player(const component::attribute &attribute)
{
    switch (attribute._type) {
        case component::attribute::Player1:
        case component::attribute::Player2:
        case component::attribute::Player3:
        case component::attribute::Player4:
            return true;
        default:
            return false;
    }
}

bool is_powerup_shoot(const component::attribute &attribute)
{
    return attribute._type == component::attribute::PowerUpShoot;
}

bool System::collision_power_up_shoot(registry &reg)
{
    auto &positions = reg.get_components<component::position>();
    auto &sizes = reg.get_components<component::size>();
    auto &attributes = reg.get_components<component::attribute>();
    auto &states = reg.get_components<component::state>();

    for (size_t i = 0; i < attributes.size(); i++) {
        if (!Is_player(attributes[i]))
            continue;

        for (size_t j = 0; j < attributes.size(); j++) {
            if (!is_powerup_shoot(attributes[j]))
                continue;

            if (check_collision_power_up_shoot(positions, sizes, i, j)) {
                states[j]._stateKey = component::state::Dead;
                return true;
            }
        }
    }
    return false;
}

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
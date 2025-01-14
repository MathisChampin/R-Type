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
#include <chrono>

bool check_collision_power_up(sparse_array<component::position> &positions,
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

void restore_life(sparse_array<component::attribute> &att, registry &reg, size_t i, sparse_array<component::life> &life)
{
    System sys;

    if (life[i].life < 3) {
        if (att[i]._type == component::attribute::Player1)
            sys.power_up_life_p1(reg);
        if (att[i]._type == component::attribute::Player2)
            sys.power_up_life_p2(reg);
        if (att[i]._type == component::attribute::Player3)
            sys.power_up_life_p3(reg);
        if (att[i]._type == component::attribute::Player4)
            sys.power_up_life_p4(reg);    
    }
}

void use_power_up_move(sparse_array<component::attribute> &att, registry &reg, size_t i)
{
    System sys;
    static std::unordered_map<size_t, std::chrono::steady_clock::time_point> playerPowerUpTimers;
    auto currentTime = std::chrono::steady_clock::now();

    if (playerPowerUpTimers.find(i) == playerPowerUpTimers.end()) {
        if (att[i]._type == component::attribute::Player1)
            sys.power_up_velocity_p1(reg);
        if (att[i]._type == component::attribute::Player2)
            sys.power_up_velocity_p2(reg);
        if (att[i]._type == component::attribute::Player3)
            sys.power_up_velocity_p3(reg);
        if (att[i]._type == component::attribute::Player4)
            sys.power_up_velocity_p4(reg);
        playerPowerUpTimers[i] = currentTime;
    }

    if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - playerPowerUpTimers[i]).count() >= 5) {
        if (att[i]._type == component::attribute::Player1)
            sys.reset_velocity_p1(reg);
        if (att[i]._type == component::attribute::Player2)
            sys.reset_velocity_p2(reg);
        if (att[i]._type == component::attribute::Player3)
            sys.reset_velocity_p3(reg);
        if (att[i]._type == component::attribute::Player4)
            sys.reset_velocity_p4(reg);
        playerPowerUpTimers.erase(i);
    }
}

void use_power_up_shoot(sparse_array<component::attribute> &att, registry &reg, size_t i)
{
    System sys;
    static std::unordered_map<size_t, std::chrono::steady_clock::time_point> playerPowerUpTimers;
    auto currentTime = std::chrono::steady_clock::now();

    if (playerPowerUpTimers.find(i) == playerPowerUpTimers.end()) {
        if (att[i]._type == component::attribute::Player1)
            sys.update_shoot_velocity_p1(reg);
        if (att[i]._type == component::attribute::Player2)
            sys.update_shoot_velocity_p2(reg);
        if (att[i]._type == component::attribute::Player3)
            sys.update_shoot_velocity_p3(reg);
        if (att[i]._type == component::attribute::Player4)
            sys.update_shoot_velocity_p4(reg);
        playerPowerUpTimers[i] = currentTime;
    }

    if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - playerPowerUpTimers[i]).count() >= 5) {
        if (att[i]._type == component::attribute::Player1)
            sys.reset_shoot_velocity_p1(reg);
        if (att[i]._type == component::attribute::Player2)
            sys.reset_shoot_velocity_p2(reg);
        if (att[i]._type == component::attribute::Player3)
            sys.reset_shoot_velocity_p3(reg);
        if (att[i]._type == component::attribute::Player4)
            sys.reset_shoot_velocity_p4(reg);
        playerPowerUpTimers.erase(i);
    }
}

bool is_Player(const component::attribute &attribute)
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

bool is_powerup(const component::attribute &attribute)
{
    if (attribute._type == component::attribute::PowerUpMove ||
    attribute._type == component::attribute::PowerUpShoot ||
    attribute._type == component::attribute::PowerUpLife)
        return true;
    return false;
}

void System::collision_power_up(registry &reg)
{
    auto &positions = reg.get_components<component::position>();
    auto &sizes = reg.get_components<component::size>();
    auto &attributes = reg.get_components<component::attribute>();
    auto &states = reg.get_components<component::state>();
    auto &life = reg.get_components<component::life>();

    for (size_t i = 0; i < attributes.size(); i++) {
        if (!is_Player(attributes[i]))
            continue;

        for (size_t j = 0; j < attributes.size(); j++) {
            if (!is_powerup(attributes[j]))
                continue;

            if (check_collision_power_up(positions, sizes, i, j)) {
                if (attributes[j]._type == component::attribute::PowerUpLife && states[j]._stateKey == component::state::Alive)
                    restore_life(attributes, reg, i, life);
                //if (attributes[j]._type == component::attribute::PowerUpMove)
                //    use_power_up_move(attributes, reg, i);
                //if (attributes[j]._type == component::attribute::PowerUpShoot)
                //    use_power_up_shoot(attributes, reg, i);
                states[j]._stateKey = component::state::Dead;
            }
        }
    }
}

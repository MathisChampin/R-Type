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

void handle_power_up_player1(size_t i, sparse_array<component::attribute> &attributes,
    registry &reg, std::unordered_map<size_t, std::chrono::steady_clock::time_point> &activePowerUps,
    std::chrono::steady_clock::time_point currentTime)
{
    System sys;

    if (attributes[i]._type == component::attribute::Player1) {
        if (activePowerUps.find(i) == activePowerUps.end()) {
            sys.power_up_velocity_p1(reg);
            activePowerUps[i] = currentTime;
        }
    }
}

void handle_power_up_player2(size_t i, sparse_array<component::attribute> &attributes,
    registry &reg, std::unordered_map<size_t, std::chrono::steady_clock::time_point> &activePowerUps,
    std::chrono::steady_clock::time_point currentTime)
{
    System sys;

    if (attributes[i]._type == component::attribute::Player2) {
        if (activePowerUps.find(i) == activePowerUps.end()) {
            sys.power_up_velocity_p2(reg);
            activePowerUps[i] = currentTime;
        }
    }
}

void handle_power_up_player3(size_t i, sparse_array<component::attribute> &attributes,
    registry &reg, std::unordered_map<size_t, std::chrono::steady_clock::time_point> &activePowerUps,
    std::chrono::steady_clock::time_point currentTime)
{
    System sys;

    if (attributes[i]._type == component::attribute::Player3) {
        if (activePowerUps.find(i) == activePowerUps.end()) {
            sys.power_up_velocity_p3(reg);
            activePowerUps[i] = currentTime;
        }
    }
}

void handle_power_up_player4(size_t i, sparse_array<component::attribute> &attributes,
    registry &reg, std::unordered_map<size_t, std::chrono::steady_clock::time_point> &activePowerUps,
    std::chrono::steady_clock::time_point currentTime)
{
    System sys;

    if (attributes[i]._type == component::attribute::Player4) {
        if (activePowerUps.find(i) == activePowerUps.end()) {
            sys.power_up_velocity_p4(reg);
            activePowerUps[i] = currentTime;
        }
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
    static std::unordered_map<size_t, std::chrono::steady_clock::time_point> activePowerUps;
    auto currentTime = std::chrono::steady_clock::now();

    // Reset expired power-ups
    for (auto it = activePowerUps.begin(); it != activePowerUps.end();) {
        if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - it->second).count() >= 5) {
            switch (attributes[it->first]._type) {
                case component::attribute::Player1:
                    System().reset_velocity_p1(reg);
                    break;
                case component::attribute::Player2:
                    System().reset_velocity_p2(reg);
                    break;
                case component::attribute::Player3:
                    System().reset_velocity_p3(reg);
                    break;
                case component::attribute::Player4:
                    System().reset_velocity_p4(reg);
                    break;
                default:
                    break;
            }
            it = activePowerUps.erase(it);
        } else {
            ++it;
        }
    }

    for (size_t i = 0; i < attributes.size(); i++) {
        if (!is_Player(attributes[i]))
            continue;

        for (size_t j = 0; j < attributes.size(); j++) {
            if (!is_powerup(attributes[j]))
                continue;

            if (check_collision_power_up(positions, sizes, i, j)) {
                if (attributes[j]._type == component::attribute::PowerUpLife && states[j]._stateKey == component::state::Alive) {
                    if (attributes[i]._type == component::attribute::Player1) {
                        if (life[i].life < 3)
                            power_up_life_p1(reg);
                    } else if (attributes[i]._type == component::attribute::Player2) {
                        if (life[i].life < 3)
                            power_up_life_p2(reg);
                    } else if (attributes[i]._type == component::attribute::Player3) {
                        if (life[i].life < 3)
                            power_up_life_p3(reg);
                    } else if (attributes[i]._type == component::attribute::Player4) {
                        if (life[i].life < 3)
                            power_up_life_p4(reg);
                    }
                }

                if (attributes[j]._type == component::attribute::PowerUpMove && states[j]._stateKey == component::state::Alive) {
                    if (attributes[i]._type == component::attribute::Player1) {
                        handle_power_up_player1(i, attributes, reg, activePowerUps, currentTime);
                    } else if (attributes[i]._type == component::attribute::Player2) {
                        handle_power_up_player2(i, attributes, reg, activePowerUps, currentTime);
                    } else if (attributes[i]._type == component::attribute::Player3) {
                        handle_power_up_player3(i, attributes, reg, activePowerUps, currentTime);
                    } else if (attributes[i]._type == component::attribute::Player4) {
                        handle_power_up_player4(i, attributes, reg, activePowerUps, currentTime);
                    }
                }

                states[j]._stateKey = component::state::Dead;
            }
        }
    }
}

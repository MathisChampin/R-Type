#include "position.hpp"
#include "velocity.hpp"
#include "system.hpp"
#include "attribute.hpp"
#include "state.hpp"

void position_ennemies(
    sparse_array<component::position> &positions,
    sparse_array<component::attribute> &attributes,
    sparse_array<component::velocity> &velocities,
    int i
)
{
    auto &pos = positions[i];
    auto &vel = velocities[i];
    const auto &att = attributes[i];

    switch (att._type) {
        case component::attribute::Ennemies:
            pos.x += vel.x;
            if (pos.x <= -10) {
                pos.x = 1960;
            }
            break;
        case component::attribute::Ennemies2:
            pos.y += vel.y;
            if (pos.y <= 0) {
                vel.y = std::abs(vel.y);
            }
            if (pos.y >= 1080)
                vel.y = -std::abs(vel.y);
            break;
        case component::attribute::Ennemies3:
            pos.x += vel.x;
            pos.y += vel.y;

            if (pos.y >= 1080) {
                vel.y = -std::abs(vel.y);
            } else if (pos.y <= 0) {
                vel.y = std::abs(vel.y);
            }
            if (pos.x <= 0) {
                pos.x = 1960;
            }
            break;
        case component::attribute::Ennemies4:
            pos.x += vel.x;
            pos.y += vel.y;

            if (pos.y <= -40) {
                pos.y = 1090;
            }
            if (pos.x <= -10) {
                pos.x = 1960;
            }
            break;
        default:
            break;
    }
}

void position_shoot(
    sparse_array<component::position> &positions,
    sparse_array<component::attribute> &attributes,
    sparse_array<component::velocity> &velocities,
    sparse_array<component::state> &states,
    int i
)
{
    auto &pos = positions[i];
    auto &vel = velocities[i];
    const auto &att = attributes[i];
    auto &s = states[i];

    switch (att._type) {
        case component::attribute::Shoot:
        case component::attribute::Shoot1:
        case component::attribute::Shoot2:
            pos.x += vel.x;
            if (pos.x <= -30 || pos.x >= 1930) {
                s._stateKey = component::state::Dead;
            }
            break;

        case component::attribute::Shoot3:
        case component::attribute::Shoot7:
            pos.x += vel.x;
            pos.y += vel.y;
            if (pos.y <= 0) {
                if (pos.y <= 0) {
                    pos.y = 0;
                    vel.y = std::abs(vel.y);
                }
            }
            break;
            if (pos.x <= -30 || pos.x >= 1930) {
                s._stateKey = component::state::Dead;
            }
            break;
        case component::attribute::Shoot4:
        case component::attribute::Shoot8:
            pos.x += vel.x;
            pos.y += vel.y;
            if (pos.y >= 900) {
                pos.y = 900;
                vel.y = -std::abs(vel.y);
            }
            break;
            if (pos.x <= -30 || pos.x >= 1930) {
                s._stateKey = component::state::Dead;
            }
            break;
        case component::attribute::Shoot5:
        case component::attribute::Shoot9:
            pos.x += vel.x;
            pos.y += vel.y;
            if (pos.y <= 0) {
                if (pos.y <= 0) {
                    pos.y = 0;
                    vel.y = std::abs(vel.y);
                }
            }
            if (pos.y >= 900) {
                pos.y = 900;
                vel.y = -std::abs(vel.y);
            }
            if (pos.x <= -30 || pos.x >= 1930) {
                s._stateKey = component::state::Dead;
            }
            break;
            if (pos.x <= -30 || pos.x >= 1930) {
                s._stateKey = component::state::Dead;
            }
            break;
        case component::attribute::Shoot6:
        case component::attribute::Shoot10:
            pos.x += vel.x;
            pos.y += vel.y;
            if (pos.y <= 0) {
                    pos.y = 0;
                    vel.y = std::abs(vel.y);
            }
            if (pos.y >= 900) {
                pos.y = 900;
                vel.y = -std::abs(vel.y);
            }
            if (pos.x <= 0) {
                    pos.x = 0;
                    vel.x = std::abs(vel.y);
            }
            if (pos.x >= 1800) {
                pos.x = 1800;
                vel.x = -std::abs(vel.y);
                }
            break;
            if (pos.x <= -30 || pos.x >= 1930) {
                s._stateKey = component::state::Dead;
            }
            break;
        default:
            break;
    }
}


void System::position_system(registry &reg)
{
    auto &positions = reg.get_components<component::position>();
    auto &velocities = reg.get_components<component::velocity>();
    auto &attributes = reg.get_components<component::attribute>();
    auto &states = reg.get_components<component::state>();

    for (size_t i = 0; i < positions.size() && i < velocities.size() && i < attributes.size(); i++) {        
        position_ennemies(positions, attributes, velocities, i);
        position_shoot(positions, attributes, velocities, states, i);
    }
}

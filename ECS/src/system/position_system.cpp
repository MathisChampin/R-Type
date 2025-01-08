#include "position.hpp"
#include "velocity.hpp"
#include "system.hpp"
#include "attribute.hpp"

void position_ennemies(
    sparse_array<component::position> &positions,
    sparse_array<component::attribute> &attributes,
    sparse_array<component::velocity> &velocities,
    int i,
    registry &reg
)
{
    auto &pos = positions[i];
    auto &vel = velocities[i];
    const auto &att = attributes[i];
    switch (att._type) {
        case component::attribute::Ennemies:
            pos.x += vel.x;
            if (pos.x <= 0) {
                reg.kill_entity(reg.get_entity(i));
            }
            break;
        case component::attribute::Ennemies2:
            pos.y += vel.y;
            if (pos.y <= 0 || pos.y >= 1080) {
                reg.kill_entity(reg.get_entity(i));
            }
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
                reg.kill_entity(reg.get_entity(i));
            }
            break;
        case component::attribute::Ennemies4:
            pos.x += vel.x;
            pos.y += vel.y;

            if (pos.y <= 0) {
                vel.y = std::abs(vel.y);
            } else if (pos.y >= 1080) {
                vel.y = -std::abs(vel.y);
            }
            if (pos.x <= 0) {
                reg.kill_entity(reg.get_entity(i));
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
    int i,
    registry &reg
)
{
    auto &pos = positions[i];
    auto &vel = velocities[i];
    const auto &att = attributes[i];

    switch (att._type) {
        case component::attribute::Shoot:
        case component::attribute::Shoot2:
            pos.x += vel.x;
            if (pos.x <= -30 || pos.x >= 1930) {
                reg.kill_entity(reg.get_entity(i));
            }
            break;

        case component::attribute::Shoot3:
        case component::attribute::Shoot5:
            if (pos.y + vel.y <= 0) {
                pos.y = 0;
                vel.y = std::abs(vel.y);
            } else if (pos.y + vel.y >= 1080) {
                pos.y = 1080;
                vel.y = -std::abs(vel.y);
            }
            pos.x += vel.x;
            pos.y += vel.y;
            if (pos.x <= -30 || pos.x >= 1930) {
                reg.kill_entity(reg.get_entity(i));
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

    for (size_t i = 0; i < positions.size() && i < velocities.size() && i < attributes.size(); i++) {        
        position_ennemies(positions, attributes, velocities, i, reg);
        position_shoot(positions, attributes, velocities, i, reg);
    }
}

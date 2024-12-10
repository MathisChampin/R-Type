#include "position.hpp"
#include "velocity.hpp"
#include "system.hpp"
#include "attribute.hpp"

void position_player(
    sparse_array<component::position> &positions,
    sparse_array<component::attribute> &attributes,
    sparse_array<component::velocity> &velocities,
    int i
)
{
    auto &pos = positions[i];
    const auto &vel = velocities[i];
    const auto &att = attributes[i];

    if (att._type == component::attribute::Player) {
        pos.x += vel.x;
        pos.y += vel.y;
    }
}

void position_ennemies(
    sparse_array<component::position> &positions,
    sparse_array<component::attribute> &attributes,
    sparse_array<component::velocity> &velocities,
    int i
)
{
    auto &pos = positions[i];
    const auto &vel = velocities[i];
    const auto &att = attributes[i];

    if (att._type == component::attribute::Ennemies) {
        pos.x += vel.x;
    }
}

void position_shoot(
    sparse_array<component::position> &positions,
    sparse_array<component::attribute> &attributes,
    sparse_array<component::velocity> &velocities,
    int i
)
{
    auto &pos = positions[i];
    const auto &vel = velocities[i];
    const auto &att = attributes[i];

    if (att._type == component::attribute::Shoot) {
        pos.x += vel.x;
    }
}

void System::position_system(registry &reg)
{
    auto &positions = reg.get_components<component::position>();
    auto &velocities = reg.get_components<component::velocity>();
    auto &attributes = reg.get_components<component::attribute>();

    for (size_t i = 0; i < positions.size() && i < velocities.size() && i < attributes.size(); i++) {        
        position_player(positions, attributes, velocities, i);
        position_ennemies(positions, attributes, velocities, i);
        position_shoot(positions, attributes, velocities, i);
    }
}
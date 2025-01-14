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


bool System::collision_power_up(registry &reg)
{
    auto &positions = reg.get_components<component::position>();
    auto &sizes = reg.get_components<component::size>();
    auto &attributes = reg.get_components<component::attribute>();
    auto &states = reg.get_components<component::state>();

    for (size_t i = 0; i < attributes.size(); i++) {
        if (!is_Player(attributes[i]))
            continue;

        for (size_t j = 0; j < attributes.size(); j++) {
            if (!is_powerup(attributes[j]))
                continue;

            if (check_collision_power_up(positions, sizes, i, j)) {
                states[j]._stateKey = component::state::Dead;
                return true;
            }
        }
    }
    return false;
}

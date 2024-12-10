#include "position.hpp"
#include "size.hpp"
#include "system.hpp"
#include "attribute.hpp"
#include "life.hpp"
#include "state.hpp"
#include "score.hpp"

#include <iostream>

void decrease_life(int id, registry reg)
{
    auto &lifes = reg.get_components<component::life>();
    auto &states = reg.get_components<component::state>();

    auto &life = lifes[id];
    auto &state = states[id];

    life.life--;
    if (life.life <= 0)
        state._stateKey = component::state::Dead;
}

void increase_score(int id, registry reg)
{
    auto &scores = reg.get_components<component::score>();

    auto &score = scores[id];

    score.score+=5;
}

void check_collision(
    sparse_array<component::position> &positions,
    sparse_array<component::size> &sizes,
    int i, int j
    )
{
    const auto &pos1 = positions[i];
    const auto &pos2 = positions[j];
    const auto &size1 = sizes[i];
    const auto &size2 = sizes[j];
    if (pos1.x < pos2.x + size2.x && pos1.x + size1.x > pos2.x &&
        pos1.y < pos2.y + size2.y && pos1.y + size1.y > pos2.y) {
        std::cout << "Collision detected between entity " << i 
                  << " and entity " << j << std::endl;
    } else {
        std::cout << "No collision find" << std::endl;
    }
}

void System::collision_system(registry &reg)
{
    auto &attributes = reg.get_components<component::attribute>();
    auto &positions = reg.get_components<component::position>();
    auto &sizes = reg.get_components<component::size>();

    for (size_t i = 0; i < attributes.size(); ++i) {
        for (size_t j = i + 1; j < attributes.size(); ++j) {
            const auto &attr1 = attributes[i];
            const auto &attr2 = attributes[j];
            if ((attr1._type == component::attribute::Player && attr2._type == component::attribute::Ennemies) ||
                (attr1._type == component::attribute::Ennemies && attr2._type == component::attribute::Player)) {
                    check_collision(positions, sizes, i, j);
            } else {
                std::cout << "No collision beetween same type" << std::endl;
            }
        }
    }
}

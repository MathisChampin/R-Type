#include "position.hpp"
#include "size.hpp"
#include "system.hpp"
#include "attribute.hpp"
#include "life.hpp"
#include "state.hpp"
#include "score.hpp"
#include "idPlayer.hpp"

#include <iostream>

bool check_collision(sparse_array<component::position> &positions,
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

bool is_player(const component::attribute& attribute)
{
    if (attribute._type == component::attribute::Player1 ||
        attribute._type == component::attribute::Player2 ||
        attribute._type == component::attribute::Player3 ||
        attribute._type == component::attribute::Player4)
            return true;
    return false;
}

void handle_collision_with_player(size_t j, sparse_array<component::life>& lifes)
{
    auto &life = lifes[j];
    if (life.life > 0) {
        life.life -= 1;
    }
}

void handle_collision_with_enemy(size_t shoot_id, sparse_array<component::score>& scores)
{
    auto &score = scores[shoot_id];
    score.score += 10;
}

bool should_check_collision(size_t j, const sparse_array<component::attribute>& attributes, const component::idPlayer& shoot_id)
{
    if ((attributes[j]._type == component::attribute::Player1 ||
        attributes[j]._type == component::attribute::Player2 ||
        attributes[j]._type == component::attribute::Player3 ||
        attributes[j]._type == component::attribute::Player4 ||
        attributes[j]._type == component::attribute::Ennemies) && shoot_id.id != j)
            return true;
    return false;
}

void System::collision_system(registry &reg)
{
    auto &positions = reg.get_components<component::position>();
    auto &sizes = reg.get_components<component::size>();
    auto &lifes = reg.get_components<component::life>();
    auto &scores = reg.get_components<component::score>();
    auto &attributes = reg.get_components<component::attribute>();
    auto &idPlayers = reg.get_components<component::idPlayer>();

    for (size_t i = 0; i < attributes.size(); i++) {
        if (attributes[i]._type == component::attribute::Shoot) {
            auto &shoot_id = idPlayers[i];
            for (size_t j = 0; j < attributes.size(); j++) {
                if (should_check_collision(j, attributes, shoot_id)) {
                    if (check_collision(positions, sizes, i, j)) {
                        if (is_player(attributes[j])) {
                            handle_collision_with_player(j, lifes);
                        } else if (attributes[j]._type == component::attribute::Ennemies) {
                            handle_collision_with_enemy(shoot_id.id, scores);
                        }
                    }
                }
            }
        }
    }
}
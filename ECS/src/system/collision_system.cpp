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

void handle_collision_with_player(size_t i, size_t j, size_t shoot_id,
    sparse_array<component::life> &lifes,
    sparse_array<component::state> &states)
{
    auto &life = lifes[j];
    auto &state = states[j];
    auto &state_shoot = states[i];
    auto &state_ennemy = states[shoot_id];

    if (state_ennemy._stateKey == component::state::stateKey::Alive) {
        if (life.life > 0) {
            life.life -= 1;
        }
        if (life.life <= 0) {
            state._stateKey = component::state::stateKey::Dead;
        }
        state_ennemy._stateKey = component::state::stateKey::Dead;
    } else
        state_shoot._stateKey = component::state::stateKey::Dead;
}

void handle_collision_with_enemy(size_t i, size_t shoot_id, size_t idEnnemy,
    sparse_array<component::score> &scores,
    sparse_array<component::state> &states)
{
    std:: cout << "COLLISION WITH ENNEMY" << "\n\n";
    auto &score = scores[shoot_id];
    auto &state = states[idEnnemy];
    auto &state_shoot = states[i];
    auto &state_player = states[shoot_id];
    if (state_player._stateKey == component::state::stateKey::Alive) {
        score.score += 10;
        state._stateKey = component::state::stateKey::Dead;
        state_shoot._stateKey = component::state::stateKey::Dead;
        std::cout << "ennemy with id = " << idEnnemy << " is dead" << std::endl;
        std::cout << "shoot with id = " << i << " is dead" << std::endl;

    }
    else
        state_shoot._stateKey = component::state::stateKey::Dead;

}

bool should_check_collision(size_t j,
    const sparse_array<component::attribute> &attributes,
    const component::idPlayer &shoot_id)
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
    auto &states = reg.get_components<component::state>();
    auto &idPlayers = reg.get_components<component::idPlayer>();

    for (size_t i = 0; i < attributes.size(); i++) {
        if (attributes[i]._type != component::attribute::Shoot) continue;

        auto &shoot_id = idPlayers[i];

        for (size_t j = 0; j < attributes.size(); j++) {
            if (!should_check_collision(j, attributes, shoot_id)) continue;

            if (!check_collision(positions, sizes, i, j)) continue;

            // Traiter les collisions selon le type de l'entité touchée
            if (is_player(attributes[j])) {
                handle_collision_with_player(i, j, shoot_id.id, lifes, states);
            } else if (attributes[j]._type == component::attribute::Ennemies) {
                handle_collision_with_enemy(i, shoot_id.id, j, scores, states);
            }
        }
    }
}

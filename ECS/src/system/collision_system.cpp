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

bool is_player(const component::attribute &attribute)
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

bool is_enemy(const component::attribute &attribute)
{
    switch (attribute._type) {
        case component::attribute::Ennemies5:
        case component::attribute::Ennemies4:
        case component::attribute::Ennemies3:
        case component::attribute::Ennemies2:
        case component::attribute::Ennemies:
            return true;
        default:
            return false;
    }
}

void handle_collision_with_player(size_t i, size_t shoot_id, size_t j,
    sparse_array<component::life> &lifes,
    sparse_array<component::state> &states,
    const sparse_array<component::attribute> &attributes,
    registry &reg)
{
    auto &life = lifes[j];
    auto &state = states[j];
    auto &state_shoot = states[i];
    Entity tmp = reg.get_entity(shoot_id);

    if (is_player(attributes[tmp.get_id()]))
        return;
    if (attributes[i]._type == component::attribute::Shoot5) {
        if (state._stateKey == component::state::stateKey::Alive && state_shoot._stateKey == component::state::Alive) {
            life.life -= 2;

            if (life.life <= 0) {
                state._stateKey = component::state::stateKey::Dead;
            }
        }
        state_shoot._stateKey = component::state::stateKey::Dead;
    } else {
        if (state._stateKey == component::state::stateKey::Alive && state_shoot._stateKey == component::state::Alive) {
            life.life -= 1;
            if (life.life <= 0) {
                state._stateKey = component::state::stateKey::Dead;
            }
            state_shoot._stateKey = component::state::stateKey::Dead;
        } else {
            state_shoot._stateKey = component::state::stateKey::Dead;
        }
    }
}

void handle_collision_with_enemy(size_t i, size_t shoot_id, size_t idEnnemy,
    sparse_array<component::score> &scores,
    sparse_array<component::state> &states,
    const sparse_array<component::attribute> &attributes,
    registry &reg)
{
    Entity tmp = reg.get_entity(shoot_id);
    auto &score = scores[shoot_id];
    auto &state = states[idEnnemy];
    auto &state_shoot = states[i];
    if (is_enemy(attributes[tmp.get_id()]))
        return;
    if (state._stateKey == component::state::stateKey::Alive && state_shoot._stateKey == component::state::Alive) {
        int score_increment = 0;

        switch (attributes[idEnnemy]._type) {
            case component::attribute::Ennemies2:
                score_increment = 100;
                break;
            case component::attribute::Ennemies:
                score_increment = 100;
                break;
            case component::attribute::Ennemies3:
                score_increment = 100;
                break;
            case component::attribute::Ennemies4:
                score_increment = 100;
                break;
            case component::attribute::Ennemies5:
                score_increment = 100;
                break;
            default:
                break;
        }

        score.score += score_increment;

        state._stateKey = component::state::stateKey::Dead;
        state_shoot._stateKey = component::state::stateKey::Dead;

        std::cout << "Enemy with id = " << idEnnemy << " is dead" << std::endl;
        std::cout << "Shoot with id = " << i << " is dead" << std::endl;
        std::cout << "Score incremented by " << score_increment << " points" << std::endl;
    } else {
        state_shoot._stateKey = component::state::stateKey::Dead;
    }
}

bool should_check_collision(size_t j,
    const sparse_array<component::attribute> &attributes,
    const component::idPlayer &shoot_id)
{
    const auto &attr = attributes[j];
    if ((attr._type == component::attribute::Player1 ||
        attr._type == component::attribute::Player2 ||
        attr._type == component::attribute::Player3 ||
        attr._type == component::attribute::Player4 ||
        attr._type == component::attribute::Ennemies ||
        attr._type == component::attribute::Ennemies2 ||
        attr._type == component::attribute::Ennemies3 ||
        attr._type == component::attribute::Ennemies4 ||
        attr._type == component::attribute::Ennemies5) && shoot_id.id != j) {
        return true;
    }
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
        if (attributes[i]._type != component::attribute::Shoot &&
        attributes[i]._type != component::attribute::Shoot2 &&
        attributes[i]._type != component::attribute::Shoot3 &&
        attributes[i]._type != component::attribute::Shoot5 &&
        attributes[i]._type != component::attribute::Shoot6 && 
        attributes[i]._type != component::attribute::Shoot7 &&
        attributes[i]._type != component::attribute::Shoot8 &&
        attributes[i]._type != component::attribute::Shoot9 &&
        attributes[i]._type != component::attribute::Shoot10 &&
        attributes[i]._type != component::attribute::Shoot1)
            continue;
        auto &shoot_id = idPlayers[i];
        for (size_t j = 0; j < attributes.size(); j++) {
            if (!should_check_collision(j, attributes, shoot_id))
                continue;
            if (!check_collision(positions, sizes, i, j))
                continue;
            if (is_player(attributes[j])) {
                handle_collision_with_player(i, shoot_id.id, j, lifes, states, attributes, reg);
            } else if (is_enemy(attributes[j])) {
                        handle_collision_with_enemy(i, shoot_id.id, j, scores, states, attributes, reg);
            }
        }
    }
}

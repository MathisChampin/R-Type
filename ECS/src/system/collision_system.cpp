#include "position.hpp"
#include "size.hpp"
#include "system.hpp"
#include "attribute.hpp"
#include "life.hpp"
#include "state.hpp"
#include "score.hpp"
#include "idPlayer.hpp"

#include <iostream>


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

bool check_collision_boss(sparse_array<component::position> &positions,
    sparse_array<component::size> &sizes,
    sparse_array<component::attribute> &attributes,
    size_t entity1,
    size_t entity2)
{
    auto &pos1 = positions[entity1];
    auto &size1 = sizes[entity1];
    auto &pos2 = positions[entity2];
    auto &size2 = sizes[entity2];

    const float enemy5_zone_x_min = 700.0f;
    const float enemy5_zone_x_max = 800.0f;
    const float enemy5_zone_y_min = 500.0f;
    const float enemy5_zone_y_max = 900.0f;
    bool collision_x = false;
    bool collision_y = false;

    if (attributes[entity1]._type == component::attribute::Ennemies5) {
        if (pos1.x >= enemy5_zone_x_min && pos1.x + size1.x <= enemy5_zone_x_max &&
            pos1.y >= enemy5_zone_y_min && pos1.y + size1.y <= enemy5_zone_y_max) {
            
            collision_x = (pos1.x < pos2.x + size2.x) && (pos1.x + size1.x > pos2.x);
            collision_y = (pos1.y < pos2.y + size2.y) && (pos1.y + size1.y > pos2.y);
        }
    } 
    if (attributes[entity2]._type == component::attribute::Ennemies5) {
        if (pos2.x >= enemy5_zone_x_min && pos2.x + size2.x <= enemy5_zone_x_max &&
            pos2.y >= enemy5_zone_y_min && pos2.y + size2.y <= enemy5_zone_y_max) {
            
            collision_x = (pos2.x < pos1.x + size1.x) && (pos2.x + size2.x > pos1.x);
            collision_y = (pos2.y < pos1.y + size1.y) && (pos2.y + size2.y > pos1.y);
        }
    }
    return collision_x && collision_y;
}

bool check_collision(sparse_array<component::position> &positions,
    sparse_array<component::size> &sizes,
    sparse_array<component::attribute> &attributes,
    size_t entity1,
    size_t entity2)
{
    auto &pos1 = positions[entity1];
    auto &size1 = sizes[entity1];
    auto &pos2 = positions[entity2];
    auto &size2 = sizes[entity2];

    if (is_enemy(attributes[entity1])) {
        size1.x = size1.x;
        size1.y = size1.y;
    }
    if (is_enemy(attributes[entity2])) {
        size2.x = size2.x;
        size2.y = size2.y;
    }

    bool collision_x = (pos1.x < pos2.x + size2.x) && (pos1.x + size1.x > pos2.x);

    bool collision_y = (pos1.y < pos2.y + size2.y) && (pos1.y + size1.y > pos2.y);

    return collision_x && collision_y;
}

void handle_collision_with_player1(size_t i, size_t shoot_id, size_t j,
    sparse_array<component::life> &lifes,
    sparse_array<component::state> &states,
    sparse_array<component::attribute> &attributes,
    registry &reg)
{
    auto &life = lifes[j];
    auto &state = states[j];
    auto &state_shoot = states[i];
    Entity tmp = reg.get_entity(shoot_id);

    if (attributes[tmp.get_id()]._type == component::attribute::Player3 ||
    attributes[tmp.get_id()]._type == component::attribute::Player4 ||
    attributes[tmp.get_id()]._type == component::attribute::Player2)
        return;

    if (attributes[i]._type == component::attribute::Shoot5) {
        if (state._stateKey == component::state::stateKey::Alive && state_shoot._stateKey == component::state::Alive) {
            life.life -= 2;
            if (life.life <= 0) {
                attributes[i]._type = component::attribute::Clear;
                state._stateKey = component::state::Dead;
            }
        }
        state_shoot._stateKey = component::state::stateKey::Dead;
    } else {
        if (state._stateKey == component::state::stateKey::Alive && state_shoot._stateKey == component::state::Alive) {
            life.life -= 1;
            if (life.life <= 0) {
                state._stateKey = component::state::stateKey::Dead;
            }
        }
        state_shoot._stateKey = component::state::stateKey::Dead;
    }
}

void handle_collision_with_player2(size_t i, size_t shoot_id, size_t j,
    sparse_array<component::life> &lifes,
    sparse_array<component::state> &states,
    sparse_array<component::attribute> &attributes,
    registry &reg)
{
    auto &life = lifes[j];
    auto &state = states[j];
    auto &state_shoot = states[i];
    Entity tmp = reg.get_entity(shoot_id);

    if (attributes[tmp.get_id()]._type == component::attribute::Player3 ||
    attributes[tmp.get_id()]._type == component::attribute::Player1 ||
    attributes[tmp.get_id()]._type == component::attribute::Player4)
        return;

    if (attributes[i]._type == component::attribute::Shoot5) {
        if (state._stateKey == component::state::stateKey::Alive && state_shoot._stateKey == component::state::Alive) {
            life.life -= 2;
            if (life.life <= 0) {
                attributes[i]._type = component::attribute::Clear;
                state._stateKey = component::state::Dead;
            }
        }
        state_shoot._stateKey = component::state::stateKey::Dead;
    } else {
        if (state._stateKey == component::state::stateKey::Alive && state_shoot._stateKey == component::state::Alive) {
            life.life -= 1;
            if (life.life <= 0) {
                state._stateKey = component::state::stateKey::Dead;
            }
        }
        state_shoot._stateKey = component::state::stateKey::Dead;
    }
}

void handle_collision_with_player3(size_t i, size_t shoot_id, size_t j,
    sparse_array<component::life> &lifes,
    sparse_array<component::state> &states,
    sparse_array<component::attribute> &attributes,
    registry &reg)
{
    auto &life = lifes[j];
    auto &state = states[j];
    auto &state_shoot = states[i];
    Entity tmp = reg.get_entity(shoot_id);

    if (attributes[tmp.get_id()]._type == component::attribute::Player4 ||
    attributes[tmp.get_id()]._type == component::attribute::Player1 ||
    attributes[tmp.get_id()]._type == component::attribute::Player2)
        return;

    if (attributes[i]._type == component::attribute::Shoot5) {
        if (state._stateKey == component::state::stateKey::Alive && state_shoot._stateKey == component::state::Alive) {
            life.life -= 2;
            if (life.life <= 0) {
                attributes[i]._type = component::attribute::Clear;
                state._stateKey = component::state::Dead;
            }
        }
        state_shoot._stateKey = component::state::stateKey::Dead;
    } else {
        if (state._stateKey == component::state::stateKey::Alive && state_shoot._stateKey == component::state::Alive) {
            life.life -= 1;
            if (life.life <= 0) {
                state._stateKey = component::state::stateKey::Dead;
            }
        }
        state_shoot._stateKey = component::state::stateKey::Dead;
    }
}

void handle_collision_with_player4(size_t i, size_t shoot_id, size_t j,
    sparse_array<component::life> &lifes,
    sparse_array<component::state> &states,
    sparse_array<component::attribute> &attributes,
    registry &reg)
{
    auto &life = lifes[j];
    auto &state = states[j];
    auto &state_shoot = states[i];
    Entity tmp = reg.get_entity(shoot_id);

    if (attributes[tmp.get_id()]._type == component::attribute::Player3 ||
    attributes[tmp.get_id()]._type == component::attribute::Player1 ||
    attributes[tmp.get_id()]._type == component::attribute::Player2)
        return;

    if (attributes[i]._type == component::attribute::Shoot5) {
        if (state._stateKey == component::state::stateKey::Alive && state_shoot._stateKey == component::state::Alive) {
            life.life -= 2;
            if (life.life <= 0) {
                attributes[i]._type = component::attribute::Clear;
                state._stateKey = component::state::Dead;
            }
        }
        state_shoot._stateKey = component::state::stateKey::Dead;
    } else {
        if (state._stateKey == component::state::stateKey::Alive && state_shoot._stateKey == component::state::Alive) {
            life.life -= 1;
            if (life.life <= 0) {
                state._stateKey = component::state::stateKey::Dead;
            }
        }
        state_shoot._stateKey = component::state::stateKey::Dead;
    }
}

void handle_collision_with_fire_player1(size_t i, size_t j,
    sparse_array<component::life> &lifes,
    sparse_array<component::state> &states,
    sparse_array<component::attribute> &attributes)
{
    auto &life = lifes[j];
    auto &state = states[j];
    auto &state_shoot = states[i];

    if (attributes[i]._type == component::attribute::Shoot5) {
        if (state._stateKey == component::state::stateKey::Alive && state_shoot._stateKey == component::state::Alive) {
            life.life -= 2;
            if (life.life <= 0) {
                attributes[i]._type = component::attribute::Clear;
                state._stateKey = component::state::Dead;
            }
        }
        state_shoot._stateKey = component::state::stateKey::Dead;
    } else {
        if (state._stateKey == component::state::stateKey::Alive && state_shoot._stateKey == component::state::Alive) {
            life.life -= 1;
            if (life.life <= 0) {
                state._stateKey = component::state::stateKey::Dead;
            }
        }
        state_shoot._stateKey = component::state::stateKey::Dead;
    }
}

void handle_collision_with_fire_player2(size_t i, size_t j,
    sparse_array<component::life> &lifes,
    sparse_array<component::state> &states,
    sparse_array<component::attribute> &attributes)
{
    auto &life = lifes[j];
    auto &state = states[j];
    auto &state_shoot = states[i];

    if (attributes[i]._type == component::attribute::Shoot5) {
        if (state._stateKey == component::state::stateKey::Alive && state_shoot._stateKey == component::state::Alive) {
            life.life -= 2;
            if (life.life <= 0) {
                attributes[i]._type = component::attribute::Clear;
                state._stateKey = component::state::Dead;
            }
        }
        state_shoot._stateKey = component::state::stateKey::Dead;
    } else {
        if (state._stateKey == component::state::stateKey::Alive && state_shoot._stateKey == component::state::Alive) {
            life.life -= 1;
            if (life.life <= 0) {
                state._stateKey = component::state::stateKey::Dead;
            }
        }
        state_shoot._stateKey = component::state::stateKey::Dead;
    }
}

void handle_collision_with_fire_player3(size_t i, size_t j,
    sparse_array<component::life> &lifes,
    sparse_array<component::state> &states,
    sparse_array<component::attribute> &attributes)
{
    auto &life = lifes[j];
    auto &state = states[j];
    auto &state_shoot = states[i];

    if (attributes[i]._type == component::attribute::Shoot5) {
        if (state._stateKey == component::state::stateKey::Alive && state_shoot._stateKey == component::state::Alive) {
            life.life -= 2;
            if (life.life <= 0) {
                attributes[i]._type = component::attribute::Clear;
                state._stateKey = component::state::Dead;
            }
        }
        state_shoot._stateKey = component::state::stateKey::Dead;
    } else {
        if (state._stateKey == component::state::stateKey::Alive && state_shoot._stateKey == component::state::Alive) {
            life.life -= 1;
            if (life.life <= 0) {
                state._stateKey = component::state::stateKey::Dead;
            }
        }
        state_shoot._stateKey = component::state::stateKey::Dead;
    }
}

void handle_collision_with_fire_player4(size_t i, size_t j,
    sparse_array<component::life> &lifes,
    sparse_array<component::state> &states,
    sparse_array<component::attribute> &attributes)
{
    auto &life = lifes[j];
    auto &state = states[j];
    auto &state_shoot = states[i];

    if (attributes[i]._type == component::attribute::Shoot5) {
        if (state._stateKey == component::state::stateKey::Alive && state_shoot._stateKey == component::state::Alive) {
            life.life -= 2;
            if (life.life <= 0) {
                attributes[i]._type = component::attribute::Clear;
                state._stateKey = component::state::Dead;
            }
        }
        state_shoot._stateKey = component::state::stateKey::Dead;
    } else {
        if (state._stateKey == component::state::stateKey::Alive && state_shoot._stateKey == component::state::Alive) {
            life.life -= 1;
            if (life.life <= 0) {
                state._stateKey = component::state::stateKey::Dead;
            }
        }
        state_shoot._stateKey = component::state::stateKey::Dead;
    }
}

void handle_collision_with_enemy(size_t i, size_t shoot_id, size_t idEnnemy,
    sparse_array<component::score> &scores,
    sparse_array<component::state> &states,
    sparse_array<component::life> &life,
    const sparse_array<component::attribute> &attributes,
    registry &reg)
{
    Entity tmp = reg.get_entity(shoot_id);
    auto &score = scores[shoot_id];
    auto &state = states[idEnnemy];
    auto &state_shoot = states[i];
    auto &lifes = life[idEnnemy];

    if (is_enemy(attributes[tmp.get_id()]))
        return;
    if (state._stateKey == component::state::stateKey::Alive && state_shoot._stateKey == component::state::Alive) {
        int score_increment = 0;

        switch (attributes[idEnnemy]._type) {
            case component::attribute::Ennemies2:
                score_increment = 10;
                break;
            case component::attribute::Ennemies:
                score_increment = 20;
                break;
            case component::attribute::Ennemies3:
                score_increment = 30;
                break;
            case component::attribute::Ennemies4:
                score_increment = 40;
                break;
            case component::attribute::Ennemies5:
                score_increment = 50;
                break;
            default:
                break;
        }

        score.score += score_increment;
        lifes.life -= 1;
        if (lifes.life <= 0)
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
    const sparse_array<component::state> &states,
    const component::idPlayer &shoot_id)
{
    const auto &attr = attributes[j];
    const auto &state = states[j];
 
    if ((attr._type == component::attribute::Player1 ||
        attr._type == component::attribute::Player2 ||
        attr._type == component::attribute::Player3 ||
        attr._type == component::attribute::Player4 ||
        attr._type == component::attribute::Ennemies ||
        attr._type == component::attribute::Ennemies2 ||
        attr._type == component::attribute::Ennemies3 ||
        attr._type == component::attribute::Ennemies4 ||
        attr._type == component::attribute::Ennemies5) && shoot_id.id != j && state._stateKey == component::state::stateKey::Alive) {
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
        attributes[i]._type != component::attribute::Shoot1 &&
        attributes[i]._type != component::attribute::Shoot11)
            continue;
        auto &shoot_id = idPlayers[i];
        for (size_t j = 0; j < attributes.size(); j++) {
            if (!should_check_collision(j, attributes, states, shoot_id))
                continue;
            if (!check_collision(positions, sizes, attributes, i, j))
                continue;
            //if (!check_collision_boss(positions, sizes, attributes, i, j)) {
            //    continue;
            //}
            if (attributes[j]._type == component::attribute::Player1)
                handle_collision_with_player1(i, shoot_id.id, j, lifes, states, attributes, reg);
            if (attributes[j]._type == component::attribute::Player2)
                handle_collision_with_player2(i, shoot_id.id, j, lifes, states, attributes, reg);
            if (attributes[j]._type == component::attribute::Player3)
                handle_collision_with_player3(i, shoot_id.id, j, lifes, states, attributes, reg);
            if (attributes[j]._type == component::attribute::Player4)
                handle_collision_with_player4(i, shoot_id.id, j, lifes, states, attributes, reg);
            if (is_enemy(attributes[j]))
                handle_collision_with_enemy(i, shoot_id.id, j, scores, states, lifes, attributes, reg);
        }
    }
}

void System::collision_system_with_frendly_fire(registry &reg)
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
            if (!should_check_collision(j, attributes, states, shoot_id))
                continue;
            if (!check_collision(positions, sizes, attributes, i, j))
                continue;
            //if (!check_collision_boss(positions, sizes, attributes, i, j)) {
            //    continue;
            //}
            if (attributes[j]._type == component::attribute::Player1)
                handle_collision_with_fire_player1(i, j, lifes, states, attributes);
            if (attributes[j]._type == component::attribute::Player2)
                handle_collision_with_fire_player2(i, j, lifes, states, attributes);
            if (attributes[j]._type == component::attribute::Player3)
                handle_collision_with_fire_player3(i, j, lifes, states, attributes);
            if (attributes[j]._type == component::attribute::Player4)
                handle_collision_with_fire_player4(i, j, lifes, states, attributes);
            if (is_enemy(attributes[j]))
                handle_collision_with_enemy(i, shoot_id.id, j, scores, states, lifes, attributes, reg);
        }
    }
}

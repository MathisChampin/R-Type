#include "system.hpp"
#include "attribute.hpp"
#include "state.hpp"
#include "size.hpp"
#include "position.hpp"
#include "idPlayer.hpp"
#include <chrono>
#include <ctime>

void create_power_up(component::attribute::entityType type, registry &reg)
{
    Entity powerUp = reg.spawn_entity();

    reg.add_component<component::attribute>(powerUp, {type});
    reg.add_component<component::state>(powerUp, {component::state::Alive});
    reg.add_component<component::position>(powerUp, {15, 15});
    reg.add_component<component::size>(powerUp, {50, 50});
}

void create_power_up_life(component::attribute::entityType type, registry &reg, int posx, int posy, size_t idPlayer)
{
    auto &attribute = reg.get_components<component::attribute>();
    auto &idPlayers = reg.get_components<component::idPlayer>();

    for (size_t j = 0; j < attribute.size(); j++) {
        if (attribute[j]._type == component::attribute::PowerUpLife && idPlayers[j].id == idPlayer) {
            return;
        }
    }
    Entity powerUp = reg.spawn_entity();

    reg.add_component<component::attribute>(powerUp, {type});
    reg.add_component<component::state>(powerUp, {component::state::Alive});
    reg.add_component<component::position>(powerUp, {posx, posy});
    reg.add_component<component::size>(powerUp, {50, 50});
    reg.add_component<component::idPlayer>(powerUp, {idPlayer});
}

void System::spawn_power_up(registry &reg)
{
    using namespace std::chrono;
    static auto lastSpawnTime = steady_clock::now();
    auto currentTime = steady_clock::now();

    if (duration_cast<seconds>(currentTime - lastSpawnTime).count() >= 10) {
        create_power_up(component::attribute::entityType::PowerUpMove, reg);
        create_power_up(component::attribute::entityType::PowerUpShoot, reg);
        lastSpawnTime = currentTime;
    }
}

void System::spawn_power_up_life(registry &reg)
{
    auto &position = reg.get_components<component::position>();
    auto &attribute = reg.get_components<component::attribute>();
    auto &states = reg.get_components<component::state>();

    for (size_t i = 0; i < attribute.size(); i++) {
        if ((attribute[i]._type == component::attribute::Ennemies2 || 
            attribute[i]._type == component::attribute::Ennemies3 ||
            attribute[i]._type == component::attribute::Ennemies4 || 
            attribute[i]._type == component::attribute::Ennemies) && states[i]._stateKey == component::state::Dead)
                    create_power_up_life(component::attribute::PowerUpLife, reg, position[i].x, position[i].y, i);
    }
}

#include "attribute.hpp"
#include "controllable.hpp"
#include "level.hpp"
#include "life.hpp"
#include "position.hpp"
#include "score.hpp"
#include "size.hpp"
#include "state.hpp"
#include "velocity.hpp"
#include "system.hpp"
#include "Registry.hpp"
#include <random>

void System::ennemies_system(registry &reg)
{
    Entity ennemies = reg.spawn_entity();
    int y = rand();

    reg.add_component<component::attribute>(ennemies, {component::attribute::Ennemies});
    reg.add_component<component::life>(ennemies, {1});
    reg.add_component<component::position>(ennemies, {1920, y});
    reg.add_component<component::size>(ennemies, {32, 14}); // remplacer par size de la sprite de l'ennemie
    reg.add_component<component::state>(ennemies, {component::state::Alive});
    reg.add_component<component::velocity>(ennemies, {20, 0});
}

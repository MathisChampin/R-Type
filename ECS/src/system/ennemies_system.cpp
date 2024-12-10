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
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 1080);

    Entity ennemies = reg.spawn_entity();
    int y = dist(rng);

    reg.add_component<component::attribute>(ennemies, {component::attribute::Ennemies});
    reg.add_component<component::controllable>(ennemies, {component::controllable::NoKey});
    reg.add_component<component::level>(ennemies, {component::level::Level0});
    reg.add_component<component::life>(ennemies, {1});
    reg.add_component<component::position>(ennemies, {1920, y});
    reg.add_component<component::score>(ennemies, {0});
    reg.add_component<component::size>(ennemies, {32, 14}); // remplacer par size de la sprite de l'ennemie
    reg.add_component<component::state>(ennemies, {component::state::Alive});
    reg.add_component<component::velocity>(ennemies, {20, 0});
}

#include <iostream>
#include "Registry.hpp"
#include "position.hpp"
#include "velocity.hpp"
#include "controllable.hpp"
#include "attribute.hpp"
#include "size.hpp"
#include "system.hpp"

int main() {
    registry reg;
    System sys;

    auto &positions = reg.register_component<component::position>();
    auto &sizes = reg.register_component<component::size>();
    auto &attributes = reg.register_component<component::attribute>();

    Entity player = reg.spawn_entity();
    Entity enemy = reg.spawn_entity();

    reg.add_component<component::position>(player, {10, 20});
    reg.add_component<component::size>(player, {5, 5});
    reg.add_component<component::attribute>(player, {component::attribute::Player});

    reg.add_component<component::position>(enemy, {12, 22});
    reg.add_component<component::size>(enemy, {5, 5});
    reg.add_component<component::attribute>(enemy, {component::attribute::Ennemies});

    const auto &pos1 = positions[player.get_id()];
    const auto &size1 = sizes[player.get_id()];
    const auto &attr1 = attributes[player.get_id()];

    const auto &pos2 = positions[enemy.get_id()];
    const auto &size2 = sizes[enemy.get_id()];
    const auto &attr2 = attributes[enemy.get_id()];

    std::cout << "Entity " << player.get_id() << ": Position(" << pos1.x << ", " << pos1.y
              << "), Size(" << size1.x << ", " << size1.y << "), Type = " << attr1._type << std::endl;

    std::cout << "Entity " << enemy.get_id() << ": Position(" << pos2.x << ", " << pos2.y
              << "), Size(" << size2.x << ", " << size2.y << "), Type = " << attr2._type << std::endl;

    std::cout << "\nChecking for collisions..." << std::endl;
    sys.collision_system(reg);

    return 0;
}

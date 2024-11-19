#include <iostream>
#include "Registry.hpp"
#include "position.hpp"
#include "velocity.hpp"
#include "controllable.hpp"
#include "system.hpp"

int main() {
    registry reg;
    System sys;

    auto &positions = reg.register_component<component::position>();
    auto &velocity = reg.register_component<component::velocity>();
    auto &controllable = reg.register_component<component::controllable>();

    entity_t entity1 = reg.spawn_entity();
    entity_t entity2 = reg.spawn_entity();

    reg.add_component<component::position>(entity1, {10, 20});
    reg.add_component<component::velocity>(entity1, {15, 20});
    reg.add_component<component::controllable>(entity1, {component::controllable::Right});
    reg.add_component<component::position>(entity2, {12, 40});
    reg.add_component<component::velocity>(entity2, {19, 10});
    reg.add_component<component::controllable>(entity2, {component::controllable::Up});

    const auto &pos1 = positions[entity1.get_id()];
    const auto &vel1 = velocity[entity1.get_id()];
    const auto &vel2 = velocity[entity2.get_id()];
    const auto &pos2 = positions[entity2.get_id()];
    const auto &c1 = controllable[entity1.get_id()];
    const auto &c2 = controllable[entity2.get_id()];

    std::cout << "Initial Positions and Velocities:" << std::endl;
    std::cout << "Entity " << entity1.get_id() << ": posx " << pos1.x << " & posy " << pos1.y 
              << ", velx " << vel1.x << " & vely " << vel1.y << " control = " << c1.active_key << std::endl;
    std::cout << "Entity " << entity2.get_id() << ": posx " << pos2.x << " & posy " << pos2.y 
              << ", velx " << vel2.x << " & vely " << vel2.y << " control = " << c2.active_key << std::endl;
    
    sys.position_system(reg);
    const auto &updated_pos = positions[entity1.get_id()];
    const auto &updated_pos2 = positions[entity2.get_id()];
    std::cout << "\nUpdated Positions after applying velocity:" << std::endl;
    std::cout << "Entity " << entity1.get_id() << ": posx " << updated_pos.x << " & posy " << updated_pos.y << std::endl;
    std::cout << "Entity " << entity2.get_id() << ": posx " << updated_pos2.x << " & posy " << updated_pos2.y << std::endl;

    sys.control_system(reg);
    const auto &updated_vel = velocity[entity1.get_id()];
    const auto &updated_vel2 = velocity[entity2.get_id()];
    std::cout << "\nUpdated Velocity after applying control:" << std::endl;
    std::cout << "Entity " << entity1.get_id() << ": velx " << updated_vel.x << " & vely " << updated_vel.y << std::endl;
    std::cout << "Entity " << entity2.get_id() << ": velx " << updated_vel2.x << " & vely " << updated_vel2.y << std::endl;

    return 0;
}


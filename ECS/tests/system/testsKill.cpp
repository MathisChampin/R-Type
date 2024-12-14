#include <criterion/criterion.h>
#include "system.hpp"
#include "state.hpp"
#include "Registry.hpp"

Test(KillSystem, KillEntityUsingGetEntity) {
    registry reg;
    System sys;

    reg.register_component<component::state>();

    Entity entityDead = reg.spawn_entity();
    reg.add_component<component::state>(entityDead, {component::state::stateKey::Dead});

    Entity entityAlive = reg.spawn_entity();
    reg.add_component<component::state>(entityAlive, {component::state::stateKey::Alive});

    sys.kill_system(reg);

    cr_assert_throw(
        reg.get_entity(entityDead.get_id()),
        std::runtime_error,
        "L'entité avec l'état 'Dead' devrait être supprimée."
    );

    try {
        reg.get_entity(entityAlive.get_id());
    } catch (const std::exception& e) {
        cr_assert_fail("L'entité avec l'état 'Alive' ne devrait pas être supprimée.");
    }
}

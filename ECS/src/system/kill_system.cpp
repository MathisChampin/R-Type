#include "system.hpp"
#include "state.hpp"
#include "attribute.hpp"
#include "Registry.hpp"

void System::kill_system(registry &reg)
{
    auto &attributes = reg.get_components<component::attribute>();

    for (size_t i = 0; i < attributes.size(); i++) {
        auto Entity = reg.get_entity(i);
        reg.kill_entity(Entity);
    }
}

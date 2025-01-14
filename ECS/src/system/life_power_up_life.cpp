#include "system.hpp"
#include "life.hpp"
#include "attribute.hpp"

void System::power_up_life_p1(registry &reg)
{
    auto &life = reg.get_components<component::life>();
    auto &attributes = reg.get_components<component::attribute>();

    for (size_t i = 0; i < attributes.size(); i++) {
        if (attributes[i]._type == component::attribute::Player1) {
            life[i].life += 1;
        }
    }
}

void System::power_up_life_p2(registry &reg)
{
    auto &life = reg.get_components<component::life>();
    auto &attributes = reg.get_components<component::attribute>();

    for (size_t i = 0; i < attributes.size(); i++) {
        if (attributes[i]._type == component::attribute::Player2) {
            life[i].life += 1;
        }
    }
}

void System::power_up_life_p3(registry &reg)
{
    auto &life = reg.get_components<component::life>();
    auto &attributes = reg.get_components<component::attribute>();

    for (size_t i = 0; i < attributes.size(); i++) {
        if (attributes[i]._type == component::attribute::Player3) {
            life[i].life += 1;
        }
    }
}

void System::power_up_life_p4(registry &reg)
{
    auto &life = reg.get_components<component::life>();
    auto &attributes = reg.get_components<component::attribute>();

    for (size_t i = 0; i < attributes.size(); i++) {
        if (attributes[i]._type == component::attribute::Player4) {
            life[i].life += 1;
        }
    }
}
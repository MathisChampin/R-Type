#include <criterion/criterion.h>
#include "Entity.hpp"

Test(EntityTests, ConstructorAndImplicitConversion) {
    size_t initialValue = 42;
    Entity entity(initialValue);

    size_t convertedValue = entity;
    cr_assert_eq(convertedValue, initialValue, "La conversion implicite ne donne pas la bonne valeur. Attendu: %zu, Obtenu: %zu", initialValue, convertedValue);
}

Test(EntityTests, DifferentValue) {
    size_t initialValue = 100;
    Entity entity(initialValue);

    size_t convertedValue = entity;
    cr_assert_eq(convertedValue, initialValue, "La conversion implicite échoue pour une valeur différente. Attendu: %zu, Obtenu: %zu", initialValue, convertedValue);
}

Test(EntityTests, UsageAsSizeT) {
    Entity entity(55);
    size_t result = entity + 10;

    cr_assert_eq(result, 65, "L'entité n'est pas correctement utilisée comme size_t dans une opération arithmétique. Attendu: 65, Obtenu: %zu", result);
}

Test(EntityTests, UsageAsSizeT2) {
    Entity entity(55);
    size_t result = entity - 10;

    cr_assert_eq(result, 45, "L'entité n'est pas correctement utilisée comme size_t dans une opération arithmétique. Attendu: 45, Obtenu: %zu", result);
}

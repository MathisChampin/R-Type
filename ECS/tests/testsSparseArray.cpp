#include <criterion/criterion.h>
#include "SparseArray.hpp"
#include "Entity.hpp"

Test(SparseArrayTests, DefaultConstructor_SizeZero) {
    sparse_array<Entity> array;
    cr_assert_eq(array.size(), 0, "La taille initiale de sparse_array devrait être 0.");
}

Test(SparseArrayTests, InsertAt_AddSingleElement) {
    sparse_array<Entity> array;

    Entity e1(10);
    array.insert_at(0, e1);
    cr_assert_eq(array.size(), 1, "La taille après une insertion devrait être 1.");
    cr_assert_eq(static_cast<size_t>(array[0]), 10, "L'entité insérée devrait avoir la valeur 10.");
}

Test(SparseArrayTests, InsertAt_AddMultipleElements) {
    sparse_array<Entity> array;

    Entity e1(10), e2(20);
    array.insert_at(0, e1);
    array.insert_at(1, e2);
    cr_assert_eq(array.size(), 2, "La taille après deux insertions devrait être 2.");
    cr_assert_eq(static_cast<size_t>(array[0]), 10, "L'entité à l'indice 0 devrait avoir la valeur 10.");
    cr_assert_eq(static_cast<size_t>(array[1]), 20, "L'entité à l'indice 1 devrait avoir la valeur 20.");
}

Test(SparseArrayTests, InsertAt_OverwriteExistingElement) {
    sparse_array<Entity> array;

    Entity e1(10), e2(30);
    array.insert_at(0, e1);
    array.insert_at(0, e2);
    cr_assert_eq(array.size(), 1, "La taille ne devrait pas changer lors de la modification d'un élément.");
    cr_assert_eq(static_cast<size_t>(array[0]), 30, "L'entité à l'indice 0 devrait avoir été remplacée par 30.");
}

Test(SparseArrayTests, EmplaceAt_AddSingleElement) {
    sparse_array<Entity> array;

    array.emplace_at(0, 42);
    cr_assert_eq(array.size(), 1, "La taille après emplace_at devrait être 1.");
    cr_assert_eq(static_cast<size_t>(array[0]), 42, "L'entité insérée devrait avoir la valeur 42.");
}

Test(SparseArrayTests, EmplaceAt_ModifyExistingElement) {
    sparse_array<Entity> array;

    array.emplace_at(0, 42);
    array.emplace_at(0, 99);
    cr_assert_eq(array.size(), 1, "La taille ne devrait pas changer lors de la modification d'un élément.");
    cr_assert_eq(static_cast<size_t>(array[0]), 99, "L'entité à l'indice 0 devrait avoir été remplacée par 99.");
}

Test(SparseArrayTests, Erase_RemoveSingleElement) {
    sparse_array<Entity> array;

    array.emplace_at(0, 1);
    array.emplace_at(1, 2);
    array.erase(1);
    cr_assert_eq(array.size(), 1, "La taille après suppression d'un élément devrait être 1.");
    cr_assert_eq(static_cast<size_t>(array[0]), 1, "L'entité restante devrait être celle avec la valeur 1.");
}

Test(SparseArrayTests, Erase_RemoveLastElement) {
    sparse_array<Entity> array;

    array.emplace_at(0, 1);
    array.erase(0);
    cr_assert_eq(array.size(), 0, "La taille après suppression de l'unique élément devrait être 0.");
}

Test(SparseArrayTests, GetIndex_ElementPresent) {
    sparse_array<Entity> array;

    Entity e1(10), e2(20), e3(30);
    array.insert_at(0, e1);
    array.insert_at(1, e2);
    array.insert_at(2, e3);

    size_t index = array.get_index(e2);
    cr_assert_eq(index, 1, "L'indice de l'entité avec la valeur 20 devrait être 1.");
}

Test(SparseArrayTests, GetIndex_ElementAbsent) {
    sparse_array<Entity> array;

    Entity e1(10), e2(20);
    array.insert_at(0, e1);

    size_t index = array.get_index(e2);
    cr_assert_eq(index, array.size(), "La recherche d'une entité absente devrait renvoyer la taille du tableau.");
}

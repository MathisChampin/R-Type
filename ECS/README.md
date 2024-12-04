### Documentation du Système ECS

---

## **Introduction**

Le système ECS (Entity-Component-System) est une architecture logicielle utilisée pour gérer les entités dans les jeux vidéo et autres applications. Il sépare les données (composants) de la logique (systèmes) pour permettre une gestion efficace des entités.

---

## **Structure du Dossier**

Le dossier `ECS` contient les éléments suivants :

- **`include/`** : Fichiers d'en-tête pour les composants, les entités, les systèmes, et le registre.
- **`src/`** : Implémentations des systèmes.
- **`tests/`** : Tests unitaires pour les composants, les entités, les systèmes, et le registre.
- **`Makefile`** : Fichier de construction pour compiler le projet et exécuter les tests.

---

## **Composants**

Les composants sont des structures de données contenant les attributs des entités. Voici quelques exemples :

### `position.hpp`

```cpp
#ifndef POSITION_HPP_
#define POSITION_HPP_

namespace component {
    struct position {
        int x;
        int y;
    };
}

#endif /* POSITION_HPP_ */
```

### `velocity.hpp`

```cpp
#ifndef VELOCITY_HPP_
#define VELOCITY_HPP_

namespace component {
    struct velocity {
        int x;
        int y;
    };
}

#endif /* VELOCITY_HPP_ */
```

### `attribute.hpp`

```cpp
#ifndef ATTRIBUTE_HPP_
#define ATTRIBUTE_HPP_

namespace component {
    struct attribute {
        enum entityType {
            Player,
            Ennemies,
            None
        };
        entityType _type;
    };
}

#endif /* ATTRIBUTE_HPP_ */
```

---

## **Entités**

Les entités sont des identifiants uniques permettant de gérer les composants.

### `Entity.hpp`

```cpp
#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <string>

class Entity {
public:
    Entity() : value(0) {};
    explicit Entity(size_t val): value{val} {};
    operator size_t() const { return value; };
    size_t get_id() const { return value; };

private:
    size_t value;
};

#endif /* ENTITY_HPP_ */
```

---

## **Systèmes**

Les systèmes contiennent la logique opérant sur les composants. Voici des exemples :

### `position_system.cpp`

```cpp
#include "position.hpp"
#include "velocity.hpp"
#include "system.hpp"

void System::position_system(registry &reg)
{
    auto& positions = reg.get_components<component::position>();
    auto& velocities = reg.get_components<component::velocity>();

    for (size_t i = 0; i < positions.size() && i < velocities.size(); i++) {        
        auto& pos = positions[i];
        const auto& vel = velocities[i];

        pos.x += vel.x;
        pos.y += vel.y;
    }
}
```

### `collision_system.cpp`

```cpp
#include "position.hpp"
#include "size.hpp"
#include "system.hpp"
#include "attribute.hpp"
#include <iostream>

void check_collision(
    sparse_array<component::position> &positions,
    sparse_array<component::size> &sizes,
    int i, int j
) {
    const auto &pos1 = positions[i];
    const auto &pos2 = positions[j];
    const auto &size1 = sizes[i];
    const auto &size2 = sizes[j];
    
    if (pos1.x < pos2.x + size2.x && pos1.x + size1.x > pos2.x &&
        pos1.y < pos2.y + size2.y && pos1.y + size1.y > pos2.y) {
        std::cout << "Collision detected between entity " << i 
                  << " and entity " << j << std::endl;
    } else {
        std::cout << "No collision found" << std::endl;
    }
}

void System::collision_system(registry &reg)
{
    auto &attributes = reg.get_components<component::attribute>();
    auto &positions = reg.get_components<component::position>();
    auto &sizes = reg.get_components<component::size>();

    for (size_t i = 0; i < attributes.size(); ++i) {
        for (size_t j = i + 1; j < attributes.size(); ++j) {
            const auto &attr1 = attributes[i];
            const auto &attr2 = attributes[j];
            if ((attr1._type == component::attribute::Player && attr2._type == component::attribute::Ennemies) ||
                (attr1._type == component::attribute::Ennemies && attr2._type == component::attribute::Player)) {
                    check_collision(positions, sizes, i, j);
            } else {
                std::cout << "No collision between same type" << std::endl;
            }
        }
    }
}
```

---

## **Registre**

Le registre gère les entités et leurs composants.

### `Registry.hpp`

```cpp
#ifndef REGISTRY_HPP_
#define REGISTRY_HPP_

#include "SparseArray.hpp"
#include "Entity.hpp"
#include <typeindex>
#include <unordered_map>
#include <any>
#include <functional>

class registry {
public:
    template <class Component>
    sparse_array<Component>& register_component() {
        auto type_index = std::type_index(typeid(Component));

        if (_components_arrays.find(type_index) == _components_arrays.end()) {
            _components_arrays[type_index] = std::make_any<sparse_array<Component>>();
            _remove_functions[type_index] = [this](registry&, Entity const& e) {
                this->remove_component<Component>(e);
            };
        }
        return std::any_cast<sparse_array<Component>&>(_components_arrays[type_index]);
    }

    // Autres méthodes comme `spawn_entity`, `kill_entity`, etc.
};

#endif /* REGISTRY_HPP_ */
```

---

## **Tests**

Les tests unitaires vérifient le bon fonctionnement des composants, entités, systèmes et registre.

### Exemple : `testsEntity.cpp`

```cpp
#include <criterion/criterion.h>
#include "Entity.hpp"

Test(EntityTests, ConstructorAndImplicitConversion) {
    size_t initialValue = 42;
    Entity entity(initialValue);

    size_t convertedValue = entity;
    cr_assert_eq(convertedValue, initialValue, 
        "La conversion implicite ne donne pas la bonne valeur. Attendu: %zu, Obtenu: %zu", 
        initialValue, convertedValue);
}
```

---

## **Compilation et Exécution**

Pour compiler le projet et exécuter les tests :

### Compilation

```sh
make
```

### Exécution des Tests

```sh
make test_run
```
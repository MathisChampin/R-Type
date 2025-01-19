# Documentation du Système ECS

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

## Entités

Une entité est simplement un identifiant unique représentant un objet ou un concept dans votre application. Une entité n’a ni état ni comportement par défaut ; elle tire ses propriétés des composants qui lui sont associés.
Création d'une entité

Pour créer une nouvelle entité, utilisez le registre (Registry):

```
Entity myEntity = registry.spawn_entity();
```

Fonctions principales des entités

Les entités sont des identifiants uniques et les fonctions principales pour les manipuler sont :

- spawn_entity : Crée une nouvelle entité.
- kill_entity : Supprime une entité et tous les composants qui lui sont associés.

## Liste des Composants

Les composants sont des structures de données associées aux entités. Chaque composant représente une propriété ou un état spécifique d'une entité. Voici la liste complète des composants disponibles :

### Composants Disponibles

1. **`attribute.hpp`**
   - Définit le type ou les attributs de l'entité, comme un joueur, un ennemi, ou un tir.
```cpp
namespace component {
    struct attribute {
        enum Type { Player, Enemy, Shoot } _type;
    };
}

// Ajouter un attribut à une entité
registry.add_component<component::attribute>(entity, {component::attribute::Player});
```

1. **`controllable.hpp`**
   - Indique si l'entité peut être contrôlée par des entrées utilisateur (ex. touches de clavier ou de souris).
```cpp
namespace component {
    struct controllable {
        enum Key { Left, Right, Shoot, None } active_key;
    };
}

// Ajouter un composant contrôlable
registry.add_component<component::controllable>(entity, {component::controllable::None});
```
3. **`idPlayer.hpp`**
   - Stocke l'identifiant unique associé à un joueur pour les entités spécifiques à un joueur.
```cpp
namespace component {
    struct idPlayer {
        int id;
    };
}

// Ajouter un identifiant de joueur
registry.add_component<component::idPlayer>(entity, {1});
```
4. **`level.hpp`**
   - Gère le niveau d'une entité ou la progression dans un jeu.
```cpp
namespace component {
    struct level {
        enum LevelKey { Level1, Level2, Level3 } _levelKey;
    };
}

// Ajouter un composant de niveau
registry.add_component<component::level>(entity, {component::level::Level1});
```
5. **`life.hpp`**
   - Suit le nombre de points de vie d'une entité. Les entités avec 0 points de vie peuvent être marquées pour suppression.
```cpp
namespace component {
    struct life {
        int life;
    };
}

// Ajouter des points de vie
registry.add_component<component::life>(entity, {100});
```
6. **`position.hpp`**
   - Contient les coordonnées `(x, y)` d'une entité dans le monde.
```cpp
namespace component {
    struct position {
        int x, y;
    };
}

// Ajouter une position
registry.add_component<component::position>(entity, {50, 100});
```
7. **`score.hpp`**
   - Stocke le score d'une entité, souvent utilisé pour les joueurs.
```cpp
namespace component {
    struct score {
        int points;
    };
}

// Ajouter un score
registry.add_component<component::score>(entity, {0});
```
8. **`shoot_type.hpp`**
   - Définit le type de projectile ou de tir associé à une entité, comme un tir normal ou spécial.
```cpp
namespace component {
    struct shoot_type {
        component::attribute _type;
    };
}

registry.add_component<component::shoot_type>(entity, {component::shoot_type::Normal});
```

9. **`size.hpp`**
   - Gère les dimensions `(largeur, hauteur)` d'une entité pour les collisions ou le rendu.
```cpp
namespace component {
    struct size {
        float width, height;
    };
}

// Ajouter une taille
registry.add_component<component::size>(entity, {50.0f, 100.0f});
```
10. **`state.hpp`**
    - Indique l'état actuel d'une entité, comme `Alive`, `Dead`, `Win` ou `Lose`.
```cpp
namespace component {
    struct state {
        enum StateKey { Alive, Dead, Win, Lose } _stateKey;
    };
}

// Ajouter un état
registry.add_component<component::state>(entity, {component::state::Alive});
```
11. **`velocity.hpp`**
    - Contient les vecteurs de mouvement `(dx, dy)` pour calculer les déplacements des entités.
```cpp
namespace component {
    struct velocity {
        float dx, dy;
    };
}

// Ajouter une vélocité
registry.add_component<component::velocity>(entity, {1.0f, 0.0f});
```
---

## SparseArray

Le SparseArray est une structure de données optimisée pour stocker les composants. Il est utilisé pour associer efficacement des composants aux entités et offre des opérations rapides pour accéder aux données.
Fonctions principales du SparseArray

Ajout d’un composant :

```
sparseArray.insert(entityId, component);
```
  - entityId : Identifiant de l'entité.
  -   component : Instance du composant à associer.
  -   Associe un composant à une entité. Si un composant existe déjà pour cette entité, il est remplacé.

Récupération d’un composant :

```
auto& component = sparseArray[entityId];
```   
   - Retourne une référence au composant associé à l’entité.

Suppression d’un composant :

```
sparseArray.erase(entityId);
```
  - Supprime le composant associé à une entité.

Itération sur les composants :

```
    for (auto& component : sparseArray) {
        // Utilisez chaque composant
    }
```
- Permet de parcourir tous les composants présents.

Vérification d'existence d’un composant
```cpp
bool exists = sparseArray.contains(entityId);
```
- Retourne true si un composant est associé à l'entité, sinon false.

Récupération sécurisée d’un composant
```cpp
auto &component = sparseArray.get(entityId);
```
- Retourne le composant associé à l'entité, ou nullptr si aucun composant n'est associé.

Taille actuelle
```cpp
size_t size = sparseArray.size();
```
- Retourne le nombre de composants actuellement présents dans le SparseArray.

### Exemple d'utilisation
Voici un exemple illustrant comment utiliser le SparseArray :
```cpp
#include "SparseArray.hpp"

// Définition d'un composant exemple
struct Position {
    float x, y;
};

int main() {
    SparseArray<Position> sparseArray;

    // Ajout d'un composant
    sparseArray.insert(1, Position{100.0f, 200.0f});
    sparseArray.insert(2, Position{300.0f, 400.0f});

    // Récupération d'un composant
    if (sparseArray.contains(1)) {
        auto& pos = sparseArray[1];
        std::cout << "Position: " << pos.x << ", " << pos.y << std::endl;
    }

    // Suppression d'un composant
    sparseArray.erase(2);

    // Itération sur les composants
    for (auto& pos : sparseArray) {
        std::cout << "Position: " << pos.x << ", " << pos.y << std::endl;
    }

    return 0;
}
```

## Registry

Le registre (Registry) est le cœur du système ECS. Il gère la création des entités, leur destruction, ainsi que l’ajout et la gestion des composants.
Fonctions principales du Registry

Créer une entité :

```
Entity entity = registry.spawn_entity();
```
  - Retourne un identifiant unique pour une nouvelle entité.

Ajouter un composant :

```
registry.addComponent(entity, MyComponent{...});
```
  - Associe un composant à une entité.
- Si un composant du même type existe déjà pour cette entité, il sera remplacé.

Récupérer un composant :

```
MyComponent& myComponent = registry.getComponent<MyComponent>(entity);
```
  - Retourne une référence au composant associé à l’entité.

Supprimer un composant :

```
registry.removeComponent<MyComponent>(entity);
```
  - Supprime un composant spécifique d’une entité.

Détruire une entité :

```
registry.kill_entity(entity);
```
  - Supprime une entité ainsi que tous ses composants associés.


## Exemple complet

Voici un exemple illustrant comment utiliser le Registry :
``` cpp
#include "Registry.hpp"
#include "position.hpp"
#include "velocity.hpp"

int main() {
    // Création d'un registre
    Registry registry;

    // Création d'une entité
    Entity entity = registry.spawn_entity();

    // Ajout de composants
    registry.add_component(entity, Position{100.0f, 200.0f});
    registry.add_component(entity, Velocity{5.0f, -3.0f});

    // Vérification de la présence d'un composant
    if (registry.has_component<Position>(entity)) {
        // Récupération et modification d'un composant
        auto& position = registry.get_component<Position>(entity);
        position.x += 10.0f;
        position.y += 20.0f;
    }

    // Suppression d'un composant
    registry.remove_component<Velocity>(entity);

    // Destruction de l'entité
    registry.kill_entity(entity);

    return 0;
}
```

## Systèmes

Un système est une logique opérationnelle qui manipule les entités en fonction de leurs composants. Les systèmes parcourent les entités ayant des composants spécifiques et appliquent des actions ou des calculs. Par exemple, un système de position pourrait mettre à jour les coordonnées d'une entité en fonction de sa vitesse.
Liste des systèmes dans le projet

1. Collision System

- Rôle : Gère les collisions entre les entités.
- Fonctionnement :
    - Parcourt les entités ayant des composants de type Position et BoundingBox.
    - Vérifie si deux entités se chevauchent.
    - Applique des actions comme arrêter un mouvement ou infliger des dégâts.
  
Exemple d'utilisation :
```cpp
System sys;
sys.collision_system(registry);
```

2. Controllable System

- Rôle : Permet de manipuler les entités contrôlées par un joueur.

- Fonctionnement :
    - Parcourt les entités avec un composant Controllable.
    - Applique les commandes (déplacement, actions) basées sur les entrées utilisateur ou une logique définie.
  
Exemple d'utilisation :
```cpp
System sys;
sys.controllable_system(registry);
```

3. Kill System

- Rôle : Supprime les entités marquées comme "mortes" ou inutilisées.
- Fonctionnement :
    - Parcourt les entités ayant un composant Health.
    - Supprime celles ayant des points de vie inférieurs ou égaux à zéro.
  
Exemple d'utilisation :
``` cpp
System sys;
sys.kill_system(registry);
```

4. Level System

- Rôle : Gère la progression et les changements de niveau.
- Fonctionnement :
    - Parcourt les entités ayant un composant Level.
    - Applique des effets ou met à jour les statistiques en fonction du niveau.
  
Exemple d'utilisation :
```cpp
System sys;
sys.level_system(registry);
```

5. Position System

- Rôle : Met à jour la position des entités en fonction de leur vitesse et de leur direction.
- Fonctionnement :
    - Parcourt les entités avec les composants Position et Velocity.
    - Calcule la nouvelle position en appliquant des vecteurs de déplacement.

Exemple d'utilisation :
```cpp
System sys;
sys.position_system(registry);
```

6. Shoot System

- Rôle : Gère le tir de projectiles par les entités.
- Fonctionnement :
    - Parcourt les entités avec un composant Shooter.
    - Crée de nouvelles entités "projectiles" avec des composants Position et Velocity.
  
Exemple d'utilisation :
```cpp
System sys;
sys.shoot_sytem(registry);
```

7. Collision Power-Up System
- Rôle : Gère les collisions entre les entités et les power-ups.
- Fonctionnement :
    - Vérifie si une entité avec un composant Position entre en collision avec un power-up.
    - Crée de nouvelles entités "projectiles" avec des composants
    - Position et Velocity.

Exemple d'utilisation :
```cpp
System sys;
sys.collision_power_up(registry);
```

8. Create Power-Up System
- Rôle : Crée et gère les power-ups dans le jeu.
- Fonctionnement :
    - Génère des entités "power-up" avec des composants spécifiques..
    - Les power-ups peuvent inclure des effets comme l'augmentation de la vitesse, de la vie, etc.

Exemple d'utilisation :
```cpp
System sys;
sys.create_power_up(registry);
```

9. Life Power-Up System
- Rôle : Applique les effets de power-ups qui augmentent les points de vie.
- Fonctionnement :
    - Parcourt les entités ayant un composant Life.
    - Ajoute des points de vie en fonction des collisions avec des power-ups.

Exemple d'utilisation :
```cpp
System sys;
sys.life_power_up_life(registry);
```

10. Velocity Power-Up System
- Rôle : Gère les power-ups qui augmentent la vitesse des entités.
- Fonctionnement :
    - Parcourt les entités ayant un composant Velocity.
    - Augmente la vitesse des entités en fonction des collisions avec des power-ups.

Exemple d'utilisation :
```cpp
System sys;
sys.velocity_power_up_move(registry);
```

11. Lose System
- Rôle : Détecte les conditions de défaite.
- Fonctionnement :
    - Parcourt les entités avec un composant State.
    - Change l’état des entités en Lose si certaines conditions sont remplies (par exemple, lorsque les points de vie sont à zéro).

Exemple d'utilisation :

```cpp
System sys;
sys.lose_system(registry);
```

11. Win System
- Rôle : Détecte les conditions de victoire.
- Fonctionnement :
    - Parcourt les entités avec un composant Level.
    - Change l’état des entités en Win lorsque le niveau final est atteint.

Exemple d'utilisation :

```cpp
System sys;
sys.win_system(registry);
```

### Comment ajouter un nouveau système ?

ajout de la méthode dans la class système :
    Implémentez une fonction qui parcourt les entités et applique une logique.

```
class System {
public:
    void exemple_system(Registry& registry);
};
```

Ajouter le système dans le jeu :

Instanciez et appelez le système dans votre boucle principale.

```
System sys;
sys.exemple_system(registry);
```
### Exemple d'utilisation des systemes

```cpp
#include "Registry.hpp"
#include "System.hpp"

int main() {
    registry reg;

    // Création d'entités
    Entity player = reg.spawn_entity();
    reg.add_component(player, component::Position{100, 200});
    reg.add_component(player, component::Velocity{5, 0});
    reg.add_component(player, component::Life{100});

    // Initialisation des systèmes
    System sys;

    // Mise à jour des positions
    sys.position_system(reg);

    // Gestion des collisions
    sys.collision_system(reg);

    // Vérification des conditions de victoire
    sys.win_system(reg);

    return 0;
}
```

### Conclusion

Le système ECS est conçu pour séparer les responsabilités entre les entités (identifiants), les composants (données) et les systèmes (logique). Cette architecture facilite l’ajout de nouvelles fonctionnalités, la gestion des entités, et l’optimisation des performances.

Si vous avez des questions ou rencontrez des problèmes, veuillez consulter les tests unitaires ou les exemples fournis dans le dossier tests/.

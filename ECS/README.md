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

## Composants

Les composants sont des structures de données associées aux entités. Ils définissent les propriétés et les états des entités.

Exemple de composant :
```
struct Position {
    float x, y;
};
```
Pour associer un composant à une entité, utilisez le registre :

```
registry.addComponent(entity, Position{10.0f, 20.0f});
```

## Exemple complet

Voici un exemple illustrant comment utiliser le système ECS :

# Étape 1 : Créer une entité

```
Entity player = registry.spawn_entity();
```

# Étape 2 : Ajouter des composants

```
struct Position { float x, y; };
struct Velocity { float dx, dy; };

registry.addComponent(player, Position{100.0f, 200.0f});
registry.addComponent(player, Velocity{1.0f, 1.5f});
```

# Étape 3 : Modifier un composant

```
Position& pos = registry.getComponent<Position>(player);
pos.x += 10.0f; // Déplace l'entité de 10 unités sur l'axe X.
```

# Étape 4 : Supprimer un composant

```
registry.removeComponent<Velocity>(player);
```

# Étape 5 : Détruire une entité

```
registry.kill_entity(player);
```

## Systèmes

Un système est une logique opérationnelle qui manipule les entités en fonction de leurs composants. Les systèmes parcourent les entités ayant des composants spécifiques et appliquent des actions ou des calculs. Par exemple, un système de position pourrait mettre à jour les coordonnées d'une entité en fonction de sa vitesse.
Liste des systèmes dans le projet

1. Collision System

    Rôle : Gère les collisions entre les entités.
    Fonctionnement :
        Parcourt les entités ayant des composants de type Position et BoundingBox.
        Vérifie si deux entités se chevauchent.
        Applique des actions comme arrêter un mouvement ou infliger des dégâts.
    Exemple d'utilisation :
    ```
    System sys;
    sys.collision_system(registry);
    ```

2. Controllable System

    Rôle : Permet de manipuler les entités contrôlées par un joueur
    Fonctionnement :
        Parcourt les entités avec un composant Controllable.
        Applique les commandes (déplacement, actions) basées sur les entrées utilisateur ou une logique définie.
    Exemple d'utilisation :
    ```
    System sys;
    sys.controllable_system(registry);
    ```

3. Kill System

    Rôle : Supprime les entités marquées comme "mortes" ou inutilisées.
    Fonctionnement :
        Parcourt les entités ayant un composant Health.
        Supprime celles ayant des points de vie inférieurs ou égaux à zéro.
    Exemple d'utilisation :
    ```
    System sys;
    sys.kill_system(registry);
    ```

4. Level System

    Rôle : Gère la progression et les changements de niveau.
    Fonctionnement :
        Parcourt les entités ayant un composant Level.
        Applique des effets ou met à jour les statistiques en fonction du niveau.
    Exemple d'utilisation :
    ```
    System sys;
    sys.level_system(registry);
    ```

5. Position System

    Rôle : Met à jour la position des entités en fonction de leur vitesse et de leur direction.
    Fonctionnement :
        Parcourt les entités avec les composants Position et Velocity.
        Calcule la nouvelle position en appliquant des vecteurs de déplacement.
    Exemple d'utilisation :
    ```
    System sys;
    sys.position_system(registry);
    ```

6. Shoot System

    Rôle : Gère le tir de projectiles par les entités.
    Fonctionnement :
        Parcourt les entités avec un composant Shooter.
        Crée de nouvelles entités "projectiles" avec des composants Position et Velocity.
    Exemple d'utilisation :
    ```
    System sys;
    sys.shoot_sytem(registry);
    ```

Comment ajouter un nouveau système ?

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

### Conclusion

Le système ECS est conçu pour séparer les responsabilités entre les entités (identifiants), les composants (données) et les systèmes (logique). Cette architecture facilite l’ajout de nouvelles fonctionnalités, la gestion des entités, et l’optimisation des performances.

Si vous avez des questions ou rencontrez des problèmes, veuillez consulter les tests unitaires ou les exemples fournis dans le dossier tests/.

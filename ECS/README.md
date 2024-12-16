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

## **Composants**

Les composants sont des structures de données contenant les attributs des entités. Par exemple :
- `position` : Contient les coordonnées `x` et `y` d'une entité.
- `velocity` : Contient les vitesses `x` et `y` d'une entité.
- `attribute` : Définit le type d'entité (e.g., Joueur, Ennemi).

---

## **Entités**

Les entités sont des identifiants uniques permettant de gérer les composants. Une entité peut être associée à plusieurs composants pour définir ses caractéristiques.

---

## **Systèmes**

Les systèmes contiennent la logique opérant sur les composants. Par exemple :
- `position_system` : Met à jour les positions des entités en fonction de leurs vitesses.
- `collision_system` : Détecte les collisions entre entités.
- `shoot_system` : Gère la logique de tir des entités.

---

## **Registre**

Le registre gère les entités et leurs composants. Il permet de :
- Créer et supprimer des entités.
- Ajouter et retirer des composants.
- Récupérer les composants associés à une entité.

---

## **Tests**

Les tests unitaires vérifient le bon fonctionnement des composants, entités, systèmes et registre. Ils sont situés dans le dossier `tests`.

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
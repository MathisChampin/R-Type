![Screencastfrom2025-01-1903-24-50online-video-cutter com-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/73fdfeef-8ca9-4c00-a7e4-26242d0fa5d6)

# Projet R-Type

Ce repo contient la structure d’un projet **R-Type** avec un **client**,  **serveur** et un **ECS** chacun dans son propre répertoire. Le projet utilise **CMake** pour gérer la configuration et la compilation. Le projet est compilable sur Linux et Windows.

# Compatibilité :

![windows logo](./images/windows-logo.jpg) ![linux logo](./images/linux-logo.png) ![apple logo](./images/apple-logo.png)  
The project runs on Windows and Unix systems, using [CMake](https://cmake.org/).  



## Structure du projet

### ECS (Entity-Component-System)
L’architecture **ECS** est utilisée pour gérer les entités du jeu. Elle sépare les données (**composants**) de la logique (**systèmes**) afin de gérer efficacement les entités.

### Serveur
Le serveur gère la communication réseau et la synchronisation de l’état du jeu. Il utilise plusieurs threads pour traiter les paquets entrants et sortants, garantissant ainsi un état de jeu cohérent entre les clients.

### Client
Le client est responsable de la communication avec le serveur, de l’envoi des actions des joueurs et du rendu de l’état du jeu reçu depuis le serveur.

## Instructions de compilation et d’exécution

### Étape 1 : Compiler le projet

Pour compiler le projet, exécutez simplement la commande suivante à la racine du dépôt :

```bash
make
```

### Étape 2 : Exécuter les programmes

Après la compilation, naviguez dans le répertoire `build`, puis dans les répertoires `client` et `server` pour exécuter les exécutables respectifs.

#### Démarrer le Serveur

```bash
cd build/server
./r_type_server
```

#### Démarrer le Client

```bash
cd build/client
./r_type_client
``` 

--- 

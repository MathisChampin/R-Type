# **Documentation Client**

## **Sommaire**
1. [Introduction](#introduction)
2. [Connexion Serveur-Client](#connexion-serveur-client)
3. [Fichiers de Configuration](#fichiers-de-configuration)
4. [Engine](#engine)
5. [Sprite Manager](#sprite-manager)
6. [Sound Manager](#sound-manager)
7. [Lobby TCP](#lobby-tcp)
8. [Gestion du Jeu (`Game`)](#gamecpp)

---

## **Introduction**

Ce document décrit le fonctionnement du client pour un jeu en réseau basé sur des technologies comme **SFML**, **TCP/UDP**, et un moteur de jeu personnalisé. Le projet inclut des fonctionnalités comme la gestion des sprites, des sons, et une logique de connexion et de gameplay via des packets échangés avec un serveur.

---

## **Connexion Serveur-Client**

### **Description**
Le client utilise une architecture client-serveur pour communiquer avec le serveur via les protocoles **TCP** et **UDP** :
- **TCP** : Utilisé pour les interactions persistantes, comme les connexions au lobby.
- **UDP** : Utilisé pour des communications rapides, comme la mise à jour des sprites et des événements en jeu.

### **Fonctionnalité Principale : Envoi et Réception de Packets**
Le client envoie des packets pour signaler des actions (par exemple, déplacement ou tir) et reçoit des packets contenant des mises à jour du serveur.

#### Exemple : Envoi d'un Packet
```cpp
void Game::handler_packets() {
    auto data = m_client.get_data();
    if (!data.has_value()) { return; }

    auto p = data.value();
    if (p.getOpCode() == NmpClient::EVENT::INFO) {
        int newLife = p.getLife();
        int newScore = p.getScore();
        m_life.updateLife(newLife);
        m_score.updateScore(newScore);
    }
}
```

### **Gestion des Handlers**
Les handlers sont des fonctions associées à des types spécifiques de packets :
```cpp
_mapHandlerPacket = {
    {1, [this](NmpClient::SpriteInfo &sp) { get_player(sp); }},
    {2, [this](NmpClient::SpriteInfo &sp) { get_ennemies(sp); }},
    {7, [this](NmpClient::SpriteInfo &sp) { get_shoots(sp); }},
};
```

---

## **Fichiers de Configuration**

### **Description**
Les fichiers de configuration définissent les ressources graphiques et sonores utilisées par le jeu. Ils permettent de séparer la logique du jeu des données.

### **Exemple : Configuration des Sprites**
Chaque sprite est décrit dans un fichier JSON :
```json
{
    "type": "player",
    "texture": "assets/player/sprite_1.png",
    "texture2": "assets/player/sprite_2.png",
    "texture3": "assets/player/sprite_3.png",
    "texture4": "assets/player/sprite_4.png",
    "texture5": "assets/player/sprite_5.png",
    "position": { "x": 500, "y": 200 },
    "size": { "width": 100, "height": 50 }
}
```

Ces fichiers sont chargés dynamiquement :
```cpp
auto sprite = std::make_shared<Sprite>("../../client/config/player.json");
sprite->setPosition(vecPos);
```

---

## **Engine**


## **Introduction**

L'engine est le composant central qui orchestre l'exécution du jeu. Il gère les états, la boucle principale, les événements, et les différents systèmes graphiques et sonores. Cette section décrit les méthodes principales de la classe `Engine` et leur rôle dans l'application.

---

## **Méthodes Principales**

### 1. **Constructeur : Initialisation des Ressources**

```cpp
Engine::Engine() : m_currentState(GameState::Menu), m_animationTime(0.0f)
```

- **Rôle** :
  - Initialise les éléments fondamentaux du jeu, comme la fenêtre, les polices, les sons et les arrière-plans.
  - Configure les différents menus et sections (menu principal, options, personnalisation, etc.).

- **Exemple** :
  - Initialisation des arrière-plans parallax :
    ```cpp
    std::vector<std::pair<std::string, float>> menuLayers = {
        {"assets/backgrounds/parallax-space-backgound.png", 0.1f},
        {"assets/backgrounds/parallax-space-stars.png", 0.2f}
    };
    m_menuBackground = std::make_unique<ParallaxBackground>(m_window.getSize(), menuLayers);
    ```

---

### 2. **Méthodes d'Initialisation**

#### a) `initializeWindow()`
- **Rôle** :
  - Crée une fenêtre SFML en plein écran.
  - Définit un limiteur de framerate pour garantir des performances fluides.

- **Exemple** :
    ```cpp
    sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();
    m_window.create(videoMode, "R-Type", sf::Style::Fullscreen);
    m_window.setFramerateLimit(60);
    ```

#### b) `initializeFont()`
- **Rôle** :
  - Charge une police spécifique pour l'affichage du texte dans le jeu.
  - Lève une exception si le fichier de police est introuvable.

- **Exemple** :
    ```cpp
    if (!m_font.loadFromFile("./assets/fonts/ZenDots-Regular.ttf")) {
        throw std::runtime_error("Échec du chargement de la police");
    }
    ```

#### c) `initializeSoundManager()`
- **Rôle** :
  - Charge et joue la musique de fond.
  - Gère les erreurs liées au chargement des fichiers sonores.

- **Exemple** :
    ```cpp
    if (!m_soundManager.loadMusic("background", "./assets/music/background.mp3")) {
        std::cerr << "Erreur : Impossible de charger la musique." << std::endl;
    }
    ```

---

### 3. **Gestion des Menus**

#### a) `setupMenuOptions()`
- **Rôle** :
  - Ajoute des options au menu principal (Jouer, Multijoueur, Infos, etc.).
  - Associe chaque option à une fonction lambda pour déclencher des actions spécifiques.

- **Exemple** :
    ```cpp
    m_menu->addOption("Play", [this]() { 
        m_game = std::make_unique<Game>(m_creatorIp, m_window, m_customMenu->getSelectedSkin(), m_font, *m_playingBackground, m_soundManager);
        m_currentState = GameState::Playing;
    });
    ```

#### b) `handleEvents()`
- **Rôle** :
  - Gère les événements clavier et souris.
  - Permet de naviguer entre les différents états (`Menu`, `Options`, `Infos`, etc.).

- **Exemple** :
    ```cpp
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        m_currentState = (m_currentState == GameState::Menu) ? GameState::Playing : GameState::Menu;
    }
    ```

---

### 4. **Boucle Principale**

#### a) `run()`
- **Rôle** :
  - Maintient la fenêtre ouverte et exécute la boucle de jeu tant qu'elle n'est pas fermée.
  - Appelle les méthodes `handleEvents`, `update`, et `render`.

- **Exemple** :
    ```cpp
    while (m_window.isOpen()) {
        float deltaTime = m_clock.restart().asSeconds();
        handleEvents();
        update(deltaTime);
        render(deltaTime);
    }
    ```

---

### 5. **Mise à Jour des États**

#### a) `update(float deltaTime)`
- **Rôle** :
  - Met à jour les arrière-plans, les animations et les menus en fonction de l'état courant (`GameState`).
  - Gère les transitions comme le passage à un nouveau niveau.

- **Exemple : Animation de Transition**
    ```cpp
    if (m_game->AnimationLevel()) {
        m_currentState = GameState::AnimationLevelGame;
        m_animationTime = 0.0f;
    }
    ```

---

### 6. **Rendu Graphique**

#### a) `render(float deltaTime)`
- **Rôle** :
  - Efface l'écran, puis affiche les éléments en fonction de l'état courant.
  - Appelle les méthodes de rendu des menus, du jeu et des animations.

- **Exemple : Rendu des Popups**
    ```cpp
    if (m_showPopup) {
        renderPopup();
    }
    ```

#### b) `renderAnimationNewFile()`
- **Rôle** :
  - Affiche un message d'animation pour signaler une nouvelle vague d'ennemis.
  
- **Exemple** :
    ```cpp
    sf::Text centerText;
    centerText.setFont(m_font);
    centerText.setString("Wave: " + std::to_string(level));
    centerText.setCharacterSize(50);
    centerText.setPosition(windowSize.x / 2, windowSize.y / 2);
    ```

---

### 7. **Popups**

#### a) `triggerPopup(const std::string& spritePath, const std::string& message)`
- **Rôle** :
  - Affiche une notification temporaire avec une image et un message.

- **Exemple** :
    ```cpp
    triggerPopup("./assets/powerup.png", "Power-Up Collected!");
    ```

---

## **Conclusion**

La classe `Engine` agit comme le chef d'orchestre du jeu en reliant toutes les fonctionnalités principales :
- Gestion des états (`GameState`).
- Initialisation et rendu des arrière-plans, menus et animations.
- Communication avec la classe `Game` pour le déroulement des parties.

---

## **Sprite Manager**


## **Introduction**

La classe `SpriteManager` est un composant clé qui gère les entités graphiques (`Sprite`) dans le jeu. Elle s'occupe de leur ajout, suppression, mise à jour, et affichage, tout en intégrant des animations spécifiques comme les explosions lors de la destruction d'entités.

---

## **Méthodes Principales**

### 1. **Constructeur**

```cpp
SpriteManager()
```

- **Rôle** :
  - Initialise le gestionnaire d'animations de mort (`DeathAnimation`).
  - Charge les ressources nécessaires pour les explosions.

- **Exemple** :
  ```cpp
  m_deathAnimation.initialize("../../client/assets/explosions/", 7, 20.f);
  ```
  - Initialise les animations d'explosion avec :
    - Le chemin vers les assets.
    - Le nombre d'étapes de l'animation.
    - La vitesse de l'animation (20.0f ici).

---

### 2. **Ajout de Sprite**

```cpp
void addSprite(const std::shared_ptr<Sprite> &sprite, std::size_t id)
```

- **Rôle** :
  - Ajoute un sprite à la collection `_mapSprite` en l'associant à un identifiant unique.

- **Exemple** :
  ```cpp
  spriteManager.addSprite(std::make_shared<Sprite>("path/to/sprite.json"), 1);
  ```

---

### 3. **Suppression de Sprite**

```cpp
void removeSprite(std::size_t id)
```

- **Rôle** :
  - Supprime un sprite par son identifiant.
  - Déclenche une animation d'explosion si le sprite est de type `Enemy` ou `Player`.

- **Exemple** :
  ```cpp
  spriteManager.removeSprite(1);
  ```

- **Animation lors de la suppression** :
  ```cpp
  if (it->second->getType() == Type::Enemy || it->second->getType() == Type::Player) {
      triggerDeathAnimation(it->second->getPosition());
  }
  ```

---

### 4. **Affichage de Tous les Sprites**

```cpp
void drawAll(sf::RenderWindow &window, sf::Time deltaTime)
```

- **Rôle** :
  - Parcourt tous les sprites pour les mettre à jour et les dessiner.
  - Met à jour et rend les animations d'explosion.

- **Exemple** :
  ```cpp
  spriteManager.drawAll(window, deltaTime);
  ```

- **Code Interne** :
  ```cpp
  for (const auto &[id, sprite] : _mapSprite) {
      sprite->update(deltaTime);
      sprite->draw(window);
  }
  ```

---

### 5. **Récupération d'un Sprite**

```cpp
std::shared_ptr<Sprite> getSprite(std::size_t id) const
```

- **Rôle** :
  - Retourne un pointeur partagé vers un sprite identifié par son `id`.
  - Retourne `nullptr` si le sprite n'existe pas.

- **Exemple** :
  ```cpp
  auto sprite = spriteManager.getSprite(1);
  if (sprite) {
      std::cout << "Sprite trouvé !";
  }
  ```

---

### 6. **Comptage des Sprites**

```cpp
std::size_t getSpriteCount() const
```

- **Rôle** :
  - Retourne le nombre total de sprites gérés par le `SpriteManager`.

- **Exemple** :
  ```cpp
  std::cout << "Nombre de sprites : " << spriteManager.getSpriteCount() << std::endl;
  ```

---

### 7. **Suppression des Sprites Obsolètes**

```cpp
void eraseOldSprite(std::unordered_set<std::size_t> &container)
```

- **Rôle** :
  - Supprime tous les sprites dont les identifiants ne sont pas présents dans le conteneur fourni.
  - Déclenche une animation d'explosion pour les sprites supprimés.

- **Exemple** :
  ```cpp
  std::unordered_set<std::size_t> activeSprites = {1, 2};
  spriteManager.eraseOldSprite(activeSprites);
  ```

---

### 8. **Suppression de Tous les Sprites**

```cpp
void eraseAll()
```

- **Rôle** :
  - Supprime tous les sprites gérés par le `SpriteManager`.

- **Exemple** :
  ```cpp
  spriteManager.eraseAll();
  ```

---

### 9. **Animation de Mort**

#### a) `triggerDeathAnimation(const sf::Vector2f& position)`

- **Rôle** :
  - Déclenche une animation d'explosion à une position donnée.
  - Utilise un système cyclique pour gérer plusieurs animations en parallèle.

- **Exemple** :
  ```cpp
  triggerDeathAnimation({100.0f, 200.0f});
  ```

- **Code Interne** :
  ```cpp
  m_deathAnimation.triggerAnimation(animationIndex);
  m_deathAnimation.setAnimationPosition(position);
  animationIndex = (animationIndex + 1) % 10;
  ```

---

## **Conclusion**

La classe `SpriteManager` offre une gestion centralisée et efficace des sprites, simplifiant leur mise à jour, affichage et suppression. Elle intègre des animations dynamiques pour améliorer l'expérience visuelle, comme les explosions lors de la suppression d'entités. Cette modularité permet de facilement étendre les fonctionnalités ou d'intégrer de nouveaux comportements.

---

## **Sound Manager**


## **Introduction**

La classe `SoundManager` gère la musique et les effets sonores dans le jeu. Elle permet de charger, jouer, mettre en pause ou arrêter des morceaux de musique ou des sons individuels. De plus, elle offre un contrôle granulaire sur le volume et la répétition des pistes.

---

## **Méthodes Principales**

### 1. **Constructeur**

```cpp
SoundManager()
```

- **Rôle** : Initialise les structures nécessaires pour gérer les musiques et les sons.

- **Exemple** :
  ```cpp
  SoundManager soundManager;
  ```

---

### 2. **Chargement de Musique**

```cpp
bool loadMusic(const std::string& key, const std::string& musicFile)
```

- **Rôle** :
  - Charge un fichier audio en mémoire sous forme de musique.
  - Associe la musique à une clé pour un accès futur.

- **Exemple** :
  ```cpp
  if (!soundManager.loadMusic("background", "./assets/music/background.mp3")) {
      std::cerr << "Failed to load background music!" << std::endl;
  }
  ```

---

### 3. **Lecture de Musique**

```cpp
bool playMusic(const std::string& key, bool loop = false)
```

- **Rôle** :
  - Joue la musique associée à une clé.
  - Permet de définir si la musique doit boucler (`loop`).

- **Exemple** :
  ```cpp
  soundManager.playMusic("background", true);
  ```

- **Comportement** :
  - Stoppe la musique si elle est déjà en lecture avant de la rejouer.

---

### 4. **Pause de Musique**

```cpp
void pauseMusic(const std::string& key)
```

- **Rôle** :
  - Met en pause une musique en cours de lecture.

- **Exemple** :
  ```cpp
  soundManager.pauseMusic("background");
  ```

---

### 5. **Arrêt de Musique**

```cpp
void stopMusic(const std::string& key)
```

- **Rôle** :
  - Stoppe complètement une musique.

- **Exemple** :
  ```cpp
  soundManager.stopMusic("background");
  ```

---

### 6. **Arrêt de Toutes les Musiques**

```cpp
void stopAllMusic()
```

- **Rôle** :
  - Stoppe toutes les musiques en cours de lecture.

- **Exemple** :
  ```cpp
  soundManager.stopAllMusic();
  ```

---

### 7. **Réglage du Volume de Musique**

```cpp
void setMusicVolume(const std::string& key, float volume)
```

- **Rôle** :
  - Définit le volume d'une musique spécifique.

- **Exemple** :
  ```cpp
  soundManager.setMusicVolume("background", 50.0f);
  ```

---

### 8. **Réglage Global du Volume**

```cpp
void setAllMusicVolume(float volume)
```

- **Rôle** :
  - Ajuste le volume de toutes les musiques.

- **Exemple** :
  ```cpp
  soundManager.setAllMusicVolume(30.0f);
  ```

---

### 9. **Chargement de Son**

```cpp
bool loadSound(const std::string& key, const std::string& soundFile)
```

- **Rôle** :
  - Charge un fichier sonore en mémoire et l’associe à une clé.

- **Exemple** :
  ```cpp
  if (!soundManager.loadSound("shoot", "./assets/sounds/shoot.wav")) {
      std::cerr << "Failed to load shoot sound!" << std::endl;
  }
  ```

---

### 10. **Lecture de Son**

```cpp
bool playSound(const std::string& key, bool loop = false)
```

- **Rôle** :
  - Joue un son associé à une clé.
  - Permet de boucler le son si nécessaire.

- **Exemple** :
  ```cpp
  soundManager.playSound("shoot", false);
  ```

---

### 11. **Arrêt de Tous les Sons**

```cpp
void stopAllSounds()
```

- **Rôle** :
  - Stoppe tous les sons actuellement en lecture.

- **Exemple** :
  ```cpp
  soundManager.stopAllSounds();
  ```

---

### 12. **Nettoyage des Sons**

```cpp
void cleanupSounds()
```

- **Rôle** :
  - Supprime de la mémoire les sons qui ont terminé leur lecture.

- **Exemple** :
  ```cpp
  soundManager.cleanupSounds();
  ```

- **Code Interne** :
  ```cpp
  _activeSounds.erase(
      std::remove_if(
          _activeSounds.begin(),
          _activeSounds.end(),
          [](sf::Sound& sound) { return sound.getStatus() == sf::Sound::Stopped; }
      ),
      _activeSounds.end()
  );
  ```

---

## **Conclusion**

Le `SoundManager` fournit une gestion efficace des musiques et sons pour le jeu. Il permet de centraliser le contrôle des fichiers audio et de leur lecture tout en offrant des fonctionnalités avancées comme le réglage du volume, la boucle, et le nettoyage des sons inactifs.
---

## **Lobby TCP**


## **Introduction**

La classe `TcpClient` est une abstraction pour gérer les connexions TCP entre le client et le serveur. Elle utilise la bibliothèque **Asio** pour offrir une communication réseau asynchrone. Cette classe est essentielle pour échanger des messages avec le serveur, qu'il s'agisse de données de jeu, d'instructions ou de synchronisation.

---

## **Méthodes Principales**

### 1. **Constructeur**

```cpp
TcpClient(const std::string& host, const std::string& port);
```

- **Rôle** :
  - Initialise le client TCP.
  - Résout l'adresse et le port fournis, puis établit une connexion au serveur.

- **Exemple** :
  ```cpp
  NmpClient::TcpClient client("127.0.0.1", "8080");
  ```

- **Comportement** :
  - En cas de succès, affiche un message :
    ```
    Connecté au serveur TCP 127.0.0.1:8080
    ```
  - Si la connexion échoue, une exception sera levée.

---

### 2. **Méthode `send`**

```cpp
void send(const std::string& message);
```

- **Rôle** :
  - Envoie un message sous forme de chaîne de caractères au serveur via la connexion TCP.

- **Exemple** :
  ```cpp
  client.send("Hello, server!");
  ```

- **Sortie** :
  - Affiche le message envoyé :
    ```
    Message envoyé : Hello, server!
    ```

---

### 3. **Méthode `receive`**

```cpp
std::optional<std::string> receive();
```

- **Rôle** :
  - Attend et lit les données envoyées par le serveur.
  - Retourne les données sous forme de chaîne de caractères si la réception réussit.

- **Exemple** :
  ```cpp
  auto response = client.receive();
  if (response) {
      std::cout << "Réponse du serveur : " << response.value() << std::endl;
  } else {
      std::cerr << "Erreur de réception" << std::endl;
  }
  ```

- **Comportement** :
  - En cas de réception réussie, retourne un `std::string` contenant les données.
  - Si une erreur survient, retourne `std::nullopt` et affiche un message :
    ```
    Erreur lors de la réception : [Description de l'erreur]
    ```

---

### **Structure et Utilisation**

#### **Attributs Privés**

1. **`_io_context`** :
   - Objet de gestion des opérations d'entrée/sortie.
   - Nécessaire pour l'exécution des tâches réseau Asio.

2. **`_socket`** :
   - Socket TCP pour la communication avec le serveur.

3. **`_resolver`** :
   - Utilisé pour résoudre l'adresse et le port du serveur.

---

## **Exemple Complet**

Voici un exemple complet d'utilisation de la classe `TcpClient` :

```cpp
#include "TcpClient.hpp"

int main() {
    try {
        // Initialisation du client
        NmpClient::TcpClient client("127.0.0.1", "8080");

        // Envoi d'un message au serveur
        client.send("Hello, server!");

        // Réception d'une réponse
        auto response = client.receive();
        if (response) {
            std::cout << "Réponse du serveur : " << response.value() << std::endl;
        } else {
            std::cerr << "Erreur de réception" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }

    return 0;
}
```

---

## **Avantages et Limites**

### **Avantages**
- **Simplicité** : Interface facile à utiliser pour gérer les connexions TCP.
- **Flexibilité** : Peut s'adapter à différents serveurs en modifiant l'adresse et le port.
- **Gestion des erreurs** : Utilise `std::optional` pour signaler les échecs.

### **Limites**
- Pas encore asynchrone : Les opérations `send` et `receive` bloquent jusqu'à leur complétion.
- Taille fixe du tampon de réception (1024 octets).

---

## **Améliorations Futures**

1. **Support Asynchrone** :
   - Intégrer des fonctionnalités asynchrones avec des `async_write` et `async_read_some`.

2. **Tampon Dynamique** :
   - Permettre la gestion de tampons de tailles dynamiques pour les données volumineuses.

3. **Reconnexion Automatique** :
   - Ajouter une logique pour gérer les pertes de connexion.

---

## **Conclusion**

La classe `TcpClient` est un composant fondamental pour la gestion des communications réseau dans un environnement client-serveur. Elle simplifie la connexion, l'envoi et la réception de données tout en gérant les erreurs courantes de manière robuste.

---

## **Gestion du Jeu (`Game`)**


## **Introduction**

La classe `Game` est le cœur de la logique de jeu. Elle orchestre l'affichage, la mise à jour, et les interactions entre les différents composants du jeu, tels que les joueurs, les ennemis, et l'arrière-plan. Cette classe utilise SFML pour le rendu graphique et gère les états du jeu.

---

## **Méthodes Principales**

### **1. Constructeur et Destructeur**

#### **Constructeur**

```cpp
Game(std::string ip, sf::RenderWindow &window, SkinType skinType, sf::Font &font, ParallaxBackground &playingBackground, SoundManager &soundManager);
```

- **Rôle** :
  - Initialise les composants principaux du jeu :
    - Connexion client via l'adresse IP.
    - Gestion de l'arrière-plan parallax.
    - Initialisation des éléments de jeu (vie, score, niveau).

- **Exemple** :
  ```cpp
  Game game("127.0.0.1", window, SkinType::SKIN1, font, playingBackground, soundManager);
  ```

#### **Destructeur**

```cpp
~Game();
```

- **Rôle** :
  - Libère les ressources utilisées par les ennemis et les tirs.

- **Comportement** :
  - Efface les vecteurs `m_enemies` et `m_shoots`.

---

### **2. Gestion des Événements**

#### **`handleEvents`**

```cpp
void handleEvents();
```

- **Rôle** :
  - Gère les événements SFML, tels que la fermeture de la fenêtre.

- **Exemple** :
  - Si un événement de fermeture est détecté :
    ```cpp
    if (event.type == sf::Event::Closed) {
        m_window.close();
    }
    ```

---

### **3. Mise à Jour**

#### **`update`**

```cpp
void update(float deltaTime);
```

- **Rôle** :
  - Met à jour les composants du jeu :
    - Gestion des entrées utilisateur via `m_players.handleInput()`.
    - Envoie des mouvements en attente au serveur via `m_players.sendQueuedMovements()`.
    - Met à jour l'arrière-plan parallax.

- **Exemple** :
  ```cpp
  m_players.handleInput();
  m_players.sendQueuedMovements();
  m_playingBackground.update(deltaTime);
  ```

---

### **4. Animation des Niveaux**

#### **`AnimationLevelGame`**

```cpp
bool AnimationLevelGame();
```

- **Rôle** :
  - Vérifie si un changement de niveau du jeu (niveau global) a eu lieu.

- **Comportement** :
  - Si le niveau global change, retourne `true` et met à jour `m_level_previous_game`.

- **Exemple** :
  ```cpp
  if (m_level_game != m_level_previous_game) {
      m_level_previous_game = m_level_game;
      return true;
  }
  return false;
  ```

---

#### **`AnimationLevel`**

```cpp
bool AnimationLevel();
```

- **Rôle** :
  - Vérifie si un changement de niveau du joueur (3, 4, 5 ou 6) a eu lieu.

- **Comportement** :
  - Si un changement est détecté pour un niveau spécifique, retourne `true` et met à jour `m_previousLevel`.

- **Exemple** :
  ```cpp
  if (currentLevel != m_previousLevel && (currentLevel == 3 || currentLevel == 4 || currentLevel == 5 || currentLevel == 6)) {
      m_previousLevel = currentLevel;
      return true;
  }
  ```

---

### **5. Rendu**

#### **`render`**

```cpp
void render(float deltaTime);
```

- **Rôle** :
  - Affiche les différents composants du jeu :
    - Arrière-plan parallax.
    - Sprites des entités (joueurs, ennemis, etc.).
    - Interface utilisateur (vie, score, niveau).

- **Exemple** :
  ```cpp
  m_playingBackground.render(m_window);
  _spriteMng.drawAll(m_window, sf::seconds(deltaTime));
  m_life.render(m_window);
  m_score.render(m_window);
  m_level.render(m_window);
  ```

---

## **Composants Internes**

### **1. Gestion des Joueurs**

- `m_players.handleInput()` :
  - Gère les entrées clavier des joueurs.

- `m_players.sendQueuedMovements()` :
  - Envoie les mouvements accumulés au serveur.

---

### **2. Gestion de l'Arrière-Plan**

- `m_playingBackground.update(deltaTime)` :
  - Met à jour les différentes couches de l'arrière-plan.

- `m_playingBackground.render(m_window)` :
  - Affiche les couches de l'arrière-plan dans la fenêtre.

---

### **3. Interface Utilisateur**

- **Vie** :
  - Gérée via l'objet `m_life`.
  - Affichage des icônes de vie (pleine, moyenne, faible).

- **Score** :
  - Géré via l'objet `m_score`.
  - Affichage du score dans la fenêtre.

- **Niveau** :
  - Géré via l'objet `m_level`.
  - Indique le niveau actuel du joueur.

---

## **Exemple Complet**

Voici un exemple de boucle de jeu avec la classe `Game` :

```cpp
#include "Game.hpp"
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "R-Type");
    sf::Font font;
    font.loadFromFile("./assets/fonts/ZenDots-Regular.ttf");

    ParallaxBackground playingBackground(window.getSize(), {{"./assets/background.png", 0.1f}});
    SoundManager soundManager;

    Game game("127.0.0.1", window, SkinType::SKIN1, font, playingBackground, soundManager);

    sf::Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        game.handleEvents();
        game.update(deltaTime);
        game.render(deltaTime);
    }

    return 0;
}
```

---

## **Conclusion**

La classe `Game` centralise la logique principale du jeu. Elle interagit avec les joueurs, les ennemis, les arrières-plans et l'interface utilisateur. Grâce à son architecture modulaire, elle permet d'ajouter ou de modifier des fonctionnalités sans affecter les autres composants.

---

## **Conclusion**

Ce document décrit les principaux composants du client et leur rôle dans le jeu. Si vous avez des questions ou rencontrez des problèmes, veuillez consulter les exemples de code fournis ou la documentation associée.

Souhaites-tu approfondir une section en particulier ou ajouter des détails supplémentaires ? 😊
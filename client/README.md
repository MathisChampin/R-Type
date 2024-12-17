# Documentation du Client

---

## **Introduction**

Cette documentation concerne exclusivement la partie client du projet **R-Type**. Le client est responsable de la communication avec le serveur pour envoyer et recevoir des données. Il utilise la bibliothèque `asio` pour gérer la communication réseau via UDP.

---

## **Classes et Méthodes**

### **Classe `Client`**

La classe **`Client`** est la base de la communication avec le serveur.

---

### **Constructeur**

#### **`Client::Client()`**

Le constructeur initialise :

1. **Le résolveur** pour trouver l'adresse du serveur.
2. **Le socket UDP** pour établir la communication.
3. Résout l'adresse du serveur et ouvre le socket.

---

### **Méthodes**

#### **`get_data`**

```cpp
std::optional<Packet> Client::get_data()
```

**Description :**  
Cette méthode reçoit les données envoyées par le serveur.  

**Fonctionnement :**
- Utilise le socket pour recevoir les données dans un buffer.
- Désérialise les données reçues en un objet `Packet`.
- Si des données sont reçues, retourne un `std::optional<Packet>` contenant le paquet, sinon retourne `std::nullopt`.

---

#### **`send_input`**

```cpp
void Client::send_input(Packet &packet)
```

**Description :**  
Cette méthode envoie des données au serveur.  

**Fonctionnement :**
- Sérialise le paquet (`Packet`) dans un buffer.
- Envoie ce buffer au serveur via le socket.
- Vide le buffer après l'envoi.

---

### **Classe `Game`**

La classe **`Game`** gère la boucle principale du jeu, y compris l'initialisation, la gestion des événements, la mise à jour et le rendu.

---

### **Constructeur**

#### **`Game::Game()`**

Le constructeur initialise :

1. **La fenêtre de rendu** pour afficher le jeu.
2. **Les polices** pour le texte affiché.
3. **Les options du menu** pour naviguer dans le jeu.
4. **L'adresse IP** pour la connexion au serveur.

---

### **Méthodes**

#### **`run`**

```cpp
void Game::run()
```

**Description :**  
Cette méthode lance la boucle principale du jeu.

---

#### **`handleEvents`**

```cpp
void Game::handleEvents()
```

**Description :**  
Cette méthode gère les événements de la fenêtre.  

**Fonctionnement :**
- Traite les entrées utilisateur.
- Délègue la gestion des événements aux menus spécifiques.

---

#### **`update`**

```cpp
void Game::update(float deltaTime)
```

**Description :**  
Cette méthode met à jour les composants du jeu en fonction de l'état actuel.  

**Fonctionnement :**
- Met à jour les joueurs et les ennemis.
- Met à jour les arrière-plans.

---

#### **`render`**

```cpp
void Game::render()
```

**Description :**  
Cette méthode rend les composants du jeu à l'écran.  

**Fonctionnement :**
- Efface la fenêtre.
- Rend les joueurs, les ennemis et les arrière-plans.
- Affiche le contenu rendu.

---

### **Communication entre le Client et le Serveur**

La communication entre le client et le serveur se fait principalement dans la classe `Game`. Voici comment cela fonctionne :

#### **Réception des données**

***Player***
```cpp
void Game::get_player()
```

**Description :**  
Cette méthode reçoit les données des joueurs envoyées par le serveur.

**Fonctionnement :**
- Utilise la méthode `get_data` de la classe `Client` pour recevoir les paquets.
- Met à jour les positions des joueurs en fonction des données reçues.

***Ennemies***
```cpp
void Game::get_ennemies()
```

**Description :**  
Cette méthode reçoit les données des ennemis envoyées par le serveur.

**Fonctionnement :**
- Utilise la méthode `get_data` de la classe `Client` pour recevoir les paquets.
- Met à jour les positions des ennemis en fonction des données reçues.

***Shoot***

```cpp
void Game::get_shoot()
```

**Description :**  
Cette méthode reçoit les données des tirs envoyées par le serveur.

**Fonctionnement :**
- Utilise la méthode `get_data` de la classe `Client` pour recevoir les paquets.
- Met à jour les positions des joueurs en fonction des données reçues.

#### **Envoi des données**

```cpp
void Player::sendMovementPacket(NmpClient::DIRECTION direction)
```

**Description :**  
Cette méthode envoie les données de mouvement des joueurs au serveur.

**Fonctionnement :**
- Crée un paquet (`Packet`) avec la direction du mouvement.
- Utilise la méthode `send_input` de la classe `Client` pour envoyer le paquet au serveur.

---

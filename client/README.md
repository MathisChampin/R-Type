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

**Fonctionnement :**
- Gère les événements.
- Met à jour les composants du jeu.
- Rend les composants du jeu.

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

## **Gestion des Erreurs**

Le client inclut des mécanismes pour gérer les erreurs de réception et d'envoi de paquets.

#### **Réception des Paquets**

Lors de la réception des paquets, le client utilise un bloc `try-catch` pour capturer les exceptions :

```cpp
std::optional<Packet> Client::get_data()
{
    try {
        std::size_t bytes = _socket.receive_from(asio::buffer(_bufferAsio), clientEndpoint, 0, ignored_error);
        if (bytes > 0) {
            // Traitement des données reçues
        }
    } catch (const std::system_error& e) {
        std::cerr << "Erreur lors de la réception des données : " << e.what() << std::endl;
        return std::nullopt;
    }
    return std::nullopt;
}
```

#### **Envoi des Paquets**

De même, lors de l'envoi des paquets, les erreurs sont capturées et journalisées :

```cpp
void Client::send_input(Packet &packet)
{
    try {
        _socket.send_to(asio::buffer(_bufferSerialize), _receiver_endpoint);
    } catch (const std::system_error& e) {
        std::cerr << "Erreur lors de l'envoi des données : " << e.what() << std::endl;
    }
}
```

Ces mécanismes permettent de garantir que le client continue de fonctionner même en cas d'erreurs de réseau.

---

## **Exemples de Code**

### **Initialisation du Client**

```cpp
NmpClient::Client client;
```

---

### **Envoi de Données**

```cpp
NmpClient::Packet packet(NmpClient::EVENT::MOVE, spriteInfo);
client.send_input(packet);
```

---

### **Réception de Données**

```cpp
auto data = client.get_data();
if (data.has_value()) {
    // Traiter les données reçues
}
```

---

## **Conclusion**

La classe **`Client`** simplifie la communication réseau avec le serveur en utilisant la bibliothèque `asio`. Elle gère automatiquement :
- La **sérialisation** et la **désérialisation** des données via les objets `Packet`.
- L'envoi et la réception des données.  

La classe **`Game`** gère la boucle principale du jeu, y compris l'initialisation, la gestion des événements, la mise à jour et le rendu. Cette interface permet une interaction fluide et efficace entre le client et le serveur dans le cadre du projet **R-Type**.
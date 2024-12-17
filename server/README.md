# **Documentation du Serveur R-Type**

---

## **Introduction**

Cette documentation concerne exclusivement la partie serveur du projet **R-Type**. Le serveur est responsable de :

- La gestion de la logique du jeu.
- La synchronisation des états entre les clients.
- La communication réseau via le protocole **UDP**, avec la bibliothèque `asio`.

---

## **1. Classes et Méthodes**

### **1.1 Classe `Server`**

La classe **`Server`** gère les connexions réseau et la logique du jeu côté serveur.

#### **Constructeur**

```cpp
Server::Server()
```

**Fonctionnalité :**  
Initialise les composants nécessaires au bon fonctionnement du serveur :  
1. Le **contexte d'IO** pour les opérations d'entrée/sortie.  
2. Les **sockets UDP** pour la communication réseau.  
3. Le **gestionnaire de protocole** pour traiter les paquets.

#### **Méthodes**

1. **`run`**

```cpp
void Server::run()
```

- **Description :** Lance le serveur et démarre les threads nécessaires (gestion des entrées et système ECS).  
- **Fonctionnement :**  
   - Démarre les threads pour la gestion des entrées, update l'ecs, envoie des frames. 

   - Exécute la boucle principale du contexte d'IO.

1. **`get_data`**

```cpp
void Server::get_data()
```

- **Description :** Réception des données envoyées par les clients.  
- **Fonctionnement :**  
   - Récupère les données via le socket UDP.  
   - Désérialise les données en **paquets** (`Packet`).  
   - Ajoute les paquets à une file d'attente pour traitement.

3. **`send_data`**

```cpp
void Server::send_data(Packet &packet, asio::ip::udp::endpoint endpoint)
```

- **Description :** Envoie des données à un client.  
- **Fonctionnement :**  
   - Sérialise le paquet.  
   - Envoie le buffer via le socket UDP.  
   - Vide le buffer après l'envoi.

4. **`systemLoop`**

```cpp
void Server::systemLoop()
```

- **Description :** Boucle principale du système ECS.  
- **Fonctionnement :**  
   - Met à jour les systèmes ECS (position, collision, etc.).  
   - Envoie les états des entités aux clients.

### **1.2 Classe `ProtocoleHandler`**

La classe **`ProtocoleHandler`** gère la logique du jeu et traite les paquets reçus.

#### **Constructeur**

```cpp
ProtocoleHandler::ProtocoleHandler(Server &server)
```

**Fonctionnalité :** Initialise le gestionnaire de protocole :  
1. Référence au serveur pour les échanges réseau.  
2. Le registre ECS pour la gestion des entités et des composants.

#### **Méthodes**

1. **`executeOpCode`**

```cpp
void ProtocoleHandler::executeOpCode()
```

- **Description :** Exécute la logique associée au code d'opération d'un paquet.

2. **`evalJoin`**

```cpp
void ProtocoleHandler::evalJoin()
```

- **Description :** Gère la logique de connexion d'un joueur.

3. **`evalMove`**

```cpp
void ProtocoleHandler::evalMove()
```

- **Description :** Gère la logique de déplacement d'un joueur.

4. **`evalQuit`**

```cpp
void ProtocoleHandler::evalQuit()
```

- **Description :** Gère la logique de déconnexion d'un joueur.

### **1.3 Classe `Binary`**

La classe **`Binary`** gère la sérialisation et la désérialisation des paquets.

#### **Méthodes**

1. **`serialize`**

```cpp
void Binary::serialize(Packet &packet, std::vector<uint32_t> &buffer)
```

- **Description :** Sérialise un paquet en un buffer de données.

2. **`deserialize`**

```cpp
Packet Binary::deserialize(std::vector<uint32_t> &buffer)
```

- **Description :** Désérialise un buffer de données en un paquet.

### **1.4 Classe `Packet`**

Les objets **`Packet`** encapsulent les données échangées entre le client et le serveur.

#### **Constructeurs**

1. **Avec identifiant et événement :**

```cpp
Packet(std::size_t id, EVENT event, std::optional<Key> key = std::nullopt)
```

2. **Avec coordonnées :**

```cpp
Packet(EVENT event, int x, int y)
```

3. **Avec sprite :**

```cpp
Packet(EVENT event, SpriteInfo &sprites)
```

---

## **2. Communication Réseau**

Le serveur utilise **UDP** pour envoyer et recevoir des données.
Il envoie de maniére régulière les entités présentes dans l'ecs

### **2.1 Transmission des Frames**

- **Fréquence :** Envoi régulier des états ECS à chaque client via le thread systemLoop.  
- **Fonctionnement :** Les sprites sont représentés par une série de 6 infos **(SPRITE)**.  

### **Événements principaux :**
- **`idclient`** : Position dans l'ecs.  
- **`id`** : Id de l'entité (joueur, ennemi, tir).  
- **`x`** : Position x.  
- **`y`** : Position y.
- **`sizeX`** : Taille sprite x.
- **`sizey`** : Taille sprite y.

### **2.1 Transmission des Evénements Clients**

- **Fréquence :** Envoie a chaque entrée clavier d'un client la touche au serveur.  
- **Fonctionnement :** 
- Les événements sont représentés par des codes d'opération **(EVENT)**.  

### **Événements principaux :**
- **`MOVE`** : Déplacement.  
- **`SHOOT`** : Tir.  
- **`QUIT`** : Déconnexion.  
- **`JOIN`** : Connexion d'un joueur.

4. **Key**

Les touches sont représentés par des codes distinct **(KEY)**.  

### **Touches :**
- **`RIGHT`** : Fleche de droite.  
- **`LEFT`** : Fleche de gauche.  
- **`UP`** : Fleche du haut.  
- **`DOWN`** : Fleche du bas.
- **`SHOOT`** : Bar espace.



---

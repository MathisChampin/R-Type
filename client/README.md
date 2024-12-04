### Documentation du Client

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
void Client::get_data()
```

**Description :**  
Cette méthode reçoit les données envoyées par le serveur.  

**Fonctionnement :**
- Utilise le socket pour recevoir les données dans un buffer.
- Désérialise les données reçues en un objet `Packet`.
- Si le paquet est un événement de type `MOVE`, affiche un message dans la console.

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
client.get_data();
```

---

## **Conclusion**

La classe **`Client`** simplifie la communication réseau avec le serveur en utilisant la bibliothèque `asio`. Elle gère automatiquement :
- La **sérialisation** et la **désérialisation** des données via les objets `Packet`.
- L'envoi et la réception des données.  

Cette interface permet une interaction fluide et efficace entre le client et le serveur dans le cadre du projet **R-Type**.
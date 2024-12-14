### Documentation : Partie Serveur

#### **Objectif Général**
Le serveur dans votre projet R-Type est la pierre angulaire de la communication réseau et de la synchronisation des états entre les **clients**, le **moteur ECS** et les entités du jeu. Il gère les interactions réseau via des threads séparés pour la réception, le traitement, et l'envoi des paquets, tout en s'assurant de maintenir une cohérence dans l'état global du jeu.

---

### **1. Structure du Serveur**
Le serveur est basé sur une architecture multi-threadée avec deux sockets distinctes :
1. **Socket d'écoute (`socketRead`) :**
   - Adresse : `localhost:8080`
   - Utilisée pour recevoir les paquets des clients.

2. **Socket d'envoi (`socketSend`) :**
   - Adresse : `localhost:8081`
   - Utilisée pour envoyer les réponses et mises à jour aux clients.

---

### **2. Synchronisation des Threads**
Le serveur utilise une queue pour gérer les paquets entrants et sortants :
1. **Thread d’entrée (`threadInput`) :**
   - Lit les paquets des clients via `socketRead.receive_from()`.
   - Pousse les paquets dans une **queue** partagée.

2. **Thread de traitement (`threadEcs`) :**
   - Récupère les paquets de la queue avec `queue.pop()`.
   - Traite chaque paquet avec le gestionnaire de protocole (`ProtocoleHandler`) :
     - Identifie l'action via l'OpCode.
     - Met à jour l'état dans l'ECS.

3. **Thread d’envoi (optionnel) :**
   - Une fois les paquets traités, ils peuvent être placés dans une autre queue dédiée aux réponses.
   - Ce thread extrait les paquets de réponse et les envoie via `socketSend`.

---

### **3. Gestion des Paquets**
La communication est basée sur des **opcodes** pour définir les actions possibles. Les paquets sont sérialisés et désérialisés via la classe **Binary** :
- **Classes principales :**
  - **`Packet` :** Représente un paquet échangé entre client et serveur.
    - **`Packet1`** : Créé par le client (id + opcode + option).
    - **`Packet2`** : Réponse du serveur (opcode + coordonnées x, y).
    - **`Packet3`** : Informations visuelles pour l'affichage (sprites).
  - **`Binary` :** Convertit les paquets en données binaires pour l’envoi réseau.

- **Enums des OpCodes :**
  - **`MOVE`** : Déplacement d’un joueur.
  - **`SHOOT`** : Tirs d’un joueur.
  - **`JOIN`** : Connexion d’un joueur.
  - **`SPRITE`** : Mises à jour des entités visuelles.

---

### **4. Fonctionnement de la Communication**
#### **Réception (client vers serveur) :**
1. Le client envoie ses entrées (`MOVE`, `SHOOT`, etc.) via `socketSend`.
2. Le serveur reçoit ces données dans le thread `threadInput`, qui les place dans une queue.

#### **Traitement (serveur) :**
1. Le thread `threadEcs` extrait les paquets de la queue.
2. Les paquets sont interprétés via **ProtocoleHandler** :
   - Par exemple, un paquet `MOVE` met à jour la vélocité du joueur dans l’ECS.

#### **Envoi (serveur vers client) :**
1. Le serveur génère des réponses (e.g., nouvelles positions) après le traitement.
2. Les réponses sont envoyées aux clients via `socketSend`.

---

### **5. Points à Améliorer**
1. **Fiabilité UDP :**
   - Intégrer un système d’acquittement (ACK) pour garantir la réception des paquets critiques.
   - Gérer la perte de paquets via une logique de retransmission.

2. **Optimisation des threads :**
   - Éviter l’utilisation de `async` inutile (deux sockets distinctes suffisent).
   - Utiliser des queues dédiées pour les réponses pour un traitement plus fluide.

3. **Amélioration du protocole :**
   - Ajouter des champs spécifiques pour gérer des cas comme les collisions.
   - Réduire la taille des paquets (optimisation de la sérialisation).

4. **Commandes client :**
   - Ajouter une queue de commandes côté client pour gérer localement les entrées avant envoi.

---

### **6. Exemple de Workflow**
#### **Connexion d’un client :**
1. Le client envoie un paquet `JOIN` :  
   ```cpp
   Packet1(42, EVENT::JOIN);
   ```
2. Le serveur traite la demande et renvoie :  
   ```cpp
   Packet2(EVENT::JOIN, x, y);
   ```

#### **Déplacement d’un joueur :**
1. Le client envoie un paquet `MOVE` avec une direction.  
   Exemple : `Packet1(id, MOVE, DIRECTION::UP)`
2. Le serveur met à jour la position dans l’ECS via `ProtocoleHandler`.

#### **Mise à jour des sprites :**
1. Le serveur envoie des informations visuelles (sprite positions).  
   Exemple : `Packet3(EVENT::SPRITE, spriteInfo)`

---

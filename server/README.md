# **Documentation Server**

### Sommaire

1. **[Server](#1-server)**

2. **[Binary (SBinary)](#2-binary-sbinary)**

3. **[ProtocolHandler](#3-protocolhandler)**

4. **[ProceduralLevel](#4-procedurallevel)**

5. **[Parser](#5-parser)**

6. **[Packet](#6-packet)**

7. **[LobbyServerTCP](#7-lobbyservertcp)**

---

### **1. Server**

---

### **1. `Server::Server(const Difficulty difficulty, const bool friendlyFire)`**
#### Description :
Le constructeur de la classe `Server` initialise les attributs du serveur, configure les sockets UDP pour la lecture et l'envoi de données, et génère un niveau de départ en fonction de la difficulté. Il charge également les données de configuration des ennemis et de leurs paramètres via un parser.

#### Exemple concret :
```cpp
Server server(Difficulty::Medium, true); // Création d'un serveur avec une difficulté moyenne et un tir amical activé.
```

---

### **2. `void Server::run()`**
#### Description :
La méthode `run()` démarre le serveur et lance plusieurs threads pour gérer différents aspects du jeu (logique du jeu, gestion des entrées, et évaluation des paquets entrants). Elle utilise la fonction `io_context.run()` pour exécuter le serveur en continu, et crée des threads pour gérer la logique du jeu et les entrées des clients de manière asynchrone.

#### Exemple concret :
```cpp
server.run(); // Démarre le serveur et exécute tous les threads nécessaires pour la gestion du jeu et des entrées.
```

---

### **3. `void Server::pauseThreads()`**
#### Description :
Cette méthode permet de mettre en pause tous les threads du serveur. Elle est utilisée lorsqu'il est nécessaire de suspendre temporairement l'exécution du serveur (par exemple, lors d'une pause du jeu).

#### Exemple concret :
```cpp
server.pauseThreads(); // Met en pause les threads du serveur pour suspendre les activités pendant un certain temps.
```

---

### **4. `void Server::resumeThreads()`**
#### Description :
Cette méthode reprend l'exécution des threads après une pause. Elle est appelée pour reprendre le traitement du serveur après avoir été mis en pause.

#### Exemple concret :
```cpp
server.resumeThreads(); // Reprend l'exécution des threads après une pause.
```

---

### **5. `void Server::send_data(Packet &packet, asio::ip::udp::endpoint endpoint)`**
#### Description :
Envoie un paquet de données à un client via un socket UDP. Le paquet est d'abord sérialisé dans un buffer avant d'être envoyé à l'endpoint du client. Cette méthode est utilisée pour envoyer des mises à jour et des informations sur l'état du jeu aux clients.

#### Exemple concret :
```cpp
Packet packet(EVENT::MOVE, 1, 100, 200); // Création d'un paquet MOVE pour le joueur 1 avec des coordonnées.
server.send_data(packet, endpoint); // Envoie le paquet à l'endpoint du joueur via UDP.
```

---

### **6. `void Server::broadcast(Packet &packet)`**
#### Description :
Cette méthode envoie un paquet de données à tous les joueurs connectés. Elle est utilisée pour diffuser des informations générales à l'ensemble des joueurs, comme les mises à jour de l'état du jeu ou la fin d'une partie.

#### Exemple concret :
```cpp
Packet packet(EVENT::INFO, 3, 100, 5); // Création d'un paquet contenant des informations de vie et de score.
server.broadcast(packet); // Diffuse ce paquet à tous les joueurs connectés.
```

---

### **7. `void Server::sendScoreLife(int i, component::state &st)`**
#### Description :
Envoie des informations sur la vie et le score d'un joueur spécifique à ce joueur. Si le joueur a perdu, la méthode met à jour le nombre de joueurs perdants. Elle utilise l'ID du joueur et son état actuel pour envoyer les bonnes informations.

#### Exemple concret :
```cpp
server.sendScoreLife(i, state); // Envoie les informations de score et de vie pour le joueur i.
```

---

### **8. `void Server::send_entity()`**
#### Description :
Envoie des entités du jeu (joueurs et ennemis) à tous les clients. Cette méthode itère sur toutes les entités vivantes et les envoie à chaque joueur via un paquet `SPRITE` contenant des informations sur la position et la taille de chaque entité.

#### Exemple concret :
```cpp
server.send_entity(); // Envoie toutes les entités du jeu (joueurs et ennemis) à tous les joueurs.
```

---

### **9. `bool Server::check_level_player(registry &_ecs)`**
#### Description :
Vérifie si un joueur a atteint un certain niveau (niveau 3 ou supérieur). Cette méthode est utilisée pour déterminer si le jeu doit progresser à un niveau supérieur, basé sur les niveaux des joueurs dans l'ECS (système de composants entité).

#### Exemple concret :
```cpp
bool levelReady = server.check_level_player(ecs); // Vérifie si un joueur a atteint un niveau supérieur ou égal à 3.
```

---

### **10. `void Server::threadInput()`**
#### Description :
Ce thread est responsable de la gestion de la réception des paquets de données des clients via UDP. Il écoute en permanence les entrées et les ajoute à la file d'attente pour traitement.

#### Exemple concret :
```cpp
server.threadInput(); // Lance un thread pour écouter et traiter les paquets entrants.
```

---

### **11. `void Server::threadSystem()`**
#### Description :
Ce thread gère la logique du système de jeu, comme la gestion des mouvements, des collisions, des ennemis et des niveaux. Il est responsable de l'exécution de tous les systèmes nécessaires à l'évolution du jeu. La méthode est exécutée de manière continue et assure une mise à jour constante de l'état du jeu.

#### Exemple concret :
```cpp
server.threadSystem(); // Lance le thread qui gère la logique du jeu en continu.
```

---

### **12. `void Server::delaySpawn(ClockManager &clock)`**
#### Description :
Gère le délai avant l'apparition des ennemis sur la carte. Les ennemis sont générés après un certain délai, ce qui est géré par cette méthode. Elle vérifie régulièrement si le temps écoulé depuis le début du jeu a dépassé les délais définis pour faire apparaître de nouveaux ennemis.

#### Exemple concret :
```cpp
server.delaySpawn(clock); // Vérifie si les ennemis doivent être générés en fonction du délai écoulé.
```

---

### **13. `bool Server::isLevelReady()`**
#### Description :
Vérifie si tous les ennemis du niveau actuel ont été générés et si le niveau est prêt à passer au suivant. Cela permet au serveur de savoir si la génération d'un nouveau niveau peut commencer.

#### Exemple concret :
```cpp
bool levelReady = server.isLevelReady(); // Vérifie si tous les ennemis du niveau ont été générés.
```

---

### Conclusion
Les méthodes décrites ci-dessus sont essentielles au bon fonctionnement du serveur de jeu. Elles gèrent la communication réseau, la gestion des joueurs, la logique de jeu, et la progression dans les niveaux. Elles utilisent des threads pour paralléliser les tâches et maintenir la fluidité du jeu en temps réel.

---

### **2. Binary **

---

### **1. `SBinary::getAction(std::string &action)`**
#### Description :
La méthode `getAction()` est utilisée pour découper une chaîne d'action (généralement sous la forme `"MOVE/UP/RIGHT"`) en plusieurs sous-actions, séparées par un caractère `/`. Elle retourne un vecteur de chaînes contenant les différentes parties de l'action.

#### Exemple concret :
```cpp
std::string action = "MOVE/UP/RIGHT";
std::vector<std::string> actions = sBinary.getAction(action);
// actions = {"MOVE", "UP", "RIGHT"}
```

---

### **2. `SBinary::serialize(NmpServer::Packet &packet, std::vector<int> &buffer)`**
#### Description :
La méthode `serialize()` transforme un paquet d'événements (par exemple, `MOVE`, `SPRITE`, `JOIN`) en une série d'entiers et les place dans un buffer. Elle gère différentes sortes d'événements et extrait les informations pertinentes de chaque paquet pour les ajouter dans le buffer.

#### Exemple concret :
```cpp
NmpServer::Packet packet(EVENT::MOVE, 1, 100, 200);  // Création d'un paquet MOVE pour le joueur 1 avec des coordonnées (100, 200)
std::vector<int> buffer;
sBinary.serialize(packet, buffer);
// buffer contiendra les entiers représentant l'événement MOVE avec les données associées
```

---

### **3. `SBinary::deserialize(std::vector<int> &buffer)`**
#### Description :
La méthode `deserialize()` prend un buffer de données binaires (représentées par un vecteur d'entiers) et les convertit en un paquet d'événements (`NmpServer::Packet`). Elle lit les informations dans le buffer et retourne le paquet correspondant à l'événement trouvé. Si l'événement est un `MOVE`, elle extrait également la direction à partir du buffer.

#### Exemple concret :
```cpp
std::vector<int> buffer = {1, 2, 100, 200};  // Représente un paquet de mouvement avec les données du joueur 1 et les coordonnées (100, 200)
NmpServer::Packet packet = sBinary.deserialize(buffer);
// Le paquet sera créé avec les informations extraites du buffer
```

---

### **4. `SBinary::clearBuffer(std::vector<int> &buffer)`**
#### Description :
Cette méthode vide le buffer en effaçant tous les éléments qu'il contient. Elle est utilisée après avoir désérialisé un buffer pour s'assurer que la mémoire est libérée et prête pour le prochain traitement.

#### Exemple concret :
```cpp
std::vector<int> buffer = {1, 2, 100, 200};
sBinary.clearBuffer(buffer);
// buffer est maintenant vide
```

---

### **5. `SBinary::printBuffer(std::vector<int> &buffer)`**
#### Description :
La méthode `printBuffer()` affiche chaque élément du buffer dans la console. Elle est utile pour le débogage et la visualisation du contenu du buffer pendant le processus de sérialisation ou de désérialisation.

#### Exemple concret :
```cpp
std::vector<int> buffer = {1, 2, 100, 200};
sBinary.printBuffer(buffer);
// Affiche : "bufferSerialize: 1", "bufferSerialize: 2", "bufferSerialize: 100", "bufferSerialize: 200"
```

---

### Conclusion

La classe `SBinary` est essentielle pour la gestion de la communication binaire entre le serveur et les clients dans l'application. Elle permet de sérialiser et de désérialiser efficacement les paquets d'événements, facilitant ainsi l'échange de données en réseau. Les méthodes décrites ci-dessus sont responsables de la conversion des données entre des objets de type `Packet` et des buffers binaires, ainsi que de l'affichage et de la gestion de ces buffers.

---

### **3. ProtocolHandler**

---

### **1. `ProtocoleHandler::executeOpCode()`**
#### Description :
La méthode `executeOpCode()` est responsable de l'exécution de l'opération correspondant à l'opcode extrait du paquet. Elle recherche dans une carte (`_mapFctOpCode`) la fonction associée à l'opcode et l'exécute.

#### Exemple concret :
Supposons que nous recevions un paquet avec l'événement `MOVE` :
```cpp
ProtocoleHandler protocoleHandler(server);
protocoleHandler.fillPacket(packet);
protocoleHandler.executeOpCode();
// Si l'opcode du paquet est MOVE, la méthode evalMove() sera appelée.
```

---

### **2. `registry &ProtocoleHandler::getECS()`**
#### Description :
Cette méthode retourne une référence à l'ECS (Entity-Component-System) utilisé dans le serveur. Elle permet d'accéder à tous les composants du jeu pour effectuer des mises à jour ou des recherches.

#### Exemple concret :
```cpp
registry &ecs = protocoleHandler.getECS();
// Permet d'accéder aux composants du système ECS pour effectuer des actions dessus.
```

---

### **3. `ProtocoleHandler::fillPacket(Packet &packet)`**
#### Description :
Cette méthode remplit un paquet (`Packet`) dans l'objet `_pck` de la classe `ProtocoleHandler`. Elle est utilisée pour associer un paquet à l'instance du `ProtocoleHandler`.

#### Exemple concret :
```cpp
Packet packet(EVENT::MOVE, 1, 100, 200); // Paquet représentant un mouvement
protocoleHandler.fillPacket(packet); // Remplie l'objet _pck avec ce paquet
```

---

### **4. `std::optional<asio::ip::udp::endpoint> ProtocoleHandler::foundEndpointByClient(Entity &player)`**
#### Description :
Cette méthode cherche un endpoint UDP correspondant à un joueur donné. Si l'endpoint est trouvé, il est retourné ; sinon, la méthode retourne un objet `std::nullopt`.

#### Exemple concret :
```cpp
Entity player = ecs.get_entity(1);
auto endpoint = protocoleHandler.foundEndpointByClient(player);
if (endpoint) {
    std::cout << "Player found at: " << endpoint->address().to_string() << std::endl;
}
```

---

### **5. `ProtocoleHandler::updateMoveEcs(Entity &player, component::controllable::Key &control, sparse_array<component::position>::value_type &pos, component::attribute &att)`**
#### Description :
Cette méthode met à jour les contrôles du joueur dans le système ECS (Entity-Component-System). Elle applique la direction ou l'action du joueur (comme se déplacer ou tirer) en fonction des commandes reçues et met à jour l'état du joueur dans le système.

#### Exemple concret :
```cpp
component::controllable::Key control = component::controllable::Down;
protocoleHandler.updateMoveEcs(player, control, pos, att);
// Cette méthode met à jour la position du joueur avec la direction 'Down'.
```

---

### **6. `ProtocoleHandler::evalMove()`**
#### Description :
La méthode `evalMove()` est appelée lorsque le serveur reçoit une commande de mouvement. Elle extrait la direction du paquet et met à jour la position du joueur dans l'ECS en utilisant la méthode `updateMoveEcs()`.

#### Exemple concret :
```cpp
protocoleHandler.evalMove(); // Évalue le mouvement du joueur et met à jour sa position dans l'ECS.
```

---

### **7. `ProtocoleHandler::evalQuit()`**
#### Description :
Cette méthode est appelée lorsque le serveur reçoit un événement `QUIT` de la part d'un client. Elle gère la logique de déconnexion du joueur.

#### Exemple concret :
```cpp
protocoleHandler.evalQuit(); // Traite l'événement Quit et déconnecte le joueur du jeu.
```

---

### **8. `ProtocoleHandler::evalJoin()`**
#### Description :
La méthode `evalJoin()` est utilisée lorsque le serveur reçoit un événement `JOIN` d'un client. Elle ajoute un nouveau joueur à la partie en initialisant un nouvel objet `Entity` pour ce joueur, lui attribue un rôle et l'ajoute à la liste des joueurs.

#### Exemple concret :
```cpp
protocoleHandler.evalJoin(); // Un joueur rejoint la partie, et son entité est ajoutée à l'ECS.
```

---

### **9. `ProtocoleHandler::initComponents()`**
#### Description :
Cette méthode initialise les différents composants du système ECS (par exemple, `position`, `life`, `score`, `attribute`, etc.). Elle est appelée lors de la création d'un nouveau `ProtocoleHandler` pour s'assurer que tous les composants nécessaires sont enregistrés.

#### Exemple concret :
```cpp
protocoleHandler.initComponents(); // Initialise les composants nécessaires dans l'ECS au début du jeu.
```

---

### **10. `ProtocoleHandler::initPlayer()`**
#### Description :
La méthode `initPlayer()` initialise un joueur avec des composants par défaut dans l'ECS, comme sa position, sa vie, et son type. Elle attribue également un rôle au joueur, par exemple `Player1`, `Player2`, etc.

#### Exemple concret :
```cpp
protocoleHandler.initPlayer(); // Crée un joueur avec des valeurs par défaut et l'ajoute à l'ECS.
```

---

### **11. `ProtocoleHandler::initEnnemies(int posX, int posY, int type)`**
#### Description :
Cette méthode initialise un ennemi dans le système ECS avec une position donnée et un type d'ennemi. Elle ajoute également les composants comme la vitesse, la taille, et la vie de l'ennemi.

#### Exemple concret :
```cpp
protocoleHandler.initEnnemies(100, 200, 1); // Crée un ennemi de type 1 à la position (100, 200).
```

---

### **12. `ProtocoleHandler::loadEnnemiesFromconfig(const std::vector<infoEnnemies_t> vecEnnemies)`**
#### Description :
Cette méthode charge les ennemis à partir d'une configuration donnée, en créant des ennemis dans l'ECS en fonction des informations du fichier de configuration.

#### Exemple concret :
```cpp
std::vector<infoEnnemies_t> enemiesConfig = ...; // Charge la configuration des ennemis.
protocoleHandler.loadEnnemiesFromconfig(enemiesConfig); // Charge et crée les ennemis dans l'ECS.
```

---

### **13. `ProtocoleHandler::clearPlayer()`**
#### Description :
Cette méthode efface les joueurs et les réinitialise à partir de la liste des joueurs dans `_vecPlayer`, en les envoyant à un nouveau niveau.

#### Exemple concret :
```cpp
protocoleHandler.clearPlayer(); // Efface les joueurs et les réinitialise pour le prochain niveau.
```

---

### Conclusion

Le `ProtocoleHandler` gère la logique de traitement des paquets reçus et leur association avec les entités du jeu dans le système ECS. Il prend en charge des événements tels que le mouvement des joueurs, leur déconnexion, leur connexion, et la gestion des ennemis. Grâce à une série de méthodes dédiées à la gestion des événements de jeu, cette classe facilite la manipulation du jeu et des interactions réseau.

---

### **4. ProceduralLevel**

---

### **1. `ProceduralLevel::createRandValue(const int lim, const int range, const bool zero)`**
#### Description :
La méthode `createRandValue()` génère une valeur aléatoire dans une plage spécifiée. Si le paramètre `zero` est vrai, la valeur générée sera dans un intervalle modifié par `range`. Sinon, la valeur sera simplement dans la plage de 0 à `lim`.

#### Exemple concret :
```cpp
ProceduralLevel proceduralLevel;
int value1 = proceduralLevel.createRandValue(100, 50, false); // génère une valeur entre 0 et 99
int value2 = proceduralLevel.createRandValue(100, 50, true);  // génère une valeur entre -25 et 75
```

---

### **2. `ProceduralLevel::generateGroup(nlohmann::json& level, int groupSize, int centerX, int centerY, int dispersion, int type, int delaySpawn)`**
#### Description :
La méthode `generateGroup()` génère un groupe d'ennemis avec des positions aléatoires autour d'un point central (`centerX`, `centerY`). La dispersion détermine la distance à laquelle les ennemis peuvent être placés par rapport à ce point central. Elle ajoute ensuite chaque ennemi au tableau JSON `level`.

#### Exemple concret :
```cpp
nlohmann::json level;
proceduralLevel.generateGroup(level, 5, 100, 200, 50, 2, 10); 
// Crée un groupe de 5 ennemis autour du point (100, 200) avec une dispersion de 50 et un délai de 10
```

---

### **3. `ProceduralLevel::generateLevel(int nbGroups, Difficulty difficulty)`**
#### Description :
La méthode `generateLevel()` génère un niveau avec un nombre spécifié de groupes d'ennemis (`nbGroups`). Elle ajuste les paramètres du niveau (comme la taille des groupes, la dispersion des ennemis et le délai de leur apparition) en fonction de la difficulté du niveau (Easy, Medium, Hard). Chaque groupe d'ennemis est généré en appelant `generateGroup()`.

#### Exemple concret :
```cpp
proceduralLevel.generateLevel(10, Difficulty::Medium);
// Crée un niveau avec 10 groupes d'ennemis, ajustant les paramètres en fonction de la difficulté moyenne.
```

---

### **4. `ProceduralLevel::generateLevel()` - Sauvegarde du Niveau dans un Fichier JSON**
#### Description :
Une fois les ennemis générés, le niveau est sauvegardé dans un fichier JSON (`level1.json`). Cela permet de conserver les informations de niveau dans un format lisible et structuré. Si l'écriture dans le fichier échoue, un message d'erreur est affiché.

#### Exemple concret :
```cpp
proceduralLevel.generateLevel(10, Difficulty::Hard); 
// Après la génération des ennemis, un fichier "level1.json" sera créé avec les détails du niveau.
```

---

### Conclusion

La classe `ProceduralLevel` est responsable de la génération procédurale des niveaux de jeu en créant des groupes d'ennemis placés aléatoirement. Elle utilise des méthodes pour déterminer la position des ennemis, ajuster leur nombre et leur délai d'apparition en fonction de la difficulté du niveau, et enfin sauvegarder les informations du niveau dans un fichier JSON. Cela permet de créer des niveaux variés de manière dynamique à chaque exécution du jeu.

---

### **5. Parser**

---

### **1. `Parser::parseConfig()`**
#### Description :
La méthode `parseConfig()` ouvre et lit un fichier JSON spécifié par `_fileName` (généralement contenant les informations des ennemis dans un niveau de jeu). Elle charge les informations des ennemis dans un tableau d'objets `infoEnnemies_t`, chacun représentant un ennemi avec son type, sa position (X, Y), et son délai d'apparition (`delaySpawn`).

#### Exemple concret :
```cpp
Parser parser("../../server/configFile/level1.json");
parser.parseConfig(); 
// Ouvre le fichier "level1.json", lit les données JSON, et charge les informations des ennemis dans le vecteur _vecEnnemies.
```

---

### **2. `Parser::displayVec()`**
#### Description :
La méthode `displayVec()` affiche sur la sortie standard toutes les informations contenues dans `_vecEnnemies`, telles que le type, la position et le délai d'apparition de chaque ennemi.

#### Exemple concret :
```cpp
parser.displayVec(); 
// Affiche toutes les informations des ennemis qui ont été chargées par `parseConfig()`, comme le type, la position, et le délai.
```

---

### **3. `Parser::getVector()`**
#### Description :
La méthode `getVector()` retourne le vecteur `_vecEnnemies`, qui contient tous les ennemis chargés à partir du fichier JSON. Cela permet à d'autres parties du programme d'accéder aux informations des ennemis générés.

#### Exemple concret :
```cpp
std::vector<infoEnnemies_t> enemies = parser.getVector(); 
// Récupère les ennemis chargés à partir du fichier JSON sous forme d'un vecteur.
```

---

### **4. `Parser::loadNewLevel(std::string file)`**
#### Description :
La méthode `loadNewLevel()` permet de charger un nouveau niveau en modifiant le nom du fichier utilisé (`_fileName`) et en réexécutant `parseConfig()` pour charger les données des ennemis du nouveau fichier.

#### Exemple concret :
```cpp
parser.loadNewLevel("../../server/configFile/level2.json");
// Charge un nouveau fichier "level2.json" et met à jour les ennemis avec les nouvelles données.
```

---

### Conclusion

La classe `Parser` est conçue pour charger et gérer les données des ennemis dans un jeu à partir de fichiers JSON. Elle inclut des méthodes pour lire les informations des ennemis depuis un fichier, afficher ces informations, et obtenir les données sous forme d'un vecteur utilisable par d'autres parties du programme. Cela permet une gestion flexible et dynamique des ennemis dans différents niveaux du jeu.

---

### **6. Packet**

---

### **1. `Packet::Packet(std::size_t id, EVENT event, std::optional<DIRECTION> direction)`**
#### Description :
Ce constructeur crée un paquet avec un `id`, un `event` (type d'événement), et un argument optionnel `direction`. Ce constructeur est utilisé lorsqu'un événement de mouvement ou d'action est envoyé.

#### Exemple concret :
```cpp
std::size_t id = 1;
NmpServer::EVENT event = NmpServer::EVENT::MOVE;
std::optional<NmpServer::DIRECTION> direction = NmpServer::DIRECTION::UP;
Packet packet(id, event, direction); 
// Crée un paquet avec un identifiant et un événement MOVE, avec la direction vers le haut.
```

---

### **2. `Packet::Packet(EVENT event, SpriteInfo &sprite)`**
#### Description :
Ce constructeur est utilisé lorsque l'événement concerne l'envoi d'informations sur un sprite, comme sa position, sa taille, etc.

#### Exemple concret :
```cpp
NmpServer::SpriteInfo sprite = {1, 2, 50, 50, 100, 100};
NmpServer::EVENT event = NmpServer::EVENT::SPRITE;
Packet packet(event, sprite);
// Crée un paquet avec un événement SPRITE, contenant des informations sur un sprite.
```

---

### **3. `Packet::Packet(EVENT event)`**
#### Description :
Ce constructeur est utilisé pour créer un paquet sans arguments ou détails supplémentaires, par exemple pour signaler la fin d'une séquence d'événements.

#### Exemple concret :
```cpp
NmpServer::EVENT event = NmpServer::EVENT::EOI; // End of Information
Packet packet(event);
// Crée un paquet avec un événement "End of Information".
```

---

### **4. `Packet::Packet(EVENT event, int life, int score, int level)`**
#### Description :
Ce constructeur est utilisé pour envoyer des informations telles que la vie, le score et le niveau d'un joueur. C'est typiquement utilisé pour transmettre des informations de progression du joueur.

#### Exemple concret :
```cpp
NmpServer::EVENT event = NmpServer::EVENT::INFO;
int life = 3;
int score = 1500;
int level = 5;
Packet packet(event, life, score, level);
// Crée un paquet contenant des informations sur la vie, le score et le niveau d'un joueur.
```

---

### **5. `bool Packet::checkPacket()`**
#### Description :
La méthode `checkPacket()` vérifie si le paquet est valide. Elle vérifie si les données nécessaires sont présentes pour les événements MOVE, SHOOT, ou QUIT. Par exemple, un mouvement nécessite une direction, mais un événement SHOOT ne doit pas contenir d'argument.

#### Exemple concret :
```cpp
Packet packet = ...;
if (packet.checkPacket()) {
    // Le paquet est valide, on peut procéder à son traitement.
} else {
    // Le paquet est invalide, gestion de l'erreur.
}
```

---

### **6. `EVENT Packet::getOpCode()`**
#### Description :
La méthode `getOpCode()` retourne l'événement du paquet. Cela permet de savoir quel type d'action est associé à ce paquet.

#### Exemple concret :
```cpp
EVENT event = packet.getOpCode(); 
// Retourne l'événement associé au paquet, par exemple MOVE ou SHOOT.
```

---

### **7. `std::optional<DIRECTION> Packet::getArg()`**
#### Description :
La méthode `getArg()` retourne l'argument associé au paquet, si présent. Cela pourrait être une direction pour un mouvement, ou aucun argument pour certains événements.

#### Exemple concret :
```cpp
std::optional<NmpServer::DIRECTION> direction = packet.getArg();
if (direction.has_value()) {
    // Utilise la direction retournée pour effectuer une action.
}
```

---

### **8. `SpriteInfo Packet::getSpriteInfo()`**
#### Description :
La méthode `getSpriteInfo()` retourne les informations sur le sprite associé au paquet, comme l'identifiant, la position, et la taille. Cela est utilisé pour envoyer des informations visuelles.

#### Exemple concret :
```cpp
SpriteInfo sprite = packet.getSpriteInfo();
// Utilisation des informations sur le sprite, comme sa position et sa taille.
```

---

### **9. `std::size_t Packet::getId()`**
#### Description :
La méthode `getId()` retourne l'identifiant du paquet, souvent utilisé pour identifier un joueur ou une entité dans le jeu.

#### Exemple concret :
```cpp
std::size_t playerId = packet.getId();
// Utilise l'ID pour identifier le joueur ou l'entité associée au paquet.
```

---

### **10. `int Packet::getX() const` et `int Packet::getY() const`**
#### Description :
Ces méthodes retournent respectivement la position X et Y d'un objet, souvent utilisées pour les événements liés à la position, comme un mouvement dans le jeu.

#### Exemple concret :
```cpp
int x = packet.getX();
int y = packet.getY();
// Utilisation des coordonnées X et Y pour déplacer un objet ou un joueur.
```

---

### **11. `Packet& Packet::operator=(const Packet &other)`**
#### Description :
L'opérateur d'assignation permet de copier un paquet dans un autre, en dupliquant ses informations (opCode, arg, sprite, id, etc.).

#### Exemple concret :
```cpp
Packet packet1 = ...;
Packet packet2;
packet2 = packet1;
// packet2 est maintenant une copie de packet1.
```

---

### Conclusion

### La classe `Packet` est essentielle pour gérer la communication d'événements entre le serveur et les clients dans un jeu réseau. Elle permet de structurer et de valider des événements tels que les mouvements, les actions (comme tirer), et les informations sur l'état du jeu (comme la vie ou le score). Elle garantit une gestion fluide et sécurisée des données échangées.
---

### **7. LobbyServerTCP**

---

### **1. `LobbyServerTCP::LobbyServerTCP(asio::io_context& ioContext, int port)`**
#### Description :
Le constructeur initialise le serveur TCP, l'associe au port spécifié et commence à écouter les connexions entrantes. Ce constructeur est essentiel pour configurer le serveur pour accepter les connexions sur un port donné.

#### Exemple concret :
```cpp
asio::io_context ioContext;
int port = 12345;
LobbyServerTCP server(ioContext, port);
// Le serveur écoute désormais les connexions entrantes sur le port 12345.
```

---

### **2. `void LobbyServerTCP::startAccepting()`**
#### Description :
Cette méthode lance le processus d'acceptation des connexions clients en appelant `acceptConnection()`, qui attend de nouvelles connexions entrantes.

#### Exemple concret :
```cpp
server.startAccepting();
// Le serveur commence à accepter les connexions clients.
```

---

### **3. `void LobbyServerTCP::acceptConnection()`**
#### Description :
La méthode `acceptConnection` accepte les connexions entrantes et crée une nouvelle session pour chaque client. Elle établit également un nouveau socket pour chaque client et les traite dans une fonction dédiée `handleClient`.

#### Exemple concret :
```cpp
// Lorsqu'un client se connecte, acceptConnection est appelé automatiquement.
server.acceptConnection();
// Accepte la connexion entrante et crée une nouvelle session pour le client.
```

---

### **4. `void LobbyServerTCP::handleClient(std::shared_ptr<asio::ip::tcp::socket> socket, const std::string& clientIP)`**
#### Description :
Cette méthode gère la communication avec le client, lit les données envoyées par le client et répond en fonction des commandes reçues.

#### Exemple concret :
```cpp
// Après avoir accepté une connexion, handleClient est appelée pour gérer la communication avec le client.
server.handleClient(socket, "192.168.0.1");
// Gère la communication avec un client ayant l'IP 192.168.0.1.
```

---

### **5. `std::string LobbyServerTCP::processRequest(const std::string& request, const std::string& playerId, const std::string& clientIP)`**
#### Description :
Cette méthode traite les commandes envoyées par les clients, telles que `CREATE_LOBBY`, `JOIN_LOBBY`, `LIST_LOBBIES`, etc., et renvoie une réponse appropriée en fonction de la commande.

#### Exemple concret :
```cpp
std::string request = "CREATE_LOBBY myLobby";
std::string response = server.processRequest(request, "player1", "192.168.0.1");
// Traite la demande de création de lobby et renvoie la réponse appropriée.
```

---

### **6. `std::string LobbyServerTCP::listLobbies()`**
#### Description :
Cette méthode génère une liste des lobbies actuellement existants, en indiquant l'ID du lobby, le nombre de joueurs et l'état du lobby.

#### Exemple concret :
```cpp
std::string lobbies = server.listLobbies();
// Renvoie une liste des lobbies existants.
```

---

### **7. `std::string LobbyServerTCP::createLobby(const std::string& lobbyId, const std::string& creatorIP)`**
#### Description :
La méthode `createLobby` crée un nouveau lobby avec un identifiant donné et assigne l'IP du créateur. Si le lobby existe déjà, elle renvoie un message d'erreur.

#### Exemple concret :
```cpp
std::string lobbyId = "myLobby";
std::string creatorIP = "192.168.0.1";
std::string response = server.createLobby(lobbyId, creatorIP);
// Crée un lobby nommé "myLobby" avec l'IP du créateur.
```

---

### **8. `std::string LobbyServerTCP::joinLobby(const std::string& lobbyId, const std::string& playerId)`**
#### Description :
Cette méthode permet à un joueur de rejoindre un lobby spécifique. Si le lobby existe, elle ajoute le joueur à la liste des joueurs du lobby.

#### Exemple concret :
```cpp
std::string lobbyId = "myLobby";
std::string playerId = "player1";
std::string response = server.joinLobby(lobbyId, playerId);
// Le joueur "player1" rejoint le lobby "myLobby".
```

---

### **9. `std::string LobbyServerTCP::leaveLobby(const std::string& playerId)`**
#### Description :
Cette méthode permet à un joueur de quitter le lobby auquel il appartient. Si le lobby devient vide après que le joueur a quitté, il est supprimé.

#### Exemple concret :
```cpp
std::string playerId = "player1";
std::string response = server.leaveLobby(playerId);
// Le joueur "player1" quitte son lobby actuel.
```

---

### **10. `std::string LobbyServerTCP::sendMessage(const std::string& playerId, const std::string& message)`**
#### Description :
Cette méthode permet à un joueur d'envoyer un message à tous les joueurs d'un lobby. Elle transmet le message à tous les joueurs présents dans le lobby via TCP.

#### Exemple concret :
```cpp
std::string playerId = "player1";
std::string message = "Hello, everyone!";
std::string response = server.sendMessage(playerId, message);
// Envoie le message "Hello, everyone!" à tous les joueurs du lobby.
```

---

### **11. `std::string LobbyServerTCP::getChatHistory(const std::string& playerId)`**
#### Description :
Cette méthode permet à un joueur de récupérer l'historique des messages du chat pour le lobby auquel il appartient.

#### Exemple concret :
```cpp
std::string playerId = "player1";
std::string chatHistory = server.getChatHistory(playerId);
// Récupère l'historique des messages du lobby où "player1" est présent.
```

---

### **12. `std::string LobbyServerTCP::getUdpInfo(const std::string& lobbyId)`**
#### Description :
Cette méthode permet de récupérer l'information UDP nécessaire pour rejoindre un lobby spécifique. Elle renvoie l'IP du créateur si le lobby est entièrement rejoint.

#### Exemple concret :
```cpp
std::string lobbyId = "myLobby";
std::string udpInfo = server.getUdpInfo(lobbyId);
// Renvoie l'IP du créateur du lobby "myLobby" si celui-ci est prêt.
```

---

### **13. `bool LobbyServerTCP::isPlayerInLobby(const std::string& playerId)`**
#### Description :
Cette méthode vérifie si un joueur est déjà dans un lobby. Elle renvoie `true` si le joueur est dans un lobby, sinon `false`.

#### Exemple concret :
```cpp
std::string playerId = "player1";
bool isInLobby = server.isPlayerInLobby(playerId);
// Vérifie si "player1" est dans un lobby.
```

---

### Conclusion

#### Le `LobbyServerTCP` est un serveur TCP qui gère les lobbies de jeu et les communications entre les joueurs. Les méthodes proposées permettent de créer des lobbies, de rejoindre des lobbies existants, de quitter un lobby, d'envoyer des messages dans le chat et de récupérer des informations sur le lobby et les joueurs. Ce serveur utilise des sockets TCP pour gérer les connexions et assure une gestion efficace des lobbies et des joueurs à l'aide de l'API `asio`.
---

## Conclusion
## Cette documentation permet de comprendre brièvement le rôle de chaque classe dans l'architecture du serveur, leurs fonctionnalités principales et comment elles interagissent pour gérer la logique du jeu et la communication entre le serveur et les clients.
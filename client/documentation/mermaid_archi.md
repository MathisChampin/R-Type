graph TD
    subgraph GameplayElements
        Player1["Player 1"]
        Player2["Player 2"]
        Enemy["Enemy (Bydo)"]
        Boss["Boss"]
        Projectile_Player["Player Projectile"]
        Projectile_Enemy["Enemy Projectile"]
        PowerUp["Power-Up"]
        Obstacle["Obstacle"]
    end

    Player1 -->|Shoots| Projectile_Player
    Player2 -->|Shoots| Projectile_Player
    Enemy -->|Shoots| Projectile_Enemy
    Boss -->|Shoots| Projectile_Enemy
    
    Projectile_Player -->|Hits| Enemy
    Projectile_Player -->|Hits| Boss
    Projectile_Player -->|Destroyed on Impact| Obstacle
    Projectile_Enemy -->|Hits| Player1
    Projectile_Enemy -->|Hits| Player2
    PowerUp -->|Collected by| Player1
    PowerUp -->|Collected by| Player2

    Enemy -->|Spawns| PowerUp
    Boss -->|Spawns Obstacles| Obstacle

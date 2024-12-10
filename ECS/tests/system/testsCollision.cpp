#include <criterion/criterion.h>
#include "system.hpp"
#include "position.hpp"
#include "size.hpp"
#include "attribute.hpp"
#include "life.hpp"
#include "idPlayer.hpp"
#include "score.hpp"
#include <iostream>

Test(CollisionSystem, PlayerHitByShoot) {
    registry reg;
    System sys;

    reg.register_component<component::position>();
    reg.register_component<component::size>();
    reg.register_component<component::attribute>();
    const auto &life = reg.register_component<component::life>();
    reg.register_component<component::idPlayer>();

    Entity player = reg.spawn_entity();
    reg.add_component<component::position>(player, {10, 10});
    reg.add_component<component::size>(player, {1, 1});
    reg.add_component<component::attribute>(player, {component::attribute::Player1});
    reg.add_component<component::life>(player, {3});
    reg.add_component<component::score>(player, {0});

    Entity enemy = reg.spawn_entity();
    reg.add_component<component::position>(enemy, {20, 20});
    reg.add_component<component::size>(enemy, {5, 5});
    reg.add_component<component::attribute>(enemy, {component::attribute::Ennemies});
    reg.add_component<component::life>(enemy, {1});
    
    Entity shoot = reg.spawn_entity();
    reg.add_component<component::position>(shoot, {10, 10});
    reg.add_component<component::size>(shoot, {1, 1});
    reg.add_component<component::attribute>(shoot, {component::attribute::Shoot});
    reg.add_component<component::idPlayer>(shoot, {enemy.get_id()});
    sys.collision_system(reg);

    const auto &l = life[player.get_id()];
    cr_assert_eq(l.life, 2, "Player's life should be decremented by 1, but is %d", l.life);
}

Test(CollisionSystem, EnemyHitByShoot) {
    registry reg;
    System sys;

    reg.register_component<component::position>();
    reg.register_component<component::size>();
    reg.register_component<component::attribute>();
    const auto &score = reg.register_component<component::score>();
    reg.register_component<component::idPlayer>();

    Entity player = reg.spawn_entity();
    reg.add_component<component::position>(player, {10, 10});
    reg.add_component<component::size>(player, {5, 5});
    reg.add_component<component::attribute>(player, {component::attribute::Player1});
    reg.add_component<component::life>(player, {3});
    reg.add_component<component::score>(player, {0});

    Entity enemy = reg.spawn_entity();
    reg.add_component<component::position>(enemy, {20, 20});
    reg.add_component<component::size>(enemy, {5, 5});
    reg.add_component<component::attribute>(enemy, {component::attribute::Ennemies});
    reg.add_component<component::life>(enemy, {1});

    Entity shoot = reg.spawn_entity();
    reg.add_component<component::position>(shoot, {20, 22});
    reg.add_component<component::size>(shoot, {1, 1});
    reg.add_component<component::attribute>(shoot, {component::attribute::Shoot});
    reg.add_component<component::idPlayer>(shoot, {player.get_id()});

    sys.collision_system(reg);

    const auto &s = score[player.get_id()];
    cr_assert_eq(s.score, 10, "Player's score should be increased by 10, but is %d", s.score);
}

Test(CollisionSystem, NoCollisionBetweenPlayerAndEnemy) {
    registry reg;
    System sys;

    reg.register_component<component::position>();
    reg.register_component<component::size>();
    reg.register_component<component::attribute>();
    const auto &life = reg.register_component<component::life>();
    const auto &score = reg.register_component<component::score>();


    Entity player = reg.spawn_entity();
    reg.add_component<component::position>(player, {10, 10});
    reg.add_component<component::size>(player, {5, 5});
    reg.add_component<component::attribute>(player, {component::attribute::Player1});
    reg.add_component<component::life>(player, {3});
    reg.add_component<component::score>(player, {0});

    Entity shoot = reg.spawn_entity();
    reg.add_component<component::position>(shoot, {100, 100});
    reg.add_component<component::size>(shoot, {1, 1});
    reg.add_component<component::attribute>(shoot, {component::attribute::Shoot});
    reg.add_component<component::idPlayer>(shoot, {player.get_id()});

    Entity enemy = reg.spawn_entity();
    reg.add_component<component::position>(enemy, {50, 50});
    reg.add_component<component::size>(enemy, {5, 5});
    reg.add_component<component::attribute>(enemy, {component::attribute::Ennemies});
    reg.add_component<component::life>(enemy, {1});

    sys.collision_system(reg);

    const auto &l = life[player.get_id()];
    cr_assert_eq(l.life, 3, "Player's life should remain unchanged, but is %d", l.life);

    const auto &sp = score[player.get_id()];
    cr_assert_eq(sp.score, 0, "Player's score should remain unchanged, but is %d", sp.score);
}

Test(CollisionSystem, MultipleCollisions) {
    registry reg;
    System sys;

    reg.register_component<component::position>();
    reg.register_component<component::size>();
    reg.register_component<component::attribute>();
    const auto &life = reg.register_component<component::life>();
    const auto &score = reg.register_component<component::score>();
    reg.register_component<component::idPlayer>();

    Entity player = reg.spawn_entity();
    reg.add_component<component::position>(player, {10, 10});
    reg.add_component<component::size>(player, {5, 5});
    reg.add_component<component::attribute>(player, {component::attribute::Player1});
    reg.add_component<component::life>(player, {3});
    reg.add_component<component::score>(player, {0});
    reg.add_component<component::idPlayer>(player, {player.get_id()});

    Entity enemy1 = reg.spawn_entity();
    reg.add_component<component::position>(enemy1, {20, 20});
    reg.add_component<component::size>(enemy1, {5, 5});
    reg.add_component<component::attribute>(enemy1, {component::attribute::Ennemies});
    reg.add_component<component::life>(enemy1, {1});
    reg.add_component<component::idPlayer>(enemy1, {player.get_id()});

    Entity enemy2 = reg.spawn_entity();
    reg.add_component<component::position>(enemy2, {50, 50});
    reg.add_component<component::size>(enemy2, {5, 5});
    reg.add_component<component::attribute>(enemy2, {component::attribute::Ennemies});
    reg.add_component<component::life>(enemy2, {1});
    reg.add_component<component::idPlayer>(enemy2, {player.get_id()});

    Entity shoot1 = reg.spawn_entity();
    reg.add_component<component::position>(shoot1, {20, 20});
    reg.add_component<component::size>(shoot1, {1, 1});
    reg.add_component<component::attribute>(shoot1, {component::attribute::Shoot});
    reg.add_component<component::idPlayer>(shoot1, {player.get_id()});

    Entity shoot2 = reg.spawn_entity();
    reg.add_component<component::position>(shoot2, {50, 50});
    reg.add_component<component::size>(shoot2, {1, 1});
    reg.add_component<component::attribute>(shoot2, {component::attribute::Shoot});
    reg.add_component<component::idPlayer>(shoot2, {player.get_id()});

    sys.collision_system(reg);
    auto &l = life[player.get_id()];
    auto &s = score[player.get_id()]; 
    cr_assert_eq(l.life, 3, "Player's life should remain unchanged, but is %d", l.life);

    cr_assert_eq(s.score, 20, "Player's score should be 20, but is %d", s.score);
}

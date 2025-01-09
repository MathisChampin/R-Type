#pragma once

    #include "Registry.hpp"
    #include "position.hpp"
    #include "attribute.hpp"
    #include "score.hpp"
    #include "life.hpp"
    #include "state.hpp"
    #include "velocity.hpp"
    #include "size.hpp"
    #include "level.hpp"
    #include "controllable.hpp"
    #include "system.hpp"
    #include "Enemy.hpp"
    #include "Shoot.hpp"
    #include <vector>
    #include <memory>

class GameECS {

    public:
        GameECS(registry ecs): m_ecs{ecs} {
            m_ecs.register_component<component::attribute>();
            m_ecs.register_component<component::controllable>();
            m_ecs.register_component<component::level>();
            m_ecs.register_component<component::life>();
            m_ecs.register_component<component::position>();
            m_ecs.register_component<component::score>();
            m_ecs.register_component<component::size>();
            m_ecs.register_component<component::state>();
            m_ecs.register_component<component::velocity>();
        }

        void createPlayer() {
            Entity player = m_ecs.spawn_entity();
    
            m_ecs.add_component(player, component::position{100, 750});
            m_ecs.add_component(player, component::velocity{5, 15});
            m_ecs.add_component(player, component::size{240, 160});
            m_ecs.add_component(player, component::attribute{component::attribute::Player1});
            m_ecs.add_component(player, component::life{3});
            m_ecs.add_component(player, component::score{0});
            m_ecs.add_component(player, component::level{component::level::Level0});
            m_ecs.add_component(player, component::controllable{component::controllable::NoKey});
            m_ecs.add_component(player, component::state{component::state::Alive});
        }

        void createEnemy() {
            Entity enemy = m_ecs.spawn_entity();
            m_ecs.add_component(enemy, component::position{1850, 780});
            m_ecs.add_component(enemy, component::velocity{-3, 15});
            m_ecs.add_component(enemy, component::size{90, 93});
            m_ecs.add_component(enemy, component::attribute{component::attribute::Ennemies});
            m_ecs.add_component(enemy, component::life{1});
            m_ecs.add_component(enemy, component::score{0});
            m_ecs.add_component(enemy, component::level{component::level::Level0});
            m_ecs.add_component(enemy, component::controllable{component::controllable::NoKey});
            m_ecs.add_component(enemy, component::state{component::state::Alive});

            std::shared_ptr<Enemy> enemySprite = std::make_shared<Enemy>(enemy.get_id(), "./assets/enemy.png", 1850, 780, 90, 93, 8, 0.1f);
            enemySprites.push_back(enemySprite);
        }

        void createShoot() {
            auto &attributes = m_ecs.get_components<component::attribute>();
            auto &positions = m_ecs.get_components<component::position>();

            for (size_t i = 0; i < attributes.size(); i++) {
                auto &att = attributes[i];
                if (att._type == component::attribute::Shoot) {
                    bool shootExists = false;
                    for (auto& enemyShoots : enemyShoot) {
                        if (enemyShoots->get_id() == i) {
                            shootExists = true;
                            break;
                        }
                    }
                    if (!shootExists) {
                        std::shared_ptr<Shoot> shootEnemy = std::make_shared<Shoot>(i, "./assets/bullet.png", positions[i].x, positions[i].y);
                        enemyShoot.push_back(shootEnemy);
                        std::cout << "size vector shoot " << enemyShoot.size() << std::endl;
                    }
                }
            }
        }

        void drawEnemies(sf::RenderWindow& window) {
            for (auto& enemySprite : enemySprites) {
                enemySprite->drawSprite(window);
            }
            if (enemyShoot.size() > 0) {
                for (auto& shootSprite : enemyShoot) {
                    shootSprite->drawSprite(window);
                }    
            }
        }

        void updatePositionEnemys()
        {
            auto &attributes = m_ecs.get_components<component::attribute>();
            auto &positions = m_ecs.get_components<component::position>();
            auto &states = m_ecs.get_components<component::state>();
            std::vector<std::shared_ptr<Enemy>> enemiesToRemove;

            for (size_t i = 0; i < attributes.size(); i++) {
                auto &att = attributes[i];
                auto &s = states[i];
                if (att._type == component::attribute::Ennemies && s._stateKey == component::state::Alive) {
                    auto &pos = positions[i];
                    for (auto& enemySprite : enemySprites) {
                        if (enemySprite->get_id() == i) {
                            enemySprite->setPosition(sf::Vector2f(pos.x, pos.y));
                        }
                    }
                } else if (att._type == component::attribute::Ennemies && s._stateKey == component::state::Dead) {
                    for (auto it = enemySprites.begin(); it != enemySprites.end(); ++it) {
                        if ((*it)->get_id() == i) {
                            enemiesToRemove.push_back(*it);
                            enemySprites.erase(it);
                        }
                    }
                }
            }
        }

        void updatePositionShoots()
        {
            auto &attributes = m_ecs.get_components<component::attribute>();
            auto &positions = m_ecs.get_components<component::position>();
            auto &states = m_ecs.get_components<component::state>();
            std::vector<std::shared_ptr<Shoot>> shootsToRemove;

            for (size_t i = 0; i < attributes.size(); i++) {
                auto &att = attributes[i];
                auto &s = states[i];
                if (att._type == component::attribute::Shoot && s._stateKey == component::state::Alive) {
                    auto &pos = positions[i];
                    for (auto& shootSprite : enemyShoot) {
                        if (shootSprite->get_id() == i) {
                            shootSprite->setPosition(sf::Vector2f(pos.x, pos.y));
                        }
                    }
                } else if (att._type == component::attribute::Shoot && s._stateKey == component::state::Dead) {
                    for (auto it = enemyShoot.begin(); it != enemyShoot.end(); ++it) {
                        if ((*it)->get_id() == i) {
                            shootsToRemove.push_back(*it);
                            enemyShoot.erase(it);
                        }
                    }
                }
            }
        }

        void spawnEnemiesAtInterval(float deltaTime) {
            enemySpawnTimer += deltaTime;

            if (enemySpawnTimer >= 2.0f) {
                createEnemy();
                sys.shoot_system_ennemies(m_ecs);
                createShoot();
                enemySpawnTimer = 0.0f;
            }
            for (auto &enemySprite : enemySprites)
                enemySprite->update(deltaTime);
        }

        void update(float deltaTime) {
            spawnEnemiesAtInterval(deltaTime);
            sys.position_system(m_ecs);
            updatePositionEnemys();
            updatePositionShoots();
        }

        Entity getPlayer()
        {
            auto &attributes = m_ecs.get_components<component::attribute>();

            for (size_t i = 0; i < attributes.size(); i++) {
                auto &at = attributes[i];
                if (at._type == component::attribute::Player1)
                    return m_ecs.get_entity(i);
            }
            return Entity{};
        }

        int getScorePlayer() {
            auto &attributes = m_ecs.get_components<component::attribute>();
            auto &scores = m_ecs.get_components<component::score>();

            for (size_t i = 0; i < attributes.size() && i < scores.size(); i++) {
                auto &at = attributes[i];
                if (at._type == component::attribute::Player1) {
                    auto &s = scores[i];
                    return s.score;
                }
            }
            return 0;
        }

        int getLifePlayer() {
            auto &attributes = m_ecs.get_components<component::attribute>();
            auto &lifes = m_ecs.get_components<component::life>();

            for (size_t i = 0; i < attributes.size() && i < lifes.size(); i++) {
                auto &at = attributes[i];
                if (at._type == component::attribute::Player1) {
                    auto &l = lifes[i];
                    return l.life;
                }
            }
            return 0;
        }

        void movePlayer(component::controllable::Key direction) {
            auto &controllables = m_ecs.get_components<component::controllable>();
            auto &attributes = m_ecs.get_components<component::attribute>();

            for (size_t i = 0; i < attributes.size(); ++i) {
                if (attributes[i]._type == component::attribute::Player1) {
                    auto &ctl = controllables[i];
                    ctl.active_key = direction;
                    sys.control_system(m_ecs);
                }
            }
        }

        const sf::Vector2f getPlayerPosition() {
            auto &attributes = m_ecs.get_components<component::attribute>();
            auto &positions = m_ecs.get_components<component::position>();

            for (size_t i = 0; i < attributes.size(); ++i) {
                if (attributes[i]._type == component::attribute::Player1) {
                    auto &pos = positions[i];
                    return sf::Vector2f(pos.x, pos.y);
                }
            }
            return sf::Vector2f(0, 0);
        }

        registry getEcs()
        {
            return m_ecs;
        }

    private:
        registry m_ecs;
        System sys;
        std::vector<std::shared_ptr<Enemy>> enemySprites;
        std::vector<std::shared_ptr<Shoot>> enemyShoot;
        float enemySpawnTimer = 0.0f;

        sf::Texture enemyTexture;
};

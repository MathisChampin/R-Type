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
            m_ecs.add_component(player, component::size{50, 50});
            m_ecs.add_component(player, component::attribute{component::attribute::Player1});
            m_ecs.add_component(player, component::life{3});
            m_ecs.add_component(player, component::score{0});
            m_ecs.add_component(player, component::level{component::level::Level0});
            m_ecs.add_component(player, component::controllable{component::controllable::NoKey});
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
};


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

        registry getEcs()
        {
            return m_ecs;
        }

    private:
        registry m_ecs;
};


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
        GameECS() {
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
    
        void createPlayer(int x, int y, int vx, int vy) {
            Entity player = m_ecs.spawn_entity();
    
            m_ecs.add_component(player, component::position{x, y});
            m_ecs.add_component(player, component::velocity{vx, vy});
            m_ecs.add_component(player, component::size{50, 50});
            m_ecs.add_component(player, component::attribute{component::attribute::Player1});
            m_ecs.add_component(player, component::life{3});
            m_ecs.add_component(player, component::score{0});
            m_ecs.add_component(player, component::level{component::level::Level0});
        }
    
    private:
        registry m_ecs;
};


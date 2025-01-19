#ifndef SYSTEM_HPP_
    #define SYSTEM_HPP_

    #include "Registry.hpp"
    #include "attribute.hpp"

class System {
    public:
        void position_system(registry &reg);
        void control_system_p1(registry &reg);
        void control_system_p2(registry &reg);
        void control_system_p3(registry &reg);
        void control_system_p4(registry &reg);
        void collision_system(registry &reg);
        void collision_system_with_frendly_fire(registry &reg);
        void power_up_velocity_p1(registry &reg);
        void power_up_velocity_p2(registry &reg);
        void power_up_velocity_p3(registry &reg);
        void power_up_velocity_p4(registry &reg);
        void reset_velocity_p1(registry &reg);
        void reset_velocity_p2(registry &reg);
        void reset_velocity_p3(registry &reg);
        void reset_velocity_p4(registry &reg);
        void collision_power_up(registry &reg);
        void level_system(registry &reg);
        void power_up_life_p1(registry &reg);
        void power_up_life_p2(registry &reg);
        void power_up_life_p3(registry &reg);
        void power_up_life_p4(registry &reg);
        void shoot_system_player_1(registry &reg, size_t i);
        void shoot_system_player_2(registry &reg, size_t i);
        void shoot_system_player_3(registry &reg, size_t i);
        void shoot_system_player_4(registry &reg, size_t i);
        void shoot_system_player_5(registry &reg, size_t i);
        void shoot_system_player_6(registry &reg, size_t i);

        void shoot_system_ennemies(registry &reg);
        void kill_system(registry &reg);
        void win_system(registry &reg);
        void lose_system(registry &reg);
        void spawn_power_up(registry &reg);
        void spawn_power_up_life(registry &reg);
    private:
        component::attribute::entityType _type;
};

#endif /* SYSTEM_HPP_ */
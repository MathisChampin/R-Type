#ifndef SYSTEM_HPP_
    #define SYSTEM_HPP_

    #include "Registry.hpp"

class System {
    public:
        void position_system(registry &reg);
        void control_system_p1(registry &reg);
        void control_system_p2(registry &reg);
        void control_system_p3(registry &reg);
        void control_system_p4(registry &reg);
        void collision_system(registry &reg);
        bool collision_power_up_move(registry &reg);
        void power_up_velocity_p1(registry &reg);
        void power_up_velocity_p2(registry &reg);
        void power_up_velocity_p3(registry &reg);
        void power_up_velocity_p4(registry &reg);
        void reset_velocity_p1(registry &reg);
        void reset_velocity_p2(registry &reg);
        void reset_velocity_p3(registry &reg);
        void reset_velocity_p4(registry &reg);
        bool collision_power_up_shoot(registry &reg);
        void level_system(registry &reg);
        void shoot_system_player(registry &reg);
        void shoot_system_ennemies(registry &reg);
        void kill_system(registry &reg);
        void win_system(registry &reg);
        void lose_system(registry &reg);
};

#endif /* SYSTEM_HPP_ */
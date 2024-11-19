#ifndef SYSTEM_HPP_
    #define SYSTEM_HPP_

    #include "Registry.hpp"

class System {
    public:
        void position_system(registry &reg);
        void control_system(registry &reg);
};

#endif /* SYSTEM_HPP_ */
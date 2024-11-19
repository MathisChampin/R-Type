#ifndef VELOCITY_HPP_
    #define VELOCITY_HPP_

namespace component {
    struct velocity {
        int x;
        int y;

        bool operator==(const velocity& other) const {
            return x == other.x && y == other.y;
        }
    };
}

#endif /* VELOCITY_HPP_ */
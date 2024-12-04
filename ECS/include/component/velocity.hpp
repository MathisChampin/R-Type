#ifndef VELOCITY_HPP_
    #define VELOCITY_HPP_

namespace component {
    struct velocity {
        float x;
        float y;

        bool operator==(const velocity& other) const {
            return x == other.x && y == other.y;
        }
    };
}

#endif /* VELOCITY_HPP_ */
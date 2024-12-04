#ifndef POSITION_HPP_
    #define POSITION_HPP_

namespace component {
    struct position {
        int x;
        int y;

        bool operator==(const position& other) const {
            return x == other.x && y == other.y;
        }
    };
}

#endif /* POSITION_HPP_ */
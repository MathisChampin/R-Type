#ifndef SIZE_HPP_
    #define SIZE_HPP_

namespace component {
    struct size {
        float x;
        float y;

        bool operator==(const size& other) const {
            return x == other.x && y == other.y;
        }
    };
}

#endif /* SIZE_HPP_ */
#ifndef CONTROLLABLE_HPP_
    #define CONTROLLABLE_HPP_

namespace component {
    struct controllable {
        enum Key {
            Up,
            Down,
            Right,
            Left,
            Shoot,
            Clear,
            NoKey,
        };
        Key active_key;
    };
}

#endif /* CONTROLLABLE_HPP_ */
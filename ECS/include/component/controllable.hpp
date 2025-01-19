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
            Shoot1,
            Shoot2,
            Shoot3,
            Shoot4,
            Shoot5,
            Shoot6,
            Clear,
            NoKey,
        };
        Key active_key;
    };
}

#endif /* CONTROLLABLE_HPP_ */
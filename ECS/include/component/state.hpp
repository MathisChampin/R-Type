#ifndef STATE_HPP_
    #define STATE_HPP_

namespace component {
    struct state {
        enum stateKey {
            Dead,
            Shoot,
            Alive
        };
        stateKey _stateKey;
    };
}

#endif /* STATE_HPP_ */
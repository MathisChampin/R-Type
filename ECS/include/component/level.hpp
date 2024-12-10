#ifndef LEVEL_HPP_
    #define LEVEL_HPP_

namespace component {
    struct level {
        enum levelKey {
            Level0,
            Level1,
            Level2,
            Level3,
            Level4,
            Level5,
            NoLevel
        };
        levelKey _levelKey;
    };
}

#endif /* LEVEL_HPP_ */
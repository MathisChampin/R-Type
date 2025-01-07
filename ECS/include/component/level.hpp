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
            Level6,
            Level7,
            Level8
        };
        levelKey _levelKey;
    };
}

#endif /* LEVEL_HPP_ */
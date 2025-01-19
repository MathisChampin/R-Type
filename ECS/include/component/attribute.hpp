#ifndef ATTRIBUTE_HPP_
    #define ATTRIBUTE_HPP_

namespace component {
    struct attribute {
        enum entityType {
            Player1,
            Player2,
            Player3,
            Player4,
            Ennemies,
            Ennemies2,
            Ennemies3,
            Ennemies4,
            Ennemies5,
            Shoot,
            Shoot1,
            Shoot2,
            Shoot3,
            Shoot4,
            Shoot5,
            Shoot6,
            Shoot7,
            Shoot8,
            Shoot9,
            Shoot10,
            Shoot11,
            Clear,
            PowerUpMove,
            PowerUpLife,
            None
        };
        entityType _type;
        bool operator==(const attribute& other) const {
            return _type == other._type;
        }
    };
}

#endif /* ATTRIBUTE_HPP_ */
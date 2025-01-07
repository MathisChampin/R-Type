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
            Shoot2,
            Shoot3,
            Shoot5,
            None
        };
        entityType _type;
        bool operator==(const attribute& other) const {
            return _type == other._type;
        }
    };
}

#endif /* ATTRIBUTE_HPP_ */
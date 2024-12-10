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
            Shoot,
            None
        };
        entityType _type;
        bool operator==(const attribute& other) const {
            return _type == other._type;
        }
    };
}

#endif /* ATTRIBUTE_HPP_ */
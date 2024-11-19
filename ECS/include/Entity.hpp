#ifndef ENTITY_HPP_
    #define ENTITY_HPP_

    #include <string>

class registry;

/**
 * @class Entity
 * @brief Represents an entity in an entity-component system.
 * An entity is a unique identifier used to attach and manage components in the system.
*/
class Entity {
public:
    /**
     * @brief Constructor to initialize an entity with a specific ID.
     * @param val The ID of the entity.
    */
    explicit Entity(size_t val): value{val} {};

    /**
     * @brief Converts the entity to its ID (of type size_t).
     * @return The ID of the entity.
    */
    operator size_t() const {
        return value;
    };

    /**
     * @brief Retrieves the ID of the entity.
     * @return The ID of the entity as a size_t.
    */
    size_t get_id() const {
        return value;
    };

private:
    size_t value; /**< The unique ID of the entity */
};

#endif /* ENTITY_HPP_ */
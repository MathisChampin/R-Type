#ifndef REGISTRY_HPP_
    #define REGISTRY_HPP_

    #include "SparseArray.hpp"
    #include "Entity.hpp"
    #include <typeindex>
    #include <unordered_map>
    #include <any>
    #include <functional>
    #include <stdexcept>

/**
 * @class registry
 * @brief Manages entities and their associated components in an entity-component system (ECS).
 * The registry allows for component registration, entity creation, component addition, and removal.
*/
class registry {
public:
    /**
     * @brief Registers a new component type with the registry.
     * If the component type is already registered, it will return the existing component array.
     * @tparam Component The component type to register.
     * @return A reference to the sparse array of the component type.
    */
    template <class Component>
    sparse_array<Component>& register_component() {
        auto type_index = std::type_index(typeid(Component));

        if (_components_arrays.find(type_index) == _components_arrays.end()) {
            _components_arrays[type_index] = std::make_any<sparse_array<Component>>();
            _remove_functions[type_index] = [this](registry&, Entity const& e) {
                this->remove_component<Component>(e);
            };
        }
        return std::any_cast<sparse_array<Component>&>(_components_arrays[type_index]);
    }

    /**
     * @brief Retrieves the sparse array of a specific component type.
     * @tparam Component The component type to retrieve.
     * @return A reference to the sparse array of the component type.
    */
    template <class Component>
    sparse_array<Component>& get_components() {
        return std::any_cast<sparse_array<Component>&>(_components_arrays[std::type_index(typeid(Component))]);
    }

    /**
     * @brief Retrieves an entity by its ID.
     * If the entity does not exist, an exception is thrown.
     * @param id The ID of the entity to retrieve.
     * @return The Entity corresponding to the given ID.
    */
    Entity get_entity(size_t id) const {
        auto it = std::find_if(_entities.begin(), _entities.end(), [id](const Entity& e) {
            return e.get_id() == id;
        });

        if (it != _entities.end()) {
            return *it;
        } else {
            throw std::runtime_error("Entity with ID " + std::to_string(id) + " does not exist.");
        }
    }

    /**
     * @brief Spawns a new entity and returns its ID.
     * If there are available entities, one will be reused. Otherwise, a new ID is generated.
     * @return A new entity with a unique ID.
    */
    Entity spawn_entity() {
        Entity id;
        if (_available_entities.empty()) {
            id = Entity(_next_entity_id++);
        } else {
            id = Entity(_available_entities.back().get_id());
            _available_entities.pop_back();
        }
    
        _entities.push_back(id);
        return id;
    }


    /**
     * @brief Kills an entity, removing it from the registry.
     * The entity is marked as available for reuse.
     * @param e The entity to kill.
    */
    void kill_entity(Entity const& e) {
        for (auto& func : _remove_functions) {
            func.second(*this, e);
        }
    
        auto it = std::find_if(_entities.begin(), _entities.end(), [&e](const Entity& entity) {
            return entity.get_id() == e.get_id();
        });
    
        if (it != _entities.end()) {
            _entities.erase(it);
        }
        _available_entities.push_back(e);
    }


    /**
     * @brief Adds a component to an entity by copying the provided component.
     * This function registers the component if it’s not already registered.
     * @tparam Component The type of the component to add.
     * @param to The entity to which the component is added.
     * @param c The component to add.
     * @return A reference to the added component.
    */
    template <typename Component>
    typename sparse_array<Component>::reference_type add_component(Entity const& to, Component&& c) {
        auto &array = register_component<Component>();
        return array.insert_at(to.get_id(), std::forward<Component>(c));
    }

    /**
     * @brief Adds a component to an entity by emplacing the component with provided parameters.
     * This function registers the component if it’s not already registered.
     * @tparam Component The type of the component to add.
     * @param to The entity to which the component is added.
     * @param params The parameters to construct the component.
     * @return A reference to the added component.
    */
    template <typename Component, typename... Params>
    typename sparse_array<Component>::reference_type emplace_component(Entity const& to, Params&&... params) {
        auto& array = register_component<Component>();
        return array.emplace_at(to.get_id(), std::forward<Params>(params)...);
    }

    /**
     * @brief Removes a component from an entity.
     * @tparam Component The type of the component to remove.
     * @param from The entity from which the component is removed.
    */
    template <typename Component>
    void remove_component(Entity const& from) {
        auto& array = get_components<Component>();
        array.erase(from.get_id());
    }

private:
    std::unordered_map<std::type_index, std::any> _components_arrays;
    std::unordered_map<std::type_index, std::function<void(registry&, Entity const&)>> _remove_functions;

    std::vector<Entity> _entities;
    std::vector<Entity> _available_entities;

    size_t _next_entity_id = 0;
};

#endif /* REGISTRY_HPP_ */
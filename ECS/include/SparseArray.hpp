#ifndef SPARSEARRAY_HPP_
#define SPARSEARRAY_HPP_

#include <vector>
#include <algorithm>
#include <utility>

template <typename Component>
class sparse_array {
    public:
        using value_type = Component;
        using reference_type = value_type&;
        using const_reference_type = value_type const&;
        using container_t = std::vector<value_type>;
        using size_type = typename container_t::size_type;
        using iterator = typename container_t::iterator;
        using const_iterator = typename container_t::const_iterator;

    public:
        /**
        * @brief Default constructor.
        * Initializes an empty sparse array.
        */
        sparse_array() = default;

        /**
         * @brief Copy constructor.
         * Creates a new sparse array as a copy of another.
         * @param other The sparse array to copy from.
        */
        sparse_array(sparse_array const& other) : _data(other._data) {}

        /**
         * @brief Move constructor.
         * Moves the data from another sparse array.
         * @param other The sparse array to move from.
        */
        sparse_array(sparse_array&& other) noexcept : _data(std::move(other._data)) {}

        /**
         * @brief Destructor.
         * Frees any allocated memory (if needed).
        */
        ~sparse_array() = default;

        /**
         * @brief Copy assignment operator.
         * Copies the data from another sparse array.
         * @param other The sparse array to copy from.
         * @return A reference to this sparse array.
        */
        sparse_array& operator=(sparse_array const& other) {
            if (this != &other)
                _data = other._data;
            return *this;
        }

        /**
         * @brief Move assignment operator.
         * Moves the data from another sparse array.
         * @param other The sparse array to move from.
         * @return A reference to this sparse array.
        */
        sparse_array& operator=(sparse_array&& other) noexcept {
            if (this != &other)
                _data = std::move(other._data);
            return *this;
        }

        /**
        * @brief Accesses an element at the specified index.
        * @param idx The index of the element.
        * @return A reference to the component at the given index.
        */
        reference_type operator[](size_t idx) {
            return _data[idx];
        }

        /**
         * @brief Accesses an element at the specified index (constant version).
         * @param idx The index of the element.
         * @return A constant reference to the component at the given index.
        */
        const_reference_type operator[](size_t idx) const {
            return _data[idx];
        }

        /**
         * @brief Returns an iterator to the beginning of the array.
         * @return An iterator pointing to the first element.
        */
        iterator begin() {
            return _data.begin();
        }

        /**
         * @brief Returns a constant iterator to the beginning of the array.
         * @return A constant iterator pointing to the first element.
        */
        const_iterator begin() const {
            return _data.begin();
        }

        /**
        * @brief Returns a constant iterator to the beginning of the array (const version).
        * @return A constant iterator pointing to the first element.
        */
        const_iterator cbegin() const {
            return _data.cbegin();
        }

        /**
         * @brief Returns an iterator to the end of the array.
         * @return An iterator pointing to the past-the-end element.
        */
        iterator end() {
            return _data.end();
        }

        /**
         * @brief Returns a constant iterator to the end of the array.
         * @return A constant iterator pointing to the past-the-end element.
        */
        const_iterator end() const {
            return _data.end();
        }

        /**
         * @brief Returns a constant iterator to the end of the array (const version).
         * @return A constant iterator pointing to the past-the-end element.
        */
        const_iterator cend() const {
            return _data.cend();
        }

        /**
         * @brief Returns the number of elements in the array.
         * @return The size of the array.
        */
        size_type size() const {
            return _data.size();
        }

        /**
         * @brief Inserts a component at a specific index.
         * If the index is beyond the current size, the component will be added at the end.
         * @param pos The index to insert at.
         * @param value The component to insert.
         * @return A reference to the inserted component.
        */
        reference_type insert_at(size_type pos, Component const& value) {
            if (pos >= _data.size()) {
                _data.push_back(value);
            } else {
                _data[pos] = value;
            }
            return _data[pos];
        }

        /**
        * @brief Inserts a component at a specific index (move version).
        * If the index is beyond the current size, the component will be added at the end.
        * @param pos The index to insert at.
        * @param value The component to insert (moved).
        * @return A reference to the inserted component.
        */
        reference_type insert_at(size_type pos, Component&& value) {
            if (pos >= _data.size()) {
                _data.push_back(std::move(value));
            } else {
                _data[pos] = std::move(value);
            }
            return _data[pos];
        }

        /**
         * @brief Emplaces a component at a specific index (in-place construction).
         * If the index is beyond the current size, the component will be added at the end.
         * @tparam Params The parameter types used to construct the component.
         * @param pos The index to emplace at.
         * @param params The parameters to construct the component.
         * @return A reference to the emplaced component.
        */
        template <class... Params>
        reference_type emplace_at(size_type pos, Params&&... params) {
            if (pos >= _data.size()) {
                _data.emplace_back(std::forward<Params>(params)...);
            } else {
                _data[pos].~value_type();
                new (&_data[pos]) value_type(std::forward<Params>(params)...);
            }
            return _data[pos];
        }

        /**
        * @brief Erases a component at a specific index.
        * @param pos The index of the component to erase.
        */
        void erase(size_type pos) {
            if (pos < _data.size()) {
                _data.erase(_data.begin() + pos);
            }
        }

        /**
         * @brief Gets the index of a component in the array (first match).
         * If the component is not found, returns the size of the array.
         * @param value The component to find.
         * @return The index of the component, or the size of the array if not found.
        */
        size_type get_index(value_type const& value) const {
            auto it = std::find(_data.begin(), _data.end(), value);
            if (it != _data.end()) {
                return std::distance(_data.begin(), it);
            }
            return _data.size();
        }

    private:
        container_t _data;
};

#endif /* SPARSEARRAY_HPP_ */

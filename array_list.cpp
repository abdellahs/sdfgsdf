#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath>

class ArrayList {
private:
    int* _data;
    int _capacity = 1;
    int _size = 0;

    // Method for increasing the capacity of the array
    void resize() {
        int new_capacity = _capacity * 2;
        int* new_data = new int[new_capacity];

        for (int i = 0; i < _size; i++)
            new_data[i] = _data[i];

        delete[] _data;

        _data = new_data;
        _capacity = new_capacity;
    }

    void shrink_to_fit() {
        int new_capacity = 1;

        while (new_capacity < _size) {
            new_capacity *= 2;
        }

        if (new_capacity == _capacity) {
            // No need to reduce, the capacity is already suitable.
            return;
        }

        int* new_data = new int[new_capacity];

        for (int i = 0; i < _size; i++) {
            new_data[i] = _data[i];
        }

        delete[] _data;
        _data = new_data;
        _capacity = new_capacity;
    }

public:
    // Default constructor
    ArrayList() {
        _data = new int[_capacity];
    }

    // Constructor for a list of values
    ArrayList(std::vector<int> values) {
        // Set the capacity to match the input size
        _capacity = values.size();
        _size = 0;  // Initialize size to 0

        // Allocate memory
        _data = new int[_capacity];

        // Copy elements from the vector
        for (int value : values) {
            append(value);
        }
    }

    // Destructor
    ~ArrayList() {
        delete[] _data;
    }

    // Length of array
    // Get the current size of the array
    int length() {
        return _size;
    }

    // Retrieve the array's maximum capacity
    int capacity() {
        return _capacity;
    }

    /**
     * @brief Append element to the end of the list
     *
     * @param n The value to be appended
     */
    void append(int value) {
        if (_size >= _capacity) {
            resize();
        }

        _data[_size++] = value;
    }

    /**
     * @brief Get value at a given index.
     * Throws a range error if the index is out of bounds
     *
     * @param index The index
     * @return int The value at that index
     */
    int get(int index) {
        if (index < 0 || index >= _size) {
            throw std::out_of_range("Index is out of bounds");
        }
        return _data[index];
    }

    /**
     * @brief Prints the array
     *
     */
    void print() {
        std::cout << "[";
        for (int i = 0; i < _size - 1; i++) {
            std::cout << _data[i] << ", ";
        }
        std::cout << _data[_size - 1] << "]\n";
    }

    /**
     * @brief Get a reference to the value at a given index.
     * Throws a range error if the index is out of bounds
     *
     * @param index The index
     * @return int The value at that index
     */
    int &operator[](int index) {
        if (index < 0 || index >= _size) {
            throw std::range_error("Index is out of bounds");
        }
        return _data[index];
    }

    /**
     * @brief get a value and an index.
     * throw an error if the index is out of bounds
     *
     * increase size by 1
     *
     * move values to the right of the index by one index up.
     *
     * @param val the value
     * @param index the index
     *
     */
    void insert(int value, int index) {
        if (index < 0 || index > _size) {
            throw std::out_of_range("Index is out of bounds");
        }

        if (_size >= _capacity) {
            resize();
        }

        if (index == _size) {
            append(value);
        } else {
            for (int i = _size; i > index; i--) {
                _data[i] = _data[i - 1];
            }
            _data[index] = value;
            _size++;
        }
    }

    /**
     * @brief deletes the element from the list.
     *
     * @param index the index
     *
     */
    void remove(int index) {
        if (index < 0 || index >= _size) {
            throw std::out_of_range("Index is out of bounds");
        }

        for (int i = index; i < _size - 1; i++) {
            _data[i] = _data[i + 1];
        }

        _size--;

        // Check if the array can be resized to fit if less than 25% of the allocated capacity is used
        if (_size < 0.25 * _capacity) {
            shrink_to_fit();
        }
    }

    /***
     * @brief removing an element at a given index
     *
     * @param index
     * @return int the value at that index
     */

    int pop(int index) {
        if (index < 0 || index >= _size) {
            throw std::out_of_range("Index is out of bounds");
        }

        int old_value = _data[index];

        // Move the elements to fill the gap left by the removed element
        for (int i = index; i < _size - 1; i++) {
            _data[i] = _data[i + 1];
        }

        _size--;

        // Check if the array can be resized to fit if less than 25% of the allocated capacity is used
        if (_size < 0.25 * _capacity) {
            shrink_to_fit();
        }

        return old_value;
    }

    /**
     * @brief removing the last element in the list
     *
     * @return int the last element
     */
    int pop() {
        if (_size == 0) {
            throw std::underflow_error("List is empty, cannot pop");
        }

        int old_value = _data[_size - 1];
        _size--;

        // Check if the array can be resized to fit if less than 25% of the allocated capacity is used
        if (_size < 0.25 * _capacity) {
            shrink_to_fit();
        }

        return old_value;
    }

    int max() {
        if (_size == 0) {
            throw std::underflow_error("List is empty, cannot find max");
        }

        int max_value = _data[0];

        for (int i = 1; i < _size; i++) {
            if (_data[i] > max_value) {
                max_value = _data[i];
            }
        }

        return max_value;
    }

    int min() {
        if (_size == 0) {
            throw std::underflow_error("List is empty, cannot find min");
        }

        int min_value = _data[0];

        for (int i = 1; i < _size; i++) {
            if (_data[i] < min_value) {
                min_value = _data[i];
            }
        }

        return min_value;
    }

    int argmax() {
        if (_size == 0) {
            throw std::underflow_error("List is empty, cannot find argmax");
        }

        int max_value = _data[0];
        int max_index = 0;

        for (int i = 1; i < _size; i++) {
            if (_data[i] > max_value) {
                max_value = _data[i];
                max_index = i;
            }
        }

        return max_index;
    }

    int argmin() {
        if (_size == 0) {
            throw std::underflow_error("List is empty, cannot find argmin");
        }

        int min_value = _data[0];
        int min_index = 0;

        for (int i = 1; i < _size; i++) {
            if (_data[i] < min_value) {
                min_value = _data[i];
                min_index = i;
            }
        }

        return min_index;
    }

    int count(int value) {
        int count = 0;

        for (int i = 0; i < _size; i++) {
            if (_data[i] == value) {
                count++;
            }
        }

        return count;
    }
};

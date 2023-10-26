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


#include <cassert>
#include <iostream>



/**
 * @brief Test that an empty array list has length zero
 *
 */
void test_empty_array_has_length_zero()
{
    ArrayList a{};
    std::cout << "Test that empty array has length zero";
    assert(a.length() == 0);
    std::cout << " - Success!\n";
}

/**
 * @brief Test the append method and the get method
 *
 */
void test_array_with_two_elements_appended_has_length_two()
{
    std::cout << "Test append";
    ArrayList a{};
    a.append(1);
    a.append(2);
    assert(a.length() == 2);
    assert(a.get(0) == 1);
    assert(a.get(1) == 2);
    std::cout << "- Success!\n";

}


/**
 * @brief Test that printing works
 *
 */
void test_print()
{
    std::cout << "Test print\n";
    ArrayList a{};
    a.append(1);
    a.append(2);
    a.print();
}

/**
 * @brief Test that we can construct an ArrayList from
 * a vector of integers
 *
 */
void test_vector_constructor()
{
    std::cout << "Test the vector constructor";
    ArrayList a{{1, 2, 3}};
    assert(a.length() == 3);
    assert(a.get(0) == 1);
    assert(a.get(1) == 2);
    assert(a.get(2) == 3);

    std::cout << " - Success!\n";
}

/**
 * @brief Test the indexing operator []
 * to both getting at setting values
 *
 */
void test_indexing_operator()
{
    std::cout << "Test the indexing operator";
    ArrayList a{{1, 2}};
    assert(a[0] == 1);
    assert(a[1] == 2);
    a[0] = 5;
    assert(a[0] == 5);
    std::cout << " - Success!\n";
}
/**
 * @brief Test that value can be inserted 
 * at given index.
 */
void test_insert()
{
    std::cout <<"Testing insert \n";
    ArrayList a{{0, 1}};
    assert(a.length() == 2);
    a.insert(42, 0);
    assert(a.length() == 3);
    assert(a[0] == 42);
    assert(a[1] == 0);
    assert(a[2] == 1);
    a.insert(43, 1);
    assert(a.length() == 4);
    assert(a[0] == 42);
    assert(a[1] == 43);
    assert(a[2] == 0);
    assert(a[3] == 1);
    a.insert(44, 4);
    assert(a.length() == 5);
    assert(a[0] == 42);
    assert(a[1] == 43);
    assert(a[2] == 0);
    assert(a[3] == 1);
    assert(a[4] == 44);
    std::cout << " - Success!\n";
}

/**
 * @brief Test that chosen value can be removed 
 * from the array
*/
void test_remove()
{
    std::cout << "Testing remove";
    ArrayList b{{10, 12, 13, 13, 24, 42}};
    assert(b.length() == 6);
    b.remove(1);
    assert(b.length() == 5);
    assert(b[0] == 10);
    assert(b[1] == 13);
    assert(b[2] == 13);
    assert(b[3] == 24);
    assert(b[4] == 42);
    b.remove(3);
    assert(b.length() == 4);
    assert(b[0] == 10);
    assert(b[1] == 13);
    assert(b[2] == 13);
    assert(b[3] == 42);
    std::cout << "- Success!\n";
}



/***
 * @brief Test that chosen element pops
*/
void test_pop_at_index()
{
    std::cout << "Testing pop at index";
    ArrayList a{{4, 5, 6, 9}};    
    assert (a.pop(1) == 5);
    assert(a[0] == 4);
    assert(a[1] == 6);
    assert(a[2] == 9);
    std::cout << "- Success\n";
}

/***
 * @brief Test that last element in list pop.
*/

void test_pop()
{
    std::cout << "Testing pop";
    ArrayList a{{4, 5, 6, 9}};    
    assert (a.pop() == 9);
    assert(a[0] == 4);
    assert(a[1] == 5);
    assert(a[2] == 6);
    std::cout << "- Success\n";
}



void test_capacity()
{
    std::cout << "Testing capacity";
    ArrayList a{};
    assert(a.capacity() == 1);
    a.append(3);
    a.append(4);
    assert(a.capacity() == 2);
    a.append(8);
    a.append(5);
    a.append(5);
    assert(a.capacity() == 8);
    std::cout << "- Success\n";

}

/***
 * @brief Test shrink_to_fit
*/

void test_shrink_to_fit_remove()
{
    std::cout << "Testing shrink to fit in remove method";
    ArrayList a{{}};

    for(int i = 0; i < 10; i++)
    {
        a.append(i);
    }
    assert(a.capacity() == 10);
    
    for (int i = 0; i < 7; i++)
    {
        a.remove(i);
    }
    assert(a.capacity() == 4);
    std::cout << "- Success\n";    
}

/**
 * @brief Test the min method to find the smallest element in the array
 */
void test_min()
{
    ArrayList a{{4, 2, 8, 1, 9}};
    assert(a.min() == 1);
    a.append(0);
    assert(a.min() == 0);
    a.append(-5);
    assert(a.min() == -5);
    std::cout << "Test min method - Success!" << std::endl;
}

void test_max()
{
    ArrayList a{{4, 2, 8, 1, 9}};
    assert(a.max() == 9);
    a.append(10);
    assert(a.max() == 10);
    a.append(3);
    assert(a.max() == 10);
    std::cout << "Test max method - Success!" << std::endl;
}

void test_argmax()
{
    ArrayList a{{4, 2, 8, 1, 9}};
    assert(a.argmax() == 4);
    a.append(10);
    assert(a.argmax() == 5);
    a.append(3);
    assert(a.argmax() == 5);
    std::cout << "Test argmax method - Success!" << std::endl;
}

void test_argmin()
{
    ArrayList a{{4, 2, 8, 1, 9}};
    assert(a.argmin() == 3);
    a.append(-5);
    assert(a.argmin() == 5);
    a.append(3);
    assert(a.argmin() == 5);
    std::cout << "Test argmin method - Success!" << std::endl;
}

void test_count()
{
    std::cout << "Testing count\n";
    ArrayList a{{1, 2, 3, 2, 4, 2}};
    assert(a.count(2) == 3);
    assert(a.count(4) == 1);
    assert(a.count(5) == 0);
    assert(a.count(1) == 1);
    std::cout << " - Success!\n";
}


void test_shrink_to_fit_pop()
{
    std::cout << "Testing shrink to fit in pop method";
    ArrayList a{{}};

    for(int i = 0; i < 10; i++)
    {
        a.append(i);
    }
    assert(a.capacity() == 16);
    
    for (int i = 0; i < 7; i++)
    {
        a.pop(i);
    }

    assert(a.capacity() == 4);
    std::cout << "- Success\n";
}

int main()
{
    
    test_empty_array_has_length_zero();
    test_array_with_two_elements_appended_has_length_two();
    test_print();
    test_vector_constructor();
    test_indexing_operator(); 
    test_insert();
    test_remove();
    test_pop_at_index();
    test_pop();
    test_min();
    test_max();
    test_argmax();
    test_argmin();
    test_count();
    test_capacity();
    test_shrink_to_fit_remove();
    test_shrink_to_fit_pop();

}

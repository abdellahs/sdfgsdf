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


#include <iostream>
#include <stdexcept>
#include <vector>

struct Node
{
    // The value at the node
    int value;
    // Pointer to the previous node; here default value nullpointer
    Node *prev = nullptr; 
    // Pointer to the next node; here default value nullpointer
    Node *next = nullptr; 
};

class LinkedList
{
  private:
    // Pointer to the first and last element in the list
    Node *head = nullptr;
    Node *tail = nullptr;
    // Size of the list
    int _size = 0;

    /**
     * @brief Check wheter the given index if out of
     * bound and throw a range error if it is
     *
     * @param index The index to be checked
     */
    void check_index_out_of_bounds(int index)
    {
        if ((index < 0) || (index >= length()))
            throw std::range_error("Index out of bounds");
    }

    /**
     * @brief Find the node at the given index
     *
     * @param index The index where you want the node
     * @return Node* A pointer to the node at the index
     */
    Node *find_node_at_index(int index)
    {
        Node *current = head;
        for (int i = 0; i < index; i++)
            current = current->next;
        return current;
    }

  public:
    // Default constructor
    LinkedList()
    {
    }

    // Constructor for a list of values
    LinkedList(std::vector<int> values)
    {
        for (int v : values)
            append(v);
    }

~LinkedList()
{
    Node *current = head;
    while (current != nullptr)
    {
        Node *next = current->next;
        delete current;
        current = next;
    }
}


    /**
     * @brief Return the length of the list
     *
     * @return int The length
     */
    int length()
    {
        return _size;
    }

    /**
     * @brief Append element to the end of the list
     *
     * @param val The value to be appended
     */
void append(int val)
{
    _size++;
    Node *newNode = new Node{val, tail, nullptr};
    if (head == nullptr)
    {
        // Hvis listen er tom, setter både hodet og halen til den nye noden.
        head = newNode;
        tail = newNode;
    }
    else
    {
        // Hvis listen ikke er tom, legger den nye noden til som "neste" for halen og oppdaterer halen til den nye noden.
        tail->next = newNode;
        tail = newNode;
    }
}


    /**
     * @brief Print values in the list
     *
     */
void print()
{
    std::cout << "[";
    Node *current = head;
    while (current != nullptr)
    {
        std::cout << current->value;
        if (current->next != nullptr)
        {
            std::cout << ", ";
        }
        current = current->next;
    }
    std::cout << "]\n";
}

    /**
     * @brief Get value at a given index
     *
     * @param index The index
     * @return int& Reference to the value at that index
     */
    int &operator[](int index)
    {
        check_index_out_of_bounds(index);
        Node *current = find_node_at_index(index);
        return current->value;
    }

    /**
     * @brief Add element to the beginning of the list
     *
     * @param val The value to be added
     */
void push_front(int val)
{
    Node *newNode = new Node{val, nullptr, head};
    if (head != nullptr) {
        head->prev = newNode;
    }
    head = newNode;

    if (tail == nullptr) {
        // Hvis listen er tom, oppdaterer vi også halen til å være den nye noden.
        tail = newNode;
    }

    _size++;
}



    /***
     * @brief Add element to index chosen
     * 
     * @param val The value to be added
     * @param index The index
    */
void insert(int val, int index)
{
    if (index <= 0)
    {
        push_front(val);
        return;
    }

    if (index >= _size)
    {
        append(val);
        return;
    }

    // Finn den gjeldende noden ved den valgte indeksen
    Node *current = find_node_at_index(index);

    // Opprett en ny node med de riktige pekerne
    Node *newNode = new Node{val, current->prev, current};

    // Oppdater pekerne for de omkringliggende noder
    current->prev->next = newNode;
    current->prev = newNode;

    _size++;
}


     /**
     * @brief deletes the element at given index from the Linked list.
     * 
     * @param index The index.
     *  
    */
void remove(int index)
{
    if (index < 0 || index >= _size)
    {
        throw std::out_of_range("Index out of bounds");
    }

    // Finn den gjeldende noden ved den valgte indeksen
    Node *current = find_node_at_index(index);

    if (index == 0)
    {
        // Hvis vi fjerner den første noden, oppdater hodet
        head = current->next;
        if (head != nullptr)
        {
            head->prev = nullptr;
        }
        else
        {
            // Hvis listen nå er tom, oppdater også halen
            tail = nullptr;
        }
    }
    else if (index == _size - 1)
    {
        // Hvis vi fjerner den siste noden, oppdater halen
        tail = current->prev;
        if (tail != nullptr)
        {
            tail->next = nullptr;
        }
        else
        {
            // Hvis listen nå er tom, oppdater også hodet
            head = nullptr;
        }
    }
    else
    {
        // Hvis vi fjerner en node i midten, oppdater pekerne for de omkringliggende nodene
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }

    // Slett den gjeldende noden
    delete current;
    _size--;
}


    /***
     * @brief removing element at index given
     * 
     * @param index
     * @return int the value at that index
    */
int pop(int index)
{
    if (index < 0 || index >= _size)
    {
        throw std::out_of_range("Index out of bounds");
    }

    Node *current = find_node_at_index(index);
    int value = current->value;
    remove(index);
    return value;
}

int pop()
{
    if (_size == 0)
    {
        throw std::out_of_range("List is empty");
    }

    int value = tail->value;
    remove(_size - 1);
    return value;
}


    int min()
    {
        if (_size == 0)
        {
            throw std::out_of_range("List is empty");
        }

        int minimum = head->value;
        Node *current = head->next;

        while (current != nullptr)
        {
            if (current->value < minimum)
            {
                minimum = current->value;
            }
            current = current->next;
        }

        return minimum;
    }

    int max()
    {
        if (_size == 0)
        {
            throw std::out_of_range("List is empty");
        }

        int maximum = head->value;
        Node *current = head->next;

        while (current != nullptr)
        {
            if (current->value > maximum)
            {
                maximum = current->value;
            }
            current = current->next;
        }

        return maximum;
    }

    // Test functions
    void test_min()
    {
        if (_size == 0)
        {
            throw std::out_of_range("List is empty");
        }

        int minValue = min();
        std::cout << "The minimum value in the list is: " << minValue << " - Success!\n";
    }

    void test_max()
    {
        if (_size == 0)
        {
            throw std::out_of_range("List is empty");
        }

        int maxValue = max();
        std::cout << "The maximum value in the list is: " << maxValue << " - Success!\n";
    }

};


#include <chrono>    // for high_resolution_clock
#include <fstream>   // for ofstream
#include <iostream>  // for cout
#include <stdexcept> // for runtime_error



using namespace std::chrono;

void run_array_list_get()
{
    std::cout << "\nArray list - get \n";
    std::ofstream ofs{"array_list_get.txt"};
    if (!ofs)
    {
        throw std::runtime_error("Unable to open file");
    }
    // Number of times we want to
    int runs = 1000;
    for (int N = 100; N < 1E6; N *= 10)
    {

        ArrayList ll{};
for (int i = 0; i < N; i++) {
    ll.append(i);
}
        auto start = high_resolution_clock::now();
        // Get value in the middle. 
for (int run = 0; run < runs; run++)
{
    auto middle_index = N / 2;
    auto value = ll[middle_index];
}
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        std::cout << N << " " << duration.count() / (double)runs << "\n";
        ofs << N << " " << duration.count() / (double)runs << "\n";
    }
}

void run_array_list_insert_front()
{
    std::cout << "Array list - insert front \n";
    std::ofstream ofs{"array_list_insert.txt"};
    if (!ofs)
    {
        throw std::runtime_error("Unable to open file");
    }
    for (int N = 100; N < 1E6; N *= 10)
    {
        auto start = high_resolution_clock::now();
        ArrayList a{};
        for (int i = 0; i < N; i++)
        {
            a.insert(i, 0);
        }

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        std::cout << N << " " << duration.count() / (double)N << "\n";
        ofs << N << " " << duration.count() / (double)N << "\n";
    }
}

void run_linked_list_get()
{
    std::cout << "\nLinked list - get \n";
    std::ofstream ofs{"linked_list_get.txt"};
    if (!ofs)
    {
        throw std::runtime_error("Unable to open file");
    }
    // Number of times we want to
    int runs = 1000;
    for (int N = 100; N < 1E6; N *= 10)
    {

        LinkedList ll{};
        for (int i = 0; i < N; i++)
        {
            ll.append(i);
        }
        auto start = high_resolution_clock::now();
        // Get value in the middle
for (int run = 0; run < runs; run++)
{
    auto middle_index = N / 2;
    auto value = ll[middle_index];
}

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        std::cout << N << " " << duration.count() / (double)runs << "\n";
        ofs << N << " " << duration.count() / (double)runs << "\n";
    }
}

void run_linked_list_insert_front()
{
    std::cout << "Linked list - insert front \n";
    std::ofstream ofs{"linked_list_insert.txt"};
    if (!ofs)
    {
        throw std::runtime_error("Unable to open file");
    }
    for (int N = 100; N < 1E6; N *= 10)
    {
        auto start = high_resolution_clock::now();
        LinkedList a{};
for (int i = N - 1; i >= 0; i--)
{
    a.insert(i, 0);
}

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        std::cout << N << " " << duration.count() / (double)N << "\n";
        ofs << N << " " << duration.count() / (double)N << "\n";
    }
}


int main()
{
    run_array_list_get();
    run_array_list_insert_front();
    run_linked_list_get();
    run_linked_list_insert_front();
    return 0;
}

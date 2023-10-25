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

    // Constructor 
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

   
    int length()
    {
        return _size;
    }

   
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
        if (head != nullptr)
        {
            head->prev = newNode;
        }
        head = newNode;

        if (tail == nullptr)
        {
            // Hvis listen er tom, oppdaterer vi også halen til å være den nye noden.
            tail = newNode;
        }

        _size++;
    }


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
     deletes the element at given index from the Linked list.
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

    /**
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

#include <cassert>
#include <iostream>

/**
 Test that empty list has length 0
*/
void test_empty_list_has_length_zero()
{
    std::cout << "Testing if empty list has length zero";
    LinkedList a{};
    assert(a.length() == 0);
    std::cout << " - Success!\n";
}

/**
 Test the append method and the indexing operator method
 */
void test_append()
{
    std::cout << "Testing append ";
    LinkedList ll{};
    ll.append(0);
    ll.append(1);
    if (ll[0] == 0 && ll[1] == 1) {
        std::cout << " - Success\n";
    } else {
        std::cout << " - Failed\n";
    }
}

/**
 Test that accesing an element outside of the
 * bounds throws a range error.
 
 */
void test_access_element_out_of_bounds_throw_range_error()
{
    std::cout << "Testing if it throws range error when elements are out of range ";
    LinkedList ll{};

    bool throwed_range_error = false;
    try
    {
        int x = ll[999];
    }
    catch (const std::range_error &e)
    {
        throwed_range_error = true;
    }
    assert(throwed_range_error);
    std::cout << " - Success!\n";
}

/**
 * Test that printing works
 *
 */
void test_print()
{
    std::cout << "Testing if print works \n";
    LinkedList ll{};
    ll.print();
    ll.append(1);
    ll.print();
    std::cout << " - Success!\n";
}

void test_index_operator()
{
    std::cout << "Testing index operator";
    LinkedList ll{{1, 2, 3, 4}};
    assert(ll[0] == 1);
    assert(ll[1] == 2);
    ll[2] = 5;
    assert(ll[2] == 5);
    assert(ll[3] == 4);
    std::cout << "- Success! \n";
}

void test_insert()
{
    std::cout << "Testing insert";
    LinkedList ll{{9, 8}};
    assert(ll.length() == 2);
    ll.insert(42, 0);
    assert(ll.length() == 3);
    assert(ll[0] == 42);
    assert(ll[1] == 9);
    assert(ll[2] == 8);
    ll.insert(43, 1);
    assert(ll.length() == 4);
    assert(ll[0] == 42);
    assert(ll[1] == 43);
    assert(ll[2] == 9);
    assert(ll[3] == 8);
    ll.insert(44, 4);
    assert(ll.length() == 5);
    assert(ll[0] == 42);
    assert(ll[1] == 43);
    assert(ll[2] == 9);
    assert(ll[3] == 8);
    assert(ll[4] == 44);
    std::cout << " - Success!\n";
}

/**
 * test that we can insert element at the front
 *
 */
void test_push_front()
{
    std::cout << "Testing push front ";
    LinkedList ll{{8, 7, 6}};
    ll.push_front(42);
    assert(ll.length() == 4);
    assert(ll[0] == 42);
    std::cout << " - Success!\n";
}

void test_vector_constructor()
{
    std::cout << "Testing vector constructor works ";
    LinkedList ll{{9, 8}};
    assert(ll[0] == 9);
    assert(ll[1] == 8);
    std::cout << " - Success!\n";
}

/**
 * Test that chosen value can be removed 
 * from the array
*/
void test_remove()
{
    std::cout << "Testing remove";
    LinkedList ll{{8, 7, 6, 5, 4}};
    ll.remove(4);
    assert(ll[0] == 8);
    assert(ll[1] == 7);
    assert(ll[2] == 6);
    assert(ll[3] == 5);
    ll.remove(2);
    assert(ll[0] == 8);
    assert(ll[1] == 7);
    assert(ll[2] == 5);
    std::cout << " - Success!\n";
}

/***
 * Test that chosen element pops
*/
void test_pop_at_index()
{
    std::cout << "Testing pop at index";
    LinkedList ll{{9, 8, 7, 6, 5}};
    ll.pop(4);
    assert (ll[0] == 9);
    assert(ll[1] == 8);
    assert(ll[2] == 7);
    assert(ll[3] == 6);
    ll.pop(2);
    assert(ll[0] == 9);
    assert(ll[1] == 8);
    assert(ll[2] == 6);
    std::cout << " - Success!\n";
}

/***
 * @brief 
*/
void test_pop()
{
    std::cout << "Testing pop";
    LinkedList ll{{9, 8, 7, 6, 5}};
    ll.pop();
    assert (ll[0] == 9);
    assert(ll[1] == 8);
    assert(ll[2] == 7);
    assert(ll[3] == 6);
    std::cout << " - Success!\n";
}

/**
 * Test that we can construct a LinkedList
 * from a vector of integers
 */
int main()
{
    LinkedList myList;
    myList.append(10);
    myList.append(5);
    myList.append(15);

    myList.test_min();
    myList.test_max();

    test_empty_list_has_length_zero();
    test_access_element_out_of_bounds_throw_range_error();
    test_append();
    test_print();
    test_insert();
    test_index_operator();
    test_push_front(); 
    test_remove();
    test_pop_at_index();
    test_pop();
    test_vector_constructor();
    return 0;
}

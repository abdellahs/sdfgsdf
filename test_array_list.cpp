
void test_empty_array_has_length_zero() {
    ArrayList a{};
    assert(a.length() == 0);
}



void test_array_with_two_elements_appended_has_length_two() {
    ArrayList a{};
    a.append(3);
    a.append(6);
    assert(a.length() == 2);
    assert(a.get(0) == 3);
    assert(a.get(1) == 6);
}

void test_print() {
    ArrayList a{};
    a.append(3);
    a.append(6);
    a.print();
}


}

void test_indexing_operator() {
    ArrayList a{{3, 6}};
    
    // Test reading
    assert(a[0] == 3);
    assert(a[1] == 6);

    // Test writing
    a[0] = 9;
    assert(a[0] == 9);
}

void test_vector_constructor() {
    ArrayList a{{3, 6, 3}};
    assert(a.length() == 3);
    assert(a.get(0) == 3);
    assert(a.get(1) == 6);
    assert(a.get(2) == 3);

void test_remove() {
    ArrayList b{{3, 6, 3, 6, 3, 6}};
    assert(b.length() == 6);
    b.remove(1);
    assert(b.length() == 5);
    assert(b[0] == 3);
    assert(b[1] == 3);
    assert(b[2] == 6);
    assert(b[3] == 3);
    assert(b[4] == 6);
    b.remove(3);
    assert(b.length() == 4);
    assert(b[0] == 3);
    assert(b[1] == 3);
    assert(b[2] == 6);
    assert(b[3] == 6);
}


void test_pop_at_index() {
    ArrayList a{{3, 6, 3, 6}};
    assert(a.pop(1) == 6);
    assert(a[0] == 3);
    assert(a[1] == 3);
    assert(a[2] == 6);
}

void test_pop() {
    ArrayList a{{3, 6, 3, 6}};
    assert(a.pop() == 6);
    assert(a[0] == 3);
    assert(a[1] == 6);
    assert(a[2] == 3);
}


void test_shrink_to_fit_remove() {
    ArrayList a{};
    for (int i = 0; i < 10; i++) {
        a.append(3);
    }
    assert(a.capacity() == 16);
    
    for (int i = 0; i < 7; i++) {
        a.remove(i);
    }
    assert(a.capacity() == 4);
}

void test_shrink_to_fit_pop() {
    ArrayList a{};
    for (int i = 0; i < 10; i++) {
        a.append(3);
    }
    assert(a.capacity() == 16);
    
    for (int i = 0; i < 7; i++) {
        a.pop(i);
    }
    assert(a.capacity() == 4);
}


void test_insert() {
    ArrayList a{{3, 6}};
    assert(a.length() == 2);
    a.insert(42, 0);
    assert(a.length() == 3);
    assert(a[0] == 42);
    assert(a[1] == 3);
    assert(a[2] == 6);
    a.insert(43, 1);
    assert(a.length() == 4);
    assert(a[0] == 42);
    assert(a[1] == 43);
    assert(a[2] == 3);
    assert(a[3] == 6);
    a.insert(44, 4);
    assert(a.length() == 5);
    assert(a[0] == 42);
    assert(a[1] == 43);
    assert(a[2] == 3);
    assert(a[3] == 6);
    assert(a[4] == 44);
}

void test_argmin() {
    ArrayList a{3, 6, 2, 8, 1};
    assert(a.argmin() == 4); // The minimum value 1 is at index 4.
}

void test_argmax() {
    ArrayList a{3, 6, 2, 8, 10};
    assert(a.argmax() == 4); // The maximum value 10 is at index 4.
}

void test_min() {
    ArrayList a{3, 6, 2, 8, 1};
    assert(a.min() == 1); // The smallest element is 1.
}

void test_max() {
    ArrayList a{3, 6, 2, 8, 10};
    assert(a.max() == 10); // The largest element is 10.
}


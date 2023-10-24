#include <iostream>
#include <stdexcept>

class ArrayList {
private:
    int* _data;
    int _capacity = 1;
    int _size = 0;

    // Metode for å øke kapasiteten til arrayen
    void resize() {
        int new_capacity = _capacity * 2;
        int* new_data = new int[new_capacity];  
        for (int i = 0; i < _size; i++)
            new_data[i] = _data[i];

        delete[] _data;

        _data = new_data;
        _capacity = new_capacity;
    }

    // Metode for å redusere kapasiteten til arrayen hvis nødvendig
    void shrink_to_fit() {
        int new_capacity = 1;
        while (new_capacity < _size) {
            new_capacity *= 2;
        }

        if (new_capacity == _capacity) {
            // Ingen behov for å redusere, kapasiteten er allerede passende.
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
    // Standard konstruktør
    ArrayList() {
        _data = new int[_capacity];
    }

    // Konstruktør som initialiserer fra en std::vector
    ArrayList(std::vector<int> values) {
        _size = values.size();
        _capacity = _size;

        _data = new int[_capacity];

        for (int i = 0; i < _size; i++) {
            _data[i] = values[i];
        }
    }

    // Destruktør for å frigjøre minnet til arrayen
    ~ArrayList() {
        delete[] _data;
    }

    // Returnerer lengden av arrayen
    int length() {
        return _size;
    }

    // Returnerer kapasiteten til arrayen
    int capacity() {
        return _capacity;
    }

    // Legger til et element i slutten av arrayen
    void append(int n) {
        if (_size >= _capacity)
            resize();

        _data[_size++] = n;
    }

    // Henter verdien på en spesifikk indeks
    int get(int index) {
        if (index < 0 || index >= _size) {
            throw std::out_of_range("Index is out of bounds");
        }
        return _data[index];
    }

    // Skriver ut arrayen til konsollen
    void print() {
        std::cout << "ArrayList([";
        for (int i = 0; i < _size - 1; i++) {
            std::cout << _data[i] << ", ";
        }
        std::cout << _data[_size - 1] << "])\n";
    }

    // Gir referanse til verdien på en spesifikk indeks
    int &operator[](int index) {
        if (index < 0 || index >= _size) {
            throw std::out_of_range("Index is out of bounds");
        }
        return _data[index];
    }

    // Setter inn et element på en spesifikk indeks
    void insert(int val, int index) {
        if (index < 0 || index > _size) {
            throw std::out_of_range("Index is out of bounds");
        }

        if (_size >= _capacity)
            resize();

        if (index == _size) {
            append(val);
            return;
        }

        for (int i = _size; i > index; i--) {
            _data[i] = _data[i - 1];
        }

        _data[index] = val;
        _size++;
    }

    // Fjerner et element på en spesifikk indeks
    void remove(int index) {
        if (index < 0 || index >= _size) {
            throw std::out_of_range("Index is out of bounds");
        }

        for (int i = index; i < _size - 1; i++) {
            _data[i] = _data[i + 1];
        }
        _size--;

        if (_size < 0.25f * _capacity)
            shrink_to_fit();
    }

    // Fjerner og returnerer et element på en spesifikk indeks
    int pop(int index) {
        if (index < 0 || index >= _size) {
            throw std::out_of_range("Index is out of bounds");
        }

        int old_value = _data[index];

        for (int i = index; i < _size - 1; i++) {
            _data[i] = _data[i + 1];
        }
        _size--;

        if (_size < 0.25f * _capacity)
            shrink_to_fit();

        return old_value;
    }

    // Fjerner og returnerer det siste elementet i arrayen
    int pop() {
        if (_size == 0) {
            throw std::underflow_error("Cannot pop from an empty list");
        }

        int old_value = _data[_size - 1];
        _size--;

        if (_size < 0.25f * _capacity)
            shrink_to_fit();

        return old_value;    
    }
};

/*
 * Реализовать дек с динамическим зацикленным буфером. Дек должен быть реализован в виде класса.
 */

#include <iostream>
#include <assert.h>
#include <sstream>

#define INITAL_SIZE 1

class Deque {
public:
    Deque(): capacity(INITAL_SIZE), size(0), head(0), tail(0) {buffer = new int[INITAL_SIZE];}
    ~Deque() {delete[] buffer;};

    void push_front(int element);
    void push_back(int element);
    int pop_front();
    int pop_back();

    bool empty() const {return (size == 0);}
private:
    void grow();

    int* buffer;
    int size;
    int capacity;
    int head;
    int tail;
};

void Deque::push_front(int element) {
    if (size + 1 > capacity) {
        grow();
    }
    head = head - 1 >= 0 ? head - 1 : capacity - 1;
    buffer[head] = element;
    ++size;

    if (size == 1) {
        tail = head;
    }
}
void Deque::push_back(int element) {
    if (size + 1 > capacity) {
        grow();
    }
    tail = (tail + 1) % capacity;
    buffer[tail] = element;
    ++size;

    if (size == 1) {
        head = tail;
    }
}
int Deque::pop_front() {
    if (empty()) {
        return -1;
    }
    int res = buffer[head];
    head = (head + 1) % capacity;
    --size;

    return res;
}
int Deque::pop_back() {
    if (empty()) {
        return -1;
    }
    int res = buffer[tail];
    tail = tail - 1 >= 0 ? tail - 1 : capacity - 1;
    --size;

    return res;
}
void Deque::grow() {
    int* new_buffer = new int[capacity * 2];

    int i = 0;
    while (i < size) {
        new_buffer[i++] = buffer[head];
        head = (head + 1) % capacity;
    }

    delete[] buffer;
    buffer = new_buffer;
    capacity *= 2;
    head = 0;
    tail = size - 1;
}

void run(std::istream &is, std::ostream &os) {
    Deque deque;

    int n;
    is >> n;
    for (int i = 0; i < n; ++i) {
        int a, b;
        is >> a >> b;
        switch (a) {
            case 1: {
                deque.push_front(b);
                break;
            }
            case 2: {
                if (deque.pop_front() != b) {
                    os << "NO" << std::endl;
                    return;
                }
                break;   
            }
            case 3: {
                deque.push_back(b);
                break;
            }
            case 4: {
                if (deque.pop_back() != b) {
                    os << "NO" << std::endl;
                    return;
                }
                break;
            }
        }
    }
    os << "YES" << std::endl;
}

void tests() {
    {
        std::stringstream input;
        std::stringstream output;

        input << "3" << std::endl;
        input << "1 44" << std::endl;
        input << "3 50" << std::endl;
        input << "2 44" << std::endl;

        run(input, output);

        assert(output.str() == "YES\n");
    }
    {
        std::stringstream input;
        std::stringstream output;

        input << "2" << std::endl;
        input << "2 -1" << std::endl;
        input << "1 10" << std::endl;

        run(input, output);

        assert(output.str() == "YES\n");
    }
    {
        std::stringstream input;
        std::stringstream output;

        input << "2" << std::endl;
        input << "3 44" << std::endl;
        input << "4 66" << std::endl;

        run(input, output);

        assert(output.str() == "NO\n");
    }
}

int main(void) {
    //tests();
    run(std::cin, std::cout);
    return 0;
}
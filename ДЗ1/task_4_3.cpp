/*
 * Планировщик процессов
 */

#include <iostream>
#include <assert.h>
#include <sstream>

#define INITIAL_SIZE 8

struct Process {
    int P;
    int t;
    int T;
};

struct ProcessComparator {
    bool operator()(const Process& l, const Process& r) {
        return (l.P * (l.t + 1) < r.P * (r.t + 1));
    }
};

template <class T>
struct DefaultComparator {
    bool operator() (const T& l, const T& r) const {
        return l < r;
    }
};

template <class T> 
void swap(T& l, T& r) {
    T t = l; 
    l = r; 
    r = t; 
}

template <class T, class Comparator = DefaultComparator<T>>
class Heap {
public:
    Heap(Comparator comp_ = Comparator()): size(0), capacity(INITIAL_SIZE), comp(comp_) {buffer = new T[INITIAL_SIZE];}
    Heap(T* array, size_t size_, Comparator comp_ = Comparator()): buffer(array), size(size_), capacity(size_), comp(comp_) {heapify();}
    ~Heap() {delete[] buffer;}

    Heap(const Heap&) = delete;
    Heap(Heap&&) = delete;
    Heap& operator= (const Heap&) = delete;
    Heap& operator= (Heap&&) = delete;

    const T& top() const {return buffer[0];}
    void pop();
    void push(const T& element);

    size_t get_size() const {return size;}
    bool empty() const {return size == 0;}

private:
    void sift_up(size_t idx);
    void sift_down(size_t idx);
    void grow();

    void heapify(); //делает кучу из массива O[n]

    T* buffer;
    size_t size;
    size_t capacity; //размер массива
    Comparator comp;
};

template <class T, class Comparator>
void Heap<T, Comparator>::pop() {
    if ( !empty() ) {
        buffer[0] = buffer[size - 1];
        --size;
        if ( !empty() ) {
            sift_down(0);
        }
    }
}
template <class T, class Comparator>
void Heap<T, Comparator>::push(const T& element) {
    if (size == capacity)
        grow();
    if (size < capacity && buffer != nullptr) {
        buffer[size++] = element;
    }

    sift_up(size - 1);
}
template <class T, class Comparator>
void Heap<T, Comparator>::sift_up(size_t idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if ( !comp(buffer[idx], buffer[parent]) ) //buffer[idx] >= buffer[parent]
            return;
        swap(buffer[idx], buffer[parent]);
        idx = parent;
    }
}
template <class T, class Comparator>
void Heap<T, Comparator>::sift_down(size_t idx) {
    while (2 * idx + 1 < size) {
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;    
        int j = left;
        if (right < get_size() && comp(buffer[right], buffer[left])) //buffer[right] < buffer[minimum]
            j = right;
        if (comp(buffer[idx], buffer[j]))
            break;
        swap(buffer[idx], buffer[j]);
        idx = j;
    }
}
template <class T, class Comparator>
void Heap<T, Comparator>::grow() {
    int new_capacity = capacity * 2;
    T* new_buffer = new T[new_capacity];
    for (int i = 0; i < size; ++i)
        new_buffer[i] = buffer[i];
    delete[] buffer;
    buffer = new_buffer;
    capacity = new_capacity;
}
template <class T, class Comparator>
void Heap<T, Comparator>::heapify() {
    for (size_t i = size / 2 - 1; i >= 0; --i)
        sift_down(i);
}

int find_count_switch(Heap<class Process, class ProcessComparator> &heap, size_t size) {
    int count_switch = 0;

    while (!heap.empty()) {
        Process top = heap.top();
        heap.pop();
        top.t += top.P;
        if (top.t < top.T) {
            heap.push(top);
        }
        ++count_switch;
    }

    return count_switch;
}

void run(std::istream &is, std::ostream &os) {
    size_t count_processes;
    is >> count_processes;

    Process* array = new Process[count_processes];
    Heap<Process, ProcessComparator> heap;

    for (int i = 0; i < count_processes; ++i) {
        Process process;
        process.t = 0;
        is >> process.P >> process.T;
        heap.push(process);
    }
    
    int result = find_count_switch(heap, count_processes);

    os << result;
}

int main(void) {
    run(std::cin, std::cout);
    return 0;
}
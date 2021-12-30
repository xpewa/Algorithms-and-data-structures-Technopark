/*
 * Дан массив целых чисел А[0..n-1]. 
 * Известно, что на интервале [0, m] значения массива строго возрастают, а на интервале [m, n-1] строго убывают. 
 * Найти m за O(log m). Требования:  Время работы O(log m). 
 * В этой задаче сначала нужно определить диапазон для бинарного поиска размером порядка m с помощью экспоненциального поиска, 
 * а потом уже в нем делать бинарный поиск.
 * 2 ≤ n ≤ 10000.
 */

#include <iostream>
#include <assert.h>
#include <sstream>

//Бинарный поиск в диапазоне [first;last), возвращает m или -1
int binarySearch(const int* array, int first, int last) {
    while (first < last) {
        int mid = (first + last) / 2;
        if (array[mid] > array[mid - 1] && array[mid] > array[mid + 1])
            return mid;
        else if (array[mid] > array[mid - 1])
            first = mid + 1;
            else
                last = mid;
    }
    return -1;
}

//Поиск диапазона и вызов binarySearch в нём
int findM(const int *array, const int size) {
    // 2 числа
    if (size == 2)
        return array[0] < array[1] ? 1 : 0;
    // Только возрастает
    if (array[size - 2] < array[size - 1])
        return size - 1;
    // Только убывает
    if (array[0] > array[1])
        return 0;
    int first = 1;
    int last = 2;
    while ((array[last-1] > array[last-2]) && first < size) {
        first *= 2;
        last *= 2;
        if (last > size)
            last = size;
    }
    return binarySearch(array, first-1, last);
}

void run(std::istream &is, std::ostream &os) {
    int n;
    is >> n;
    int* A = new int[n];
    assert(A != nullptr);
    for (int i = 0; i < n; ++i)
        is >> A[i];

    os << findM(A, n) << std::endl;

    delete[] A;
}

void tests() {
    {
        std::stringstream input;
        std::stringstream output;

        input << "19" << std::endl;
        input << "1 2 3 4 5 6 7 8 9 10 9 8 7 6 5 4 3 2 1" << std::endl;

        run(input, output);

        assert(output.str() == "9\n");
    }
    {
        std::stringstream input;
        std::stringstream output;

        input << "2" << std::endl;
        input << "2 1" << std::endl;

        run(input, output);

        assert(output.str() == "0\n");
    }
    {
        std::stringstream input;
        std::stringstream output;

        input << "3" << std::endl;
        input << "1 2 1" << std::endl;

        run(input, output);

        assert(output.str() == "1\n");
    }
    {
        std::stringstream input;
        std::stringstream output;

        input << "10" << std::endl;
        input << "-20 -1 0 50 60 100000 0 -100 -101 -100000" << std::endl;

        run(input, output);

        assert(output.str() == "5\n");
    }
    {
        std::stringstream input;
        std::stringstream output;

        input << "7" << std::endl;
        input << "10 20 30 40 50 60 70" << std::endl;

        run(input, output);

        assert(output.str() == "6\n");
    }
    {
        std::stringstream input;
        std::stringstream output;

        input << "7" << std::endl;
        input << "60 50 40 30 20 10 0" << std::endl;

        run(input, output);

        assert(output.str() == "0\n");
    }
    {
        std::stringstream input;
        std::stringstream output;

        input << "10000" << std::endl;
        for (int i = 0; i < 9000; ++i) {
            input << i << " ";
        }
        for (int i = 9000; i > 7999; --i) {
            input << i << " ";
        }
        input << std::endl;

        run(input, output);

        assert(output.str() == "9000\n");
    }
}

int main(void) {
    run(std::cin, std::cout);
    //tests();
    return 0;
}
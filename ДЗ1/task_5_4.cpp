/*
 * Закраска прямой 2.
 * На числовой прямой окрасили N отрезков. 
 * Известны координаты левого и правого концов каждого отрезка (Li и Ri). 
 * Найти сумму длин частей числовой прямой, окрашенных ровно в один слой.
 */

#include <iostream>
#include <sstream>

 template <typename T, typename Comparator = std::less<T>>
T* merge(T* array_1, T* array_2, int len_1, int len_2, Comparator cmp = Comparator()) {
    T* array = new T[len_1 + len_2];
    int i_array = 0, i_array_1 = 0, i_array_2 = 0;
    while (len_1 && len_2) {
        if (cmp(array_1[i_array_1], array_2[i_array_2])) {//array_1[i_array_1] < array_2[i_array_2]
            array[i_array] = array_1[i_array_1];
            ++i_array_1;
            --len_1;
        } 
        else {
            array[i_array] = array_2[i_array_2];
            ++i_array_2;
            --len_2;
        }
        ++i_array;
    }
    if (len_1 == 0)
        while (len_2 != 0) {
            array[i_array] = array_2[i_array_2];
            ++i_array;
            ++i_array_2;
            --len_2;
        }
    else
        while (len_1 != 0) {
            array[i_array] = array_1[i_array_1];
            ++i_array;
            ++i_array_1;
            --len_1;
        }
    return array;
}

template <typename T, typename Comparator = std::less<T>>
void merge_sort(T* mas, int size, Comparator cmp = Comparator()) {
    int right = 1;
    while (right < size) {
        int left = 0;
        while (left < size) {
            if (left + right >= size) 
                break;
            int ost = (left + right*2 > size) ? size - left - right : right;
            T* buffer;
            buffer = merge(&mas[left], &mas[left + right], right, ost, cmp);
            for (int i = 0; i < right + ost; ++i)
                mas[left + i] = buffer[i];
            delete[] buffer;
            left += right * 2;
        }
        right *= 2;
    }
}

struct Point {
    int point;
    int type; // начало (1) или конец отрезка (-1)
};

void run(std::istream &is, std::ostream &os) {
    int N;
    is >> N;
    if (N <= 0) {
        os << "0" << std::endl;
        return;
    }
    Point* array = new Point[N * 2];
    for (int i = 0; i < N * 2; ++i) {
        is >> array[i].point;
        array[i].type = (i % 2 == 0) ? 1 : -1;
    }

    merge_sort(array, N * 2, [](const Point &one, const Point &two) {return (one.point < two.point);});

    int result = 0;
    int prev = array[0].point;
    int paint_layer = 1;
    for (int i = 1; i < N * 2; ++i) {
        if (paint_layer == 1)
            result += array[i].point - prev;  
        prev = array[i].point;
        paint_layer += array[i].type; 
    }
    os << result << std::endl;

    delete[] array;
}

int main() {
    run(std::cin, std::cout);
    return 0;
}
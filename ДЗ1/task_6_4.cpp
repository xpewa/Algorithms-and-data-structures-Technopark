/*
 * Дано множество целых чисел из [0..10^9] размера n. 
 * Используя алгоритм поиска k-ой порядковой статистики, требуется найти следующие параметры множества:
 * 10%  перцентиль
 * медиана
 * 90%  перцентиль
 * Реализуйте стратегию выбора опорного элемента “случайный элемент”. 
 * Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.
 */

#include <iostream>
#include <sstream>
#include <time.h>

template <typename T, typename Comparator = std::less<T>>
int partition(T *array, int left, int right, Comparator cmp = Comparator()) {
    //Выбор опорного элемента, swap c последним
    srand(time(NULL));
    int pivot_pos = rand() % (right - left) + left;
    std::swap(array[pivot_pos], array[right - 1]);

    T pivot = array[right - 1];
    int i = right - 1;
    int j = right - 2;

    while (j >= left) {
        if ( !cmp(array[j], pivot) )
            std::swap(array[--i], array[j]);
        --j;
    }

    std::swap(array[i], array[right - 1]);

    return i;
}

template <typename T, typename Comparator = std::less<T>>
T find_kth_statistic(T *array, int size, int k, Comparator cmp = Comparator()) {
    int left = 0;
    int pivot_pos;
    while (left < size) {
        pivot_pos = partition(array, left, size, cmp);
        if (pivot_pos == k)
            return array[pivot_pos];
        if (pivot_pos > k)
            size = pivot_pos;
        else
            left = pivot_pos + 1;
    }
    return array[pivot_pos];
}

void run(std::istream &is, std::ostream &os) {
    int n;
    is >> n;
    int *array = new int[n];
    for (int i = 0; i < n; ++i)
        is >> array[i];

    os << find_kth_statistic(array, n, n * 0.1) << std::endl;
    os << find_kth_statistic(array, n, n / 2) << std::endl;
    os << find_kth_statistic(array, n, n * 0.9) << std::endl;

    delete[] array;
}

int main(void) {
    run(std::cin, std::cout);
    return 0;
}
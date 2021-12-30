/* 
 * Binary MSD для long long.
 * Дан массив неотрицательных целых 64-разрядных чисел. Количество чисел не больше 106. 
 * Отсортировать массив методом MSD по битам (бинарный QuickSort).
 */

#include <iostream>
#include <sstream>

#define SIZE_NUMBER 64

int bit(unsigned long long number, int digit) {
    return (number >> digit) & 1;
}

void sort_MSD(unsigned long long* array, int left, int right, int digit) {
    if (left >= right || left < 0 || digit < 0) {
        return;
    }

    int i = left;
    int j = right;

    while (i < j) {
        while (bit(array[i], digit) == 0 && (i < j)) {
            ++i;
        }
        while (bit(array[j], digit) == 1 && (i < j)) {
            --j;
        }

        std::swap(array[i], array[j]);
    }

    if (bit(array[i], digit) == 0) {
        sort_MSD(array, left, j, digit - 1);
        sort_MSD(array, i + 1, right, digit - 1);
    }
    else {
        sort_MSD(array, left, j - 1, digit - 1);
        sort_MSD(array, i, right, digit - 1);
    }
}

void run(std::istream &is, std::ostream &os) {
    int n;
    is >> n;
    unsigned long long* array = new unsigned long long[n];
    for (int i = 0; i < n; ++i)
        is >> array[i];

    sort_MSD(array, 0, n - 1, SIZE_NUMBER - 1);

    for (int i = 0; i < n; ++i)
        os << array[i] << " ";

    delete[] array;
}

int main(void) {
    run(std::cin, std::cout);
    return 0;
}
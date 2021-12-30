/*
 * Подсчитать кол-во единичных бит в входном числе, стоящих на четных позициях. Позиции битов нумеруются с 0.
 * Необходимо использование битовых операций. Использование арифметических операций запрещено.
 * Входное число лежит в диапазоне 0..2^32-1 и вводится в десятичном виде.
 */

#include <iostream>
#include <assert.h>
#include <sstream>

int countNumberOfBits(long long number) {
    unsigned count = 0; 
    int i = 1;
    while (number) {
        if ((number & 1) && (i > 0))
            for (unsigned mask = 1; (mask & (count ^= mask)) == 0; mask <<= 1); // ++count
        i = ~i; //меняем знак (1 или -2)
        number = number >> 1;
    }
    return count;
}

void run(std::istream &is, std::ostream &os) {
    long long number = 0;
    is >> number;
    os << countNumberOfBits(number) << std::endl;
}

void tests() {
    {
        std::stringstream input;
        std::stringstream output;

        input << "6" << std::endl;

        run(input, output);

        assert(output.str() == "1\n");
    }
    {
        std::stringstream input;
        std::stringstream output;

        input << "4294967295" << std::endl;

        run(input, output);

        assert(output.str() == "16\n");
    }
}

int main(void) {
    run(std::cin, std::cout);
    //tests();
    return 0;
}

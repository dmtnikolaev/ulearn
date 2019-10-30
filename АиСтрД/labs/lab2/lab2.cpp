#if SET_IMPL == 0
    #include "word.h"
#elif SET_IMPL == 1
    #include "bitarr.h"
#elif SET_IMPL == 2
    #include "arr.h"
#elif SET_IMPL == 3
    #include "list.h"
#else
    #error "unknown implementation"
#endif

#include <time.h>
#include <string>
#include <iostream>

const long kIterationsNum = 100000;

std::string Read(std::string prompt) {
    std::string str;

    std::cout << prompt;
    std::cin >> str;
    return str;
}

int main() {
    srand(time(nullptr));
    Set A(Read("A = "));
    Set B(Read("B = "));
    Set C(Read("C = "));
    Set D(Read("D = "));
    Set R;

    clock_t begin = clock();

    for (long q = 0; q < kIterationsNum; ++q) {
        R = (A | C) & ~(B | D);
    }

    clock_t end = clock();

    std::cout << "R = " << R.ToString() <<
        " Time = " << end - begin << "/" << kIterationsNum << std::endl;
    return 0;
}
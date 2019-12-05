#include "screen.h"

#include <iostream>

void Screen::Clear() {
    for (auto i = 0; i < kHeight; i++) {
        screen_[i][kWidth - 1] = '\0';
        for (auto j = 0; j < kWidth - 1; j++) {
            screen_[i][j] = '.';
        }
    }
}

void Screen::Print() {
    std::cout << std::endl;
    for (auto i = 0; i < kHeight; i++) {
        std::cout << screen_[i] << std::endl;
    }
}

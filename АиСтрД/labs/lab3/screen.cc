#include "screen.h"

#include <iostream>

void Screen::Clear() {
    for (auto i = 0; i < kmax_height_; i++) {
        screen_[i][kmax_width_ - 1] = '\0';
        for (auto j = 0; j < kmax_width_ - 1; j++) {
            screen_[i][j] = '.';
        }
    }
}

void Screen::Print() {
    std::cout << std::endl;
    for (auto i = 0; i < kmax_height_; i++) {
        std::cout << screen_[i] << std::endl;
    }
}

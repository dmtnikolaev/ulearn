#ifndef LAB3_SCREEN_H_
#define LAB3_SCREEN_H_

#include <iostream>

class Screen {
public:
    Screen() {
        Clear();
    }

    inline char symbol(int x, int y) { return screen_[x][y]; }
    inline void set_symbol(int x, int y, char c) { screen_[x][y] = c; }

    void Clear();
    void Print();

private:
    static const int kmax_height_ = 8;
    static const int kmax_width_ = 80;

    char screen_[kmax_height_][kmax_width_];
};

#endif  // LAB3_SCREEN_H_

#ifndef LAB3_SCREEN_H_
#define LAB3_SCREEN_H_

#include <iostream>

class Screen {
public:
    static const int kHeight = 5;
    static const int kWidth = 80;

    Screen() {
        Clear();
    }

    void SetSymbol(int x, int y, char c) {
        screen_[x][y] = c;
    }
    void Clear();
    void Print();

private:
    char screen_[kHeight][kWidth];
};

#endif  // LAB3_SCREEN_H_

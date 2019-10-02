#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <string>
#include <tuple>
#include <climits>

using namespace std;

typedef unsigned short WORD;
const size_t WORD_MAX = SHRT_MAX;

const int UNIVERSUM_LEN = 16;
const char UNIVERSUM[] = "1234567890ABCDEF";

WORD DoEvaluation(WORD A, WORD B, WORD C, WORD D) {
    return (A | C) & ~(B | D);
}

string ReadHex(string prompt) {
    string str;

    cout << prompt;
    cin >> str;
    return str;
}

WORD ToSet(const string& hex_array) {
    WORD word = 0;
    for (auto c : hex_array) {
        WORD current_bit = 1;
        for (auto i = 0; i < UNIVERSUM_LEN; ++i) {
            if (c == UNIVERSUM[i]) {
                word |= current_bit;
            }
            current_bit <<= 1;
        }
    }

    return word;
}

string ToString(WORD arr) {
    string str;
    WORD current_bit = 1;
    for (auto i = 0; i < UNIVERSUM_LEN; ++i) {
        if (arr & current_bit) {
            str += UNIVERSUM[i];
        }
        current_bit <<= 1;
    }
    if (str.length() == 0) {
        str = "-";
    }
    return str;
}

int ReadMode() {
    cout << "Choose program mode:" << endl;
    cout << "1 - Random input" << endl;
    cout << "2 - Last random" << endl;
    cout << "3 - Read input" << endl;

    int mode = -1;
    cout << "> ";
    cin >> mode;

    return mode;
}

WORD GenerateSet() {
    return rand() % static_cast<int>(WORD_MAX + 1);
}

std::tuple<WORD, WORD, WORD, WORD> GenerateInput() {
    auto A = GenerateSet();
    auto B = GenerateSet();
    auto C = GenerateSet();
    auto D = GenerateSet();

    cout << "A: " << ToString(A) << endl;
    cout << "B: " << ToString(B) << endl;
    cout << "C: " << ToString(C) << endl;
    cout << "D: " << ToString(D) << endl;

    return { A, B, C, D };
}

std::tuple<WORD, WORD, WORD, WORD> ReadInputFromUser() {
    auto A = ToSet(ReadHex("A: "));
    auto B = ToSet(ReadHex("B: "));
    auto C = ToSet(ReadHex("C: "));
    auto D = ToSet(ReadHex("D: "));

    return { A, B, C, D };
}

int main() {
    WORD A, B, C, D;

    auto mode = ReadMode();

    switch (mode) {
        case 1: 
            srand(time(nullptr));
            [[fallthrough]];
        case 2:
            tie(A, B, C, D) = GenerateInput();
            break;
        case 3:
            tie(A, B, C, D) = ReadInputFromUser();
            break;
        default:
            cout << "Invalid mode" << endl;
            return 0;
    }

    auto res = ToString(DoEvaluation(A, B, C, D));

    cout << "(A | C) & !(B | D): "
         << res
         << endl;

    return 0;
}

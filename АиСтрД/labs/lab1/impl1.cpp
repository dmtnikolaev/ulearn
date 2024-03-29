#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <string>
#include <array>
#include <tuple>

using namespace std;

const int MAX_LEN = 16;
const char UNIVERSUM[] = { "1234567890ABCDEF" };

array<int, MAX_LEN> DoEvaluation(const array<int, MAX_LEN> A,
                                  const array<int, MAX_LEN> B,
                                  const array<int, MAX_LEN> C,
                                  const array<int, MAX_LEN> D) {
    array<int, MAX_LEN> res = { 0 };
    for (auto i = 0; i < MAX_LEN; ++i) {
        res[i] = (A[i] || C[i]) && !(B[i] || D[i]);
    }
    return res;
}

string ReadHex(string prompt) {
    string str;

    cout << prompt;
    cin >> str;
    return str;
}

array<int, MAX_LEN> ToSet(const string& hex_array) {
    array<int, MAX_LEN> arr = { 0 };
    for (auto c : hex_array) {
        for (auto i = 0; i < MAX_LEN; ++i) {
            if (c == UNIVERSUM[i]) {
                arr[i] = 1;
            }
        }
    }

    return arr;
}

string ToString(array<int, MAX_LEN> arr) {
    string str;
    for (auto i = 0; i < MAX_LEN; ++i) {
        if (arr[i]) {
            str += UNIVERSUM[i];
        }
    }
    return str;
}

int ReadMode() {
    cout << "Choose program mode:" << endl;
    cout << "1 - Benchmark" << endl;
    cout << "2 - Random input" << endl;
    cout << "3 - Last random" << endl;
    cout << "4 - Read input" << endl;

    int mode = -1;
    cout << "> ";
    cin >> mode;

    return mode;
}

array<int, MAX_LEN> GenerateSet() {
    static_assert(MAX_LEN <= numeric_limits<unsigned char>::digits*sizeof(int),
        "MAX_LEN should be less than or equal to the count of bits in int.");

    int random_bits = rand();
    array<int, MAX_LEN> res;

    for (auto i = 0; i < MAX_LEN; i++) {
        res[i] = random_bits & (1 << i);
    }

    return res;
}

auto GenerateInput() {
    auto A = GenerateSet();
    auto B = GenerateSet();
    auto C = GenerateSet();
    auto D = GenerateSet();

    cout << "A: " << ToString(A) << endl;
    cout << "B: " << ToString(B) << endl;
    cout << "C: " << ToString(C) << endl;
    cout << "D: " << ToString(D) << endl;

    return make_tuple(A, B, C, D);
}

auto ReadInputFromUser() {
    auto A = ToSet(ReadHex("A: "));
    auto B = ToSet(ReadHex("B: "));
    auto C = ToSet(ReadHex("C: "));
    auto D = ToSet(ReadHex("D: "));

    return make_tuple(A, B, C, D );
}

int main() {
    array<int, MAX_LEN> A, B, C, D;
    auto n_repetitions = 1;

    auto mode = ReadMode();

    switch (mode) {
        case 1:
            n_repetitions = 100000;
            [[fallthrough]];
        case 2:
            srand(time(nullptr));
            [[fallthrough]];
        case 3:
            tie(A, B, C, D) = GenerateInput();
            break;
        case 4:
            tie(A, B, C, D) = ReadInputFromUser();
            break;
        default:
            cout << "Invalid mode" << endl;
            return 0;
    }

    auto clk_begin = clock();

    array<int, MAX_LEN> res;
    for (auto i = 0; i < n_repetitions; i++) {
        res = DoEvaluation(A, B, C, D);
    }

    if (mode == 1) {
        auto clk_end = clock();
        cout << "Elapsed time: "
             << clk_end - clk_begin
             << endl;
    }

    auto res_str = ToString(res);
    cout << "(A | C) & !(B | D): "
         << res_str
         << endl;

    return 0;
}

#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <string>
#include <array>
#include <tuple>

using namespace std;

const int MAX_LEN = 16;
const char UNIVERSUM[] = { "1234567890ABCDEF" };

bool Set_Contains(const array<char, MAX_LEN> A, char a) {
    for (auto i = 0; A[i] != 0; i++) {
        if (A[i] == a) {
            return true;
        }
    }
    return false;
}

array<char, MAX_LEN> Set_Union(const array<char, MAX_LEN> A,
                               const array<char, MAX_LEN> B) {
    array<char, MAX_LEN> res;
    auto res_len = 0;

    for (auto i = 0; A[i] != 0; i++) {
        res[res_len] = A[i];
        res_len++;
    }

    for (auto i = 0; B[i] != 0; i++) {
        if (!Set_Contains(res, B[i])) {
            res[res_len] = B[i];
            res_len++;
        }
    }

    res[res_len] = '\0';

    return res;
}

array<char, MAX_LEN> Set_Subtract(const array<char, MAX_LEN> A,
                                   const array<char, MAX_LEN> B) {
    auto res_len = 0;
    array<char, MAX_LEN> res;
    for (auto i = 0; A[i] != 0; i++) {
        if (!Set_Contains(B, A[i])) {
            res[res_len] = A[i];
            res_len++;
        }
    }

    res[res_len] = '\0';

    return res;
}

array<char, MAX_LEN> DoEvaluation(const array<char, MAX_LEN> A,
                                  const array<char, MAX_LEN> B,
                                  const array<char, MAX_LEN> C,
                                  const array<char, MAX_LEN> D) {
    auto A_or_C = Set_Union(A, C);
    auto B_or_D = Set_Union(B, D);
    return Set_Subtract(A_or_C, B_or_D);
}

string ReadHex(string prompt) {
    string str;

    cout << prompt;
    cin >> str;
    return str;
}

array<char, MAX_LEN> ToSet(const string& hex_array) {
    bool used_symbols[MAX_LEN] = { false };
    array<char, MAX_LEN> arr = { 0 };
    
    auto i = 0;
    for (auto c : hex_array) {
        auto universum_index = c <= '9'
                                    ? c -'0'
                                    : c - 'A' + 10;
        if (!used_symbols[universum_index]) {
            arr[i] = c;
            i++;
            used_symbols[universum_index] = true;
        }
    }

    return arr;
}

string ToString(array<char, MAX_LEN> arr) {
    return string(arr.data());
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

array<char, MAX_LEN> GenerateSet() {
    static_assert(MAX_LEN <= numeric_limits<unsigned char>::digits*sizeof(int),
        "MAX_LEN should be less than or equal to the count of bits in int.");

    array<char, MAX_LEN> res { 0 };
    auto i = 0;
    for (auto x : UNIVERSUM) {
        auto should_add_x = rand() < RAND_MAX/2;
        if (should_add_x) {
            res[i] = x;
            i++;
        }
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
    array<char, MAX_LEN> A, B, C, D;
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

    array<char, MAX_LEN> res;
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

#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <string>
#include <array>
#include <tuple>

using namespace std;

const int MAX_LEN = 16;
const char UNIVERSUM[] = { "1234567890ABCDEF" };

bool ContainsArray(const array<char, MAX_LEN> A, char a) {
    for (auto i = 0; A[i] != 0; i++) {
        if (A[i] == a) {
            return true;
        }
    }
    return false;
}

array<char, MAX_LEN> UnionArray(const array<char, MAX_LEN> A,
                                const array<char, MAX_LEN> B) {
    array<char, MAX_LEN> res;
    auto res_len = 0;

    for (auto i = 0; A[i] != 0; i++) {
        res[res_len] = A[i];
        res_len++;
    }

    for (auto i = 0; B[i] != 0; i++) {
        if (!ContainsArray(res, B[i])) {
            res[res_len] = B[i];
            res_len++;
        }
    }

    res[res_len] = '\0';

    return res;
}

array<char, MAX_LEN> SubtractArray(const array<char, MAX_LEN> A,
                                   const array<char, MAX_LEN> B) {
    auto res_len = 0;
    array<char, MAX_LEN> res;
    for (auto i = 0; A[i] != 0; i++) {
        if (!ContainsArray(B, A[i])) {
            res[res_len] = A[i];
            res_len++;
        }
    }

    res[res_len] = '\0';

    return res;
}

array<char, MAX_LEN> EvaluateArray(const array<char, MAX_LEN> A,
                                   const array<char, MAX_LEN> B,
                                   const array<char, MAX_LEN> C,
                                   const array<char, MAX_LEN> D) {
    auto A_or_C = UnionArray(A, C);
    auto B_or_D = UnionArray(B, D);
    return SubtractArray(A_or_C, B_or_D);
}

string ReadHex(string prompt) {
    string str;

    cout << prompt;
    cin >> str;
    return str;
}

array<char, MAX_LEN> ToSymbolArray(const string& hex_array) {
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
    cout << "1 - Random input" << endl;
    cout << "2 - Last random" << endl;
    cout << "3 - Read input" << endl;

    int mode = -1;
    cout << "> ";
    cin >> mode;

    return mode;
}

array<char, MAX_LEN> GenerateSymbolArray() {
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
    auto A = GenerateSymbolArray();
    auto B = GenerateSymbolArray();
    auto C = GenerateSymbolArray();
    auto D = GenerateSymbolArray();

    cout << "A: " << ToString(A) << endl;
    cout << "B: " << ToString(B) << endl;
    cout << "C: " << ToString(C) << endl;
    cout << "D: " << ToString(D) << endl;

    return make_tuple(A, B, C, D);
}

auto ReadInputFromUser() {
    auto A = ToSymbolArray(ReadHex("A: "));
    auto B = ToSymbolArray(ReadHex("B: "));
    auto C = ToSymbolArray(ReadHex("C: "));
    auto D = ToSymbolArray(ReadHex("D: "));

    return make_tuple(A, B, C, D );
}

int main() {
    array<char, MAX_LEN> A, B, C, D;

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

    auto res = ToString(EvaluateArray(A, B, C, D));

    cout << "(A | C) & !(B | D): "
         << res
         << endl;

    return 0;
}

#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <string>
#include <array>
#include <tuple>

using namespace std;

const int MAX_LEN = 16;
const char UNIVERSUM[] = { "1234567890ABCDEF" };

array<int, MAX_LEN> EvaluateArray(const array<int, MAX_LEN> A,
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

array<int, MAX_LEN> ToBitArray(const string& hex_array) {
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
    cout << "1 - Random input" << endl;
    cout << "2 - Last random" << endl;
    cout << "3 - Read input" << endl;

    int mode = -1;
    cout << "> ";
    cin >> mode;

    return mode;
}

array<int, MAX_LEN> GenerateBitArray() {
    static_assert(MAX_LEN <= numeric_limits<unsigned char>::digits*sizeof(int),
        "MAX_LEN should be less than or equal to the count of bits in int.");

    int random_bits = rand();
    array<int, MAX_LEN> res;

    cout << random_bits << endl;

    for (auto i = 0; i < MAX_LEN; i++) {
        res[i] = random_bits & (1 << i);
    }

    return res;
}

auto GenerateInput() {
    auto A = GenerateBitArray();
    auto B = GenerateBitArray();
    auto C = GenerateBitArray();
    auto D = GenerateBitArray();

    cout << "A: " << ToString(A) << endl;
    cout << "B: " << ToString(B) << endl;
    cout << "C: " << ToString(C) << endl;
    cout << "D: " << ToString(D) << endl;

    return make_tuple(A, B, C, D);
}

auto ReadInputFromUser() {
    auto A = ToBitArray(ReadHex("A: "));
    auto B = ToBitArray(ReadHex("B: "));
    auto C = ToBitArray(ReadHex("C: "));
    auto D = ToBitArray(ReadHex("D: "));

    return make_tuple(A, B, C, D );
}

int main() {
    array<int, MAX_LEN> A, B, C, D;

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

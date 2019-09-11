#include <iostream>
#include <string>
#include <array>

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
    array<int, MAX_LEN> arr = {0 };
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

int main() {
    auto A = ToBitArray(ReadHex("A: "));
    auto B = ToBitArray(ReadHex("B: "));
    auto C = ToBitArray(ReadHex("C: "));
    auto D = ToBitArray(ReadHex("D: "));

    auto res = ToString(EvaluateArray(A, B, C, D));

    cout << "(A | C) & !(B | D)"
         << endl
         << res;

    return 0;
}
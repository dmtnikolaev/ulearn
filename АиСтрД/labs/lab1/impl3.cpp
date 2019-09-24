#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <string>
#include <array>
#include <tuple>
#include <functional>

using namespace std;

const int MAX_LEN = 16;
const char UNIVERSUM[] = { "1234567890ABCDEF" };

struct Set {
    char val;
    Set* next;
};

Set* Set_New(char v, Set* next) {
    return new Set { v, next };
}

Set* Set_New(char v) {
    return Set_New(v, nullptr);
}

void Set_Delete(Set* a) {
    while (a != nullptr) {
        auto tmp = a->next;
        delete a;
        a = tmp;
    }
}

Set* Set_Add(Set* a, char v) {
    if (a == nullptr) {
        return Set_New(v);
    }

    auto a_el = a;
    while (a_el->next != nullptr) {
        a_el = a_el->next;
    }
    a_el->next = Set_New(v);

    return a;
}

bool Set_Contains(const Set* a, char v) {
    while (a != nullptr) {
        if (a->val == v) {
            return true;
        }
        a = a->next;
    }
    return false;
}

Set* Set_Union(const Set* a, const Set* b) {
    Set* c = nullptr;

    while (a != nullptr) {
        c = Set_Add(c, a->val);
        a = a->next;
    }

    while (b != nullptr) {
        if (!Set_Contains(c, b->val)) {
            c = Set_Add(c, b->val);
        }
        b = b->next;
    }

    return c;
}

Set* Set_Substr(const Set* a, const Set* b) {
    Set* c = nullptr;
    while (a != nullptr) {
        if (!Set_Contains(b, a->val)) {
            c = Set_Add(c, a->val);
        }
        a = a->next;
    }
    return c;
}

string Set_ToString(const Set& a) {
    string str;
    auto a_el = &a;
    while (a_el != nullptr) {
        str += a_el->val;
        a_el = a_el->next;
    }
    return str;
}

Set* EvaluateSet(const Set* A, const Set* B,
                 const Set* C, const Set* D) {
    auto A_and_C = Set_Union(A, C);
    auto B_and_D = Set_Union(B, D);
    auto res = Set_Substr(A_and_C, B_and_D);

    Set_Delete(A_and_C);
    Set_Delete(B_and_D);

    return res;
}

string ReadHex(string prompt) {
    string str;

    cout << prompt;
    cin >> str;
    return str;
}

Set* ToList(const string& hex_array) {
    Set* set = nullptr;
    for (auto c : hex_array) {
        set = Set_Add(set, c);
    }

    return set;
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

Set* GenerateSet() {
    Set* set = nullptr;
    // Создаем множество размером не больше универсума.
    for (auto x : UNIVERSUM) {
        auto should_add_x = rand() < RAND_MAX/2;
        if (should_add_x) {
            set = Set_Add(set, x);
        }
    }
    return set;
}

auto GenerateInput() {
    auto A = GenerateSet();
    auto B = GenerateSet();
    auto C = GenerateSet();
    auto D = GenerateSet();

    cout << "A: " << Set_ToString(*A) << endl;
    cout << "B: " << Set_ToString(*B) << endl;
    cout << "C: " << Set_ToString(*C) << endl;
    cout << "D: " << Set_ToString(*D) << endl;

    return make_tuple(A, B, C, D);
}

auto ReadInputFromUser() {
    auto A = ToList(ReadHex("A: "));
    auto B = ToList(ReadHex("B: "));
    auto C = ToList(ReadHex("C: "));
    auto D = ToList(ReadHex("D: "));

    return make_tuple(A, B, C, D );
}

int main() {
    Set * A,
        * B,
        * C,
        * D;

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

    auto res = EvaluateSet(A, B, C, D);
    auto res_str = Set_ToString(*res);

    cout << "(A | C) & !(B | D): "
         << res_str
         << endl;

    Set_Delete(A);
    Set_Delete(B);
    Set_Delete(C);
    Set_Delete(D);
    Set_Delete(res);

    return 0;
}

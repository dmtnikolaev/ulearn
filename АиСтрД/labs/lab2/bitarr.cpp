#if SET_IMPL == 1

#include "bitarr.h"

#include <string>

Set::Set(const std::string &str) {
    for (auto c : str) {
        for (auto i = 0; i < kUniversumPower_; ++i) {
            if (c == kUniversum_[i]) {
                bitArray_[i] = 1;
            }
        }
    }
}

Set::Set() {

}

Set::Set(const Set &set) {
    for (auto i = 0; i < kUniversumPower_; ++i) {
        bitArray_[i] = set.bitArray_[i];
    }
}

Set::Set(const int *bits) {
    for (auto i = 0; i < kUniversumPower_; ++i) {
        bitArray_[i] = bits[i];
    }
}

Set Set::operator|(const Set &set) const {
    int res[kUniversumPower_] = {0};

    for (auto i = 0; i < kUniversumPower_; ++i) {
        res[i] = bitArray_[i] || set.bitArray_[i];
    }

    return Set(res);
}

Set Set::operator&(const Set &set) const {
    int res[kUniversumPower_] = {0};

    for (auto i = 0; i < kUniversumPower_; ++i) {
        res[i] = bitArray_[i] && set.bitArray_[i];
    }

    return Set(res);
}

Set Set::operator~() const {
    int res[kUniversumPower_] = {0};

    for (auto i = 0; i < kUniversumPower_; ++i) {
        if (bitArray_[i]) {
            res[i] = 0;
        }
        else {
            res[i] = 1;
        }
    }

    return Set(res);
}

Set Set::operator=(const Set &set) {
    if (this != &set) {
        for (auto i = 0; i < kUniversumPower_; ++i) {
            bitArray_[i] = set.bitArray_[i];
        }
    }

    return *this;
}

std::string Set::ToString() const {
    std::string str;
    for (auto i = 0; i < kUniversumPower_; ++i) {
        if (bitArray_[i]) {
            str += kUniversum_[i];
        }
    }
    return str;
}

#endif
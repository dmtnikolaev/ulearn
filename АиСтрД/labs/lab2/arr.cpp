#if SET_IMPL == 2

#include "arr.h"

#include <string>

Set::Set(const std::string &str) {
    auto res_len = 0;

    for (auto i = 0; i < kUniversumPower_; ++i) {
        if (StringContains(str, kUniversum_[i])) {
            array_[res_len] = kUniversum_[i];
            res_len++;
        } 
    }
}

Set::Set() {

}

Set::Set(const Set &set) {
    for (auto i = 0; i < kUniversumPower_; ++i) {
        array_[i] = set.array_[i];
    }
}

Set Set::operator|(const Set &set) const {
    Set R;
    auto res_len = 0;

    for (auto i = 0; i < kUniversumPower_ && array_[i]; i++) {
        R.array_[res_len] = array_[i];
        res_len++;
    }

    for (auto i = 0; i < kUniversumPower_ && set.array_[i]; i++) {
        if (!Contains(set.array_[i])) {
            R.array_[res_len] = set.array_[i];
            res_len++;
        }
    }

    return R;
}

Set Set::operator&(const Set &set) const {
    Set R;
    auto res_len = 0;
    
    for (auto i = 0; i < kUniversumPower_; ++i) {
        if (Contains(kUniversum_[i]) && set.Contains(kUniversum_[i])) {
            R.array_[res_len] = kUniversum_[i];
            res_len++;
        }
    }

    return R;
}

Set Set::operator~() const {
    Set R;
    auto res_len = 0;

    for (auto i = 0; i < kUniversumPower_; ++i) {
        if (!Contains(kUniversum_[i])) {
            R.array_[res_len] = kUniversum_[i];
            res_len++;
        }
    }

    return R;
}

Set Set::operator=(const Set &set) {
    for (auto i = 0; i < kUniversumPower_; ++i) {
        array_[i] = set.array_[i];
    }

    return *this;
}

std::string Set::ToString() const {
    if (array_[0]) {
        return std::string{array_};
    }
    else {
        return "";
    }
}

bool Set::Contains(char a) const {
    for (auto i = 0; i < kUniversumPower_; i++) {
        if (array_[i] == a) {
            return true;
        }
    }
    return false;    
}

bool StringContains(const std::string &str, char a) {
    for (auto i = 0; i < str.length(); i++) {
        if (str[i] == a) {
            return true;
        }
    }
    return false;
}

#endif
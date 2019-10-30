#if SET_IMPL == 0

#include "word.h"

#include <iostream>

Set::Set(const std::string &str) {
    word_ = StringToWord(str);
}

Set::Set(const Set &set) {
    word_ = set.word_;
}

Set Set::operator|(const Set &set) const {
    Set R;
    R.word_ = word_ | set.word_;
    return R;
}

Set Set::operator&(const Set &set) const {
    Set R;
    R.word_ = word_ & set.word_;
    return R;
}

Set Set::operator~() const {
    Set R;
    R.word_ = ~word_;
    return R;
}

Set Set::operator=(const Set &set) {
    if (this != &set) {
        word_ = set.word_;
    }
    return *this;
}

std::string Set::ToString() const {
    std::string str;
    Word current_bit = 1;
    for (auto i = 0; i < kUniversumPower_; ++i) {
        if (word_ & current_bit) {
            str += kUniversum_[i];
        }
        current_bit <<= 1;
    }
    if (str.length() == 0) {
        str = "-";
    }
    return str;
}

Word Set::StringToWord(const std::string &str) const {
    Word word = 0;
    for (auto c : str) {
        Word current_bit = 1;
        for (auto i = 0; i < kUniversumPower_; ++i) {
            if (c == kUniversum_[i]) {
                word |= current_bit;
            }
            current_bit <<= 1;
        }
    }

    return word;
}

#endif
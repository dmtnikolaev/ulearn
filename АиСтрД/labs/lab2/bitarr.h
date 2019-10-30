#ifndef BITARR_H
#define BITARR_H

#include <string>

using Word = unsigned short;

class Set {
public:
    explicit Set(const std::string &);
    Set();
    Set(const Set &);
    Set(const int *);
    Set operator|(const Set &) const;
    Set operator&(const Set &) const;
    Set operator~() const;
    Set operator=(const Set &);
    std::string ToString() const;
private:
    static const int kUniversumPower_ = 16;
    inline static std::string kUniversum_ = "0123456789ABCDEF";
    unsigned int bitArray_[kUniversumPower_] = {0};  
};

#endif
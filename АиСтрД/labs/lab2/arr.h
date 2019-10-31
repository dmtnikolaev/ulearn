#ifndef ARR_H
#define ARR_H

#include <string>

class Set {
public:
    explicit Set(const std::string &);
    Set();
    Set(const Set &);
    Set operator|(const Set &) const;
    Set operator&(const Set &) const;
    Set operator~() const;
    Set operator=(const Set &);
    std::string ToString() const;
private:
    static const int kUniversumPower_ = 16;
    inline static std::string kUniversum_ = "0123456789ABCDEF";
    char array_[kUniversumPower_] = {0};

    bool Contains(char a) const;
};

bool StringContains(const std::string &, char);

#endif
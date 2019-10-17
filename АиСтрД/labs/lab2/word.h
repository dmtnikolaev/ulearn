#ifndef WORD_H
#define WORD_H

#include <string>

using Word = unsigned short;

class Set {
public:
    explicit Set(const std::string &);
    Set() : word_(0) {};
    Set(const Set &);
    Set operator|(const Set &) const;
    Set operator&(const Set &) const;
    Set operator~() const;
    Set operator=(const Set &);
    std::string ToString() const;
private:
    static const int kUniversumPower_ = 16;
    inline static std::string kUniversum_ = "0123456789ABCDEF";
    Word word_;

    Word StringToWord(const std::string &) const;  
};

#endif
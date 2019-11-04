#ifndef LIST_H
#define LIST_H

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
    ~Set();
private:
    static const int kUniversumPower_ = 16;
    inline static std::string kUniversum_ = "0123456789ABCDEF";

    struct Item {
        char val;
        Item* next;
    };

    Item* head_ = nullptr;

    Item* New(char, Item*) const;
    Item* New(char) const;
    void Delete(Item*);
    Item* Add(Item*, char) const;
    bool Contains(const Item*, char) const;
    std::string ItemToString(const Item*) const;
};

bool StringContains(const std::string &, char);

#endif
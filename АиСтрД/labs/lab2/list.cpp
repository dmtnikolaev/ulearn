#if SET_IMPL == 3

#include "list.h"

Set::Set(const std::string &str) {
    for (auto c : kUniversum_) {
        if (StringContains(str, c)) {
            head_ = Add(head_, c);
        }
    }
}

Set::Set() {

}

Set::Set(const Set &set) {
    auto tmp = set.head_;

    while (tmp != nullptr) {
        head_ = Add(head_, tmp->val);
        tmp = tmp->next;
    }
}

Set Set::operator|(const Set &set) const {
    Set R;

    auto tmp = head_;
    while (tmp != nullptr) {
        R.head_ = Add(R.head_, tmp->val);
        tmp = tmp->next;
    }

    tmp = set.head_;
    while (tmp != nullptr) {
        if (!Contains(R.head_, tmp->val)) {
            R.head_ = Add(R.head_, tmp->val);
        }
        tmp = tmp->next;
    }

    return R;
}

Set Set::operator&(const Set &set) const {
    Set R;

    auto tmp = head_;
    while (tmp != nullptr) {
        if (Contains(set.head_, tmp->val)) {
            R.head_ = Add(R.head_, tmp->val);
        }
        tmp = tmp->next;
    }

    return R;
}

Set Set::operator~() const {
    Set R;

    for (auto c : kUniversum_) {
        if (!Contains(head_, c)) {
            R.head_ = Add(R.head_, c);
        }
    }

    return R;
}
    
Set Set::operator=(const Set &set) {
    Set::Delete(head_);
    head_ = nullptr;
    
    auto tmp = set.head_;
    while (tmp != nullptr) {
        head_ = Add(head_, tmp->val);
        tmp = tmp->next;
    }

    return *this;
}

std::string Set::ToString() const {
    return ItemToString(head_);
}

Set::~Set() {
    Delete(head_);
    head_ = nullptr;
}

Set::Item* Set::New(char v, Set::Item* next) const {
    return new Set::Item { v, next };
}

Set::Item* Set::New(char v) const {
    return New(v, nullptr);
}

void Set::Delete(Set::Item* a) {
    while (a != nullptr) {
        auto tmp = a->next;
        delete a;
        a = tmp;
    }
}

Set::Item* Set::Add(Set::Item* a, char v) const {
    if (a == nullptr) {
        return New(v);
    }

    auto a_el = a;
    while (a_el->next != nullptr) {
        a_el = a_el->next;
    }
    a_el->next = New(v);

    return a;
}

bool Set::Contains(const Set::Item* a, char v) const {
    while (a != nullptr) {
        if (a->val == v) {
            return true;
        }
        a = a->next;
    }
    return false;
}

std::string Set::ItemToString(const Set::Item* a) const {
    std::string str;
    auto a_el = a;
    while (a_el != nullptr) {
        str += a_el->val;
        a_el = a_el->next;
    }
    return str;
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
#ifndef LAB3_NODE_H_
#define LAB3_NODE_H_

class Node {
public:
    Node() : tag_('\0'), left_(nullptr), middle_(nullptr), right_(nullptr) {}
    
    ~Node() { 
            delete left_; 
            delete middle_; 
            delete right_;
        }

    inline char tag() { return tag_; }
    inline Node* left() { return left_; }
    inline Node* middle() { return middle_; }
    inline Node* right() { return right_; }

    inline void set_tag(char tag) { tag_ = tag; }
    inline void set_left(Node* left) { left_ = left; }
    inline void set_middle(Node* middle) { middle_ = middle; }
    inline void set_right(Node* right) { right_ = right; }

private:
    char tag_;
    Node* left_;
    Node* middle_;
    Node* right_;
};

#endif  // LAB3_NODE_H_

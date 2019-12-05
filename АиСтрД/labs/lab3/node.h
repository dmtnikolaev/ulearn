#ifndef LAB3_NODE_H_
#define LAB3_NODE_H_

class Node {
public:
    Node() : tag_('\0'), left_(nullptr), middle_(nullptr), right_(nullptr) {}
    Node(char tag, Node* left, Node* middle, Node* right) : 
        tag_(tag), left_(left), middle_(middle), right_(right) {} 

    ~Node() { 
        delete left_; 
        delete middle_; 
        delete right_;
    }

    char tag() const {
        return tag_;
    }
    Node* left() const {
        return left_;
    }
    Node* middle() const {
        return middle_;
    }
    Node* right() const {
        return right_;
    }

private:
    char tag_;
    Node* left_;
    Node* middle_;
    Node* right_;
};

#endif  // LAB3_NODE_H_

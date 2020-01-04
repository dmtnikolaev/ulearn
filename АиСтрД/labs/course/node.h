#ifndef COURSE_NODE_H_
#define COURSE_NODE_H_

#include <string>

class Node {
public:
    Node(int id) : id_(id), visited_(false) {}

    int id() const {
        return id_;
    }

    bool visited() const {
        return visited_;
    }

    void set_visited(bool flag) {
        visited_ = flag;
    }

    friend std::ostream& operator<<(std::ostream& os, Node& n) {
        os << std::to_string(n.id_ + 1);
        return os;
    }

    static Node kEmpty;
    static Node* kEmptyPtr;

private:
    int id_;
    bool visited_;
};

#endif  // COURSE_NODE_H_

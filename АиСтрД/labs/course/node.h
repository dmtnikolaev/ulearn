#ifndef COURSE_NODE_H_
#define COURSE_NODE_H_

class Node {
public:
    Node(int id) : id_(id), visited_(false) {}

    int id() {
        return id_;
    }
    bool visited() {
        return visited_;
    }
    void set_visited(bool flag) {
        visited_ = flag;
    }

private:
    int id_;
    bool visited_;
};

#endif  // COURSE_NODE_H_

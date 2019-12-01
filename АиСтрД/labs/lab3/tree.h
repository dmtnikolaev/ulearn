#ifndef LAB3_TREE_H_
#define LAB3_TREE_H_

#include <cstdlib>
#include "node.h"

class Tree {
public:
    Tree(char first_tag, char max_tag, int max_depth) : current_tag_(first_tag),
        max_tag_(max_tag), max_depth_(max_depth) {}

    ~Tree();

    inline void MakeTree() { root_ = MakeNode(kroot_depth_); }
    void OutTree();

private:
    const int kroot_depth_ = 0;

    Tree(const Tree &tree);
    Tree operator=(const Tree &tree) const;

    inline bool DoNodeMaking(int depth) {
        return (depth < std::rand()%(max_depth_+1) + 1) && 
            (current_tag_ <= max_tag_);
    }
    Node* MakeNode(int depth);

    char current_tag_;
    char max_tag_;
    int max_depth_;
    int offset_;
    Node* root_ = nullptr;
};

#endif  // LAB3_TREE_H_

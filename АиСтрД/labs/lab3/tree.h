#ifndef LAB3_TREE_H_
#define LAB3_TREE_H_

#include <cstdlib>
#include "node.h"
#include "screen.h"

class Tree {
public:
    Tree(char first_tag, char max_tag, int max_depth) :
        current_tag_(first_tag), max_tag_(max_tag), max_depth_(max_depth) {}

    ~Tree() {
        delete root_;
    }

    void MakeTree() {
        root_ = MakeNode(kRootDepth);
    }
    void OutTree(Screen &screen);
    int BFS();

private:
    const int kRootDepth = 0;
    const int kOffset = Screen().kWidth / 2 - 2;

    Tree(const Tree &tree);
    Tree operator=(const Tree &tree) const;

    bool DoNodeMaking(int depth) {
        return depth < std::rand()%max_depth_ + 1 && current_tag_ <= max_tag_;
    }
    Node* MakeNode(int depth);
    void OutNodes(Node* root, Screen &screen, int depth, int offset);

    char current_tag_;
    char max_tag_;
    int max_depth_;
    int offset_;
    Node* root_ = nullptr;
};

#endif  // LAB3_TREE_H_

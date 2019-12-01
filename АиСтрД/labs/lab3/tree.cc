#include "tree.h"

Node* Tree::MakeNode(int depth) {
    Node* node = nullptr;

    if (DoNodeMaking(depth)) {
        auto node = new Node;

        node->set_tag(current_tag_++);
        node->set_left(MakeNode(depth + 1));
        node->set_middle(MakeNode(depth + 1));
        node->set_right(MakeNode(depth + 1));
    }

    return node;
}

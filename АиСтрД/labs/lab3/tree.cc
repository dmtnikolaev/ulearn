#include "tree.h"

void Tree::OutTree(Screen &screen) {
    screen.Clear();
    if (root_) {
        OutNodes(root_, screen, 0, screen.kmax_width_ / 2 - 2);
    }
}

Node* Tree::MakeNode(int depth) {
    Node* node = nullptr;

    if (DoNodeMaking(depth)) {
        node = new Node();

        node->set_tag(current_tag_++);
        node->set_left(MakeNode(depth + 1));
        node->set_middle(MakeNode(depth + 1));
        node->set_right(MakeNode(depth + 1));
    }

    return node;
}

void Tree::OutNodes(Node* root, Screen &screen, int depth, int offset) {
    screen.set_symbol(depth, offset, root->tag());

    if (root->left()) {
        OutNodes(root->left(), screen, depth + 1, 
            offset - (koffset_ >> depth + 1));
    }

    if (root->middle()) {
        OutNodes(root->middle(), screen, depth + 1, offset);
    }

    if (root->right()) {
        OutNodes(root->right(), screen, depth + 1, 
            offset + (koffset_ >> depth + 1));
    }
}

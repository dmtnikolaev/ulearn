#include "tree.h"

#include <queue>
#include "node.h"

void Tree::OutTree(Screen &screen) {
    screen.Clear();
    if (root_) {
        OutNodes(root_, screen, 0, kOffset);
    }
}

Node* Tree::MakeNode(int depth) {
    Node* node = nullptr;

    if (DoNodeMaking(depth)) {
        node = new Node(current_tag_++, MakeNode(depth + 1), 
                        MakeNode(depth + 1), MakeNode(depth + 1));
        
        if (depth > depth_) {
            depth_ = depth;
        }
    }

    return node;
}

void Tree::OutNodes(Node* root, Screen &screen, int depth, int offset) {
    screen.SetSymbol(depth, offset, root->tag());

    if (root->left()) {
        OutNodes(root->left(), screen, depth + 1, 
            offset - (kOffset >> depth + 1));
    }

    if (root->middle()) {
        OutNodes(root->middle(), screen, depth + 1, offset);
    }

    if (root->right()) {
        OutNodes(root->right(), screen, depth + 1, 
            offset + (kOffset >> depth + 1));
    }
}

int Tree::BFS() {
    const int kMaxQueue = 20;
    int count = 0;
    std::queue<Node*> queue;
    queue.push(root_);
    while (!queue.empty()) {
        Node* node = queue.front();
        queue.pop();
        std::cout << node->tag() << '_';
        count++;
        if (node->left()) {
            queue.push(node->left());
        }
        if (node->middle()) {
            queue.push(node->middle());
        }
        if (node->right()) {
            queue.push(node->right());
        }
    }

    return count;
}
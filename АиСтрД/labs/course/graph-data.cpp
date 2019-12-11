#include "graph-data.h"

#include <stdexcept>
#include <vector>

#include "node.h"

AdjList::AdjList() {

}

void AdjList::AddNode(Node u) {
    if (u.id() < count()) {
        return;
    }
    auto node_pos = nodes_.begin() + u.id()*sizeof(Node*);
    nodes_.insert(node_pos, new Node(u.id()));
    auto nei = std::vector<int>();
    adj_list_.insert({ u.id(), nei });
}

void AdjList::AddEdge(int id1, int id2) {
    if (id1 >= nodes_.size() ||
        id2 >= nodes_.size()) {
        throw std::out_of_range("id1/id2");
    }

    adj_list_[id1].push_back(id2);
}

void AdjList::AddEdge(Node u, Node v) {
    AddNode(u);
    AddNode(v);
    AddEdge(v.id(), v.id());
}

Node* AdjList::GetNode(int id) const {
    return nodes_.at(id);
}

std::vector<Node*> AdjList::GetNeigbors(int id) {
    auto nei_ids = adj_list_[id];
    auto nei = std::vector<Node*>();
    for (auto nei_id : nei_ids) {
        nei.push_back(nodes_[nei_id]);
    }
    return nei;
}

AdjList::~AdjList() {
    for (auto u : nodes_) {
        delete u;
    }
}


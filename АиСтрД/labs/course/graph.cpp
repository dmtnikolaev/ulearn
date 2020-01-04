#include "graph.h"

#include <vector>
#include <stack>

std::vector<Cycle> Graph::BuildCycles() {
    std::vector<Cycle> cycles;

    std::vector<Node*> nodes = data_.GetNodes();
    int id = 0;
    while (true) {
        if (id == nodes.size()) {
            return cycles;
        }

        auto new_cycles = Dfs(nodes[id], nodes[id]);
        for (auto c : new_cycles) {
            c.Add(nodes[id]);
            cycles.push_back(c);
        }
        for (auto x : nodes) {
                x->set_visited(false);
        }
        id++;
    }
}

std::vector<Cycle> Graph::Dfs(Node* start, Node* n) {
    n->set_visited(true);

    std::vector<Cycle> pathes;
    for (auto x : data_.GetNeighbors(n->id())) {
        if (!x->visited() && x != start) {
            auto cycs = Dfs(start, x);
            for (auto cyc : cycs) {
               cyc.Add(x);
               pathes.push_back(cyc);
            }
        } 
        if (x == start) {
            Cycle c;
            c.Add(x);
            pathes.push_back(c);
        }
    }
    return pathes;
}

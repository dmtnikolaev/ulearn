#include "graph.h"

#include <vector>
#include <stack>

std::vector<Cycle> Graph::BuildCycles() {
    std::vector<Cycle> cycles;

    for (auto root : data_.GetNodes()) {
        if (root && !root->visited()) {
            auto path = Dfs(root);

            for (auto i = 0; i < path.size(); i++) {
                for (auto j = i + 2; j < path.size(); j++) {
                    if (path[i] == path[j]) {
                        Cycle c;
                        for (auto k = i; k <= j; k++) {
                            c.Add(path[k]);
                        }
                        cycles.push_back(c);
                    }
                }
            }
        }
    }

    return cycles;
}

std::vector<Node*> Graph::Dfs(Node* n) {
    std::vector<Node*> path;
    std::stack<Node*> stack;

    path.push_back(n);
    stack.push(n);

    while (!stack.empty()) {
        auto t = stack.top();
        stack.pop();

        if (!t->visited()) {
            t->set_visited(true);
            auto neighbors = data_.GetNeighbors(t->id());

            for (auto n : neighbors) {
                path.push_back(n);
                stack.push(n);
            } 
        }
    }

    return path;
}

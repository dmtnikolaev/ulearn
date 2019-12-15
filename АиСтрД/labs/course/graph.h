#ifndef COURSE_GRAPH_H_
#define COURSE_GRAPH_H_

#include <iostream>
#include <vector>

#include "graph-data.h"
#include "graph-source.h"
#include "node.h"

struct Cycle {
public:
    Cycle();
    void Add(Node* u);

    std::vector<Node*> nodes() const {
        return nodes_;
    }

private:
    std::vector<Node*> nodes_;
};

template<class Repr = AdjList>
class Graph {
public:
    Graph(const GraphSource* src) {
        std::vector<Edge> edges = src->Load();

        for (auto e : edges) {
            data_.AddEdge(e.src, e.dest);
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Graph<Repr>& gr) {
        for (auto u : gr.data_.GetNodes()) {
            os  << *u << " -> ";

            auto neis = gr.data_.GetNeighbors(u->id());
            os << "[ ";
            for (auto i = 0; i < neis.size(); i++) {
                if (i != 0) {
                    os << ", ";
                }
                os << *(neis[i]);
            }
            if (neis.size() == 0) {
                os << " ";
            }
            os << " ]" << std::endl;
        }
        return os;
    }
    std::vector<Cycle> BuildCycles();

private:
    Repr data_;

    std::vector<Node*> Dfs();
};

#endif  // COURSE_GRAPH_H_

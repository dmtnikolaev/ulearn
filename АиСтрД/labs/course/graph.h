#ifndef COURSE_GRAPH_H_
#define COURSE_GRAPH_H_

#include <iostream>
#include <vector>

#include "graph-data.h"
#include "graph-source.h"
#include "node.h"

class Graph {
public:
    Graph(GraphSource* src);

    friend std::ostream& operator<<(std::ostream& os, const Graph& graph);

    std::vector<Cycle> BuildCycles();

private:
    GraphData data_;

    std::vector<Node> DFS();
};

class Cycle {

};

#endif  // COURSE_GRAPH_H_

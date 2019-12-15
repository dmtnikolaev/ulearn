#ifndef COURSE_GRAPH_DATA_H_
#define COURSE_GRAPH_DATA_H_

#include <map>
#include <vector>

#include "node.h"

class GraphData {
public:
    virtual void AddNode(Node u) = 0;
    virtual void AddEdge(int id1, int id2) = 0;
    virtual void AddEdge(Node u, Node v) = 0;

    virtual std::vector<Node*> GetNodes() const = 0;
    virtual Node* GetNode(int id) const = 0;
    virtual std::vector<Node*> GetNeighbors(int id) const = 0;

    virtual int count() const = 0;

    virtual ~GraphData() {

    }
};

class AdjList : public GraphData {
public:
    AdjList();

    void AddNode(Node u) override;
    void AddEdge(int id1, int id2) override;
    void AddEdge(Node u, Node v) override;

    virtual std::vector<Node*> GetNodes() const override;
    Node* GetNode(int id) const override;
    std::vector<Node*> GetNeighbors(int id) const override;

    int count() const override {
        return nodes_.size();
    }

    ~AdjList();

private:
    std::vector<Node*> nodes_;
    std::map<int, std::vector<int>> adj_list_;
};

#endif  // COURSE_GRAPH_DATA_H_

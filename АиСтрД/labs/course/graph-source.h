#ifndef COURSE_GRAPH_SOURCE_H_
#define COURSE_GRAPH_SOURCE_H_

#include <stdexcept>
#include <vector>

#include "node.h"

struct Edge {
    Node src;
    Node dest;

    Edge(Node src, Node dest) : src(src), dest(dest) {

    }
};

class GraphSource {
public:
    virtual std::vector<Edge> Load() const = 0;

    virtual ~GraphSource() {

    }
};

class TextFileSource : public GraphSource {
public:
    TextFileSource(const char* filepath) : filepath_(filepath) {

    }

    std::vector<Edge> Load() const override;

    ~TextFileSource() override;

private:
    Edge ParseFileLine(std::string s) const;

    const char* filepath_;
};

#endif  // COURSE_GRAPH_SOURCE_H_

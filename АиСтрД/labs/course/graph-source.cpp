#include "graph-source.h"

#include <fstream>
#include <stdexcept>
#include <string>

std::vector<Edge> TextFileSource::Load() const {
    std::ifstream file(filepath_);
    if (!file.is_open()) {
        throw new std::runtime_error("can't open file");
    }

    std::vector<Edge> res;
    std::string line;
    while (getline(file, line)) {
        auto e = ParseFileLine(line);
        res.push_back(e);
    }
    file.close();

    return res;
}

// TODO: Add error checking.
//
Edge TextFileSource::ParseFileLine(std::string s) const {
    std::string n1_name;
    std::string n2_name;
    bool is_n1_name_parsing = true;

    int i = 0;
    while (i < s.size()) {
        if (i < s.size()-1 &&
            s[i] == '-' && s[i+1] == '>') {

            is_n1_name_parsing = false;
            i += 2;
            continue;
        }

        if (is_n1_name_parsing) {
            n1_name += s[i];
        }
        else {
            n2_name += s[i];
        }

        i++;
    }

    auto n1 = Node(std::stoi(n1_name)-1);
    auto n2 = Node(std::stoi(n2_name)-1);
    return Edge(n1, n2);
}

TextFileSource::~TextFileSource() {

}

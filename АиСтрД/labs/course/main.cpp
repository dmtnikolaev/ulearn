#include <iostream>

#include <memory>

#include "graph.h"
#include "graph-source.h"

int main() {
    try {
        auto src = std::make_unique<TextFileSource>("input.txt");
        auto gr = Graph<AdjList>(src.get());
        std::cout << gr;
    }
    catch(std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    //getchar();
    return 0;
}

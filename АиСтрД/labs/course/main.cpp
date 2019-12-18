#include <iostream>

#include <memory>

#include "graph.h"
#include "graph-source.h"

void PrintCycles(Graph& gr) {
    std::cout << "Cycles: " << std::endl;
    
    for (auto c : gr.BuildCycles()) {
        std::cout << c;
    }
}

int main() {
    try {
        auto src = std::make_unique<TextFileSource>("input.txt");
        auto gr = Graph(src.get());
        std::cout << gr;
        PrintCycles(gr);
    }
    catch(std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    //getchar();
    return 0;
}

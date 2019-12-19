#include <iostream>

#include <memory>

#include "graph.h"
#include "graph-source.h"

void PrintCycles(Graph& gr) {
    auto cycles = gr.BuildCycles();
    if (cycles.size() == 0) {
        std::cout << "Graph doesn't have cycles"
                  << std::endl;
        return;
    }

    std::cout << "Cycles: " << std::endl;
    for (auto c : cycles) {
        std::cout << c;
    }
}

int main(int argc, char* argv[]) {
    try {
        auto src = std::make_unique<TextFileSource>(argv[1]);
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

#include "tree.h"

#include <ctime>

int main() {
    srand(time(NULL));
    auto tree = Tree('a', 'z', 4);
    auto screen = Screen();

    tree.MakeTree();
    tree.OutTree(screen);

    screen.Print();

    std::cout << std::endl << "Обход в ширину: ";
    auto nodes_visited_count = tree.BFS();
    std::cout << " Пройдено узлов = " << nodes_visited_count << std::endl;
    std::cout << "Высота дерева = " << tree.depth() + 1 << std::endl;

    return 0;
}

#include "tree.h"

#include <ctime>

int main() {
    srand(time(NULL));
    auto tree = Tree('a', 'z', 4);
    auto screen = Screen();

    tree.MakeTree();
    tree.OutTree(screen);

    screen.Print();

    return 0;
}

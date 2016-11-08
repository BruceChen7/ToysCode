#include "base/graph.h"

int main() {
    MGraph g;
    createMGraph(&g);
    dfsTraverse(&g);
}
#include "Graph.h"

void findBaseCycles(Graph*g){
}

int main(int argc, char const *argv [])
{
    Graph* G=new Graph(6);
    G->addEdge(0,1,1);
    G->addEdge(1,2,1);
    G->addEdge(0,2,1);
    G->addEdge(1,3,1);
    G->addEdge(3,4,1);
    G->addEdge(4,5,1);
    G->addEdge(3,5,1);

    std::cout<<*G;
    delete G;
    return 0;
}

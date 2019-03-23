#include <iostream>
#include "Graph.h"




int main(int argc, char const *argv[])
{
    Graph* G=new Graph(5);
    std::cout<<G;
    delete G;
    return 0;
}

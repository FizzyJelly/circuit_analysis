#include "Graph.h"
#include <stack>




std::list<std::list<size_t>>& findBaseCycles(Graph&g){
    std::list<std::list<size_t>>* baseCycles=new std::list<std::list<size_t>>; //container for results
    std::stack<size_t> queue;
    size_t parents[g.n_vertices];

    queue.push(0); //starting with first node
    Graph copy=g;

    for(size_t i=0;i<g.n_vertices;i++){
        parents[i]=i;
    }

    size_t current;

    while(!queue.empty()){
        current=queue.top();
        queue.pop();

        for(size_t i=0;i<g.n_vertices;i++){

            if(g.matrix[current][i]>0){ //for each edge coming out of that node

                if(parents[i]!=i){ //node has been visited already => found cycle


                    

                } else { //not visited => add to queue
                    parents[i]=current;
                    queue.push(i);
                }

                g.removeEdge(current,i); //already processed that edge
            }
        }
    }



    return *baseCycles;
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

    std::list<std::list<size_t>>* cycles= &findBaseCycles(*G);
    std::cout<<*G;
    delete G;
    delete cycles;
    return 0;
}

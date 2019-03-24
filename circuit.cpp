#include "Graph.h"

void dfs(size_t u,size_t p,size_t colours[],size_t marked[], size_t parents[],size_t &cycle_num, Graph* g){
    if(colours[u] == 2){
        return; //already fully porcessed
    }

    if(colours[u] == 1){ //vertex was seen before, but not processed completely
        ++cycle_num;
        size_t tmp=p;
        marked[tmp]=cycle_num;


        while(tmp != u){
            tmp=parents[tmp];
            marked[tmp]=cycle_num;
        }

        return; //added whole cycle -> go back to the parent
    }

    parents[u] = p; //marking parent of currently visited vertex

    colours[u]=1; //marking visited current vertex

    vertex* current=g->vertices[u];
    std::list<edge>::iterator it;

    for(it=current->edges->begin();it!=current->edges->end();++it){
        if((*it).endNode!=p){ //other than the parent
            dfs((*it).endNode,u,colours,marked,parents,cycle_num,g);
        }    
    }

    colours[u]=2; //vertex cmopletely processed
}

void getCycles(size_t vertices, size_t marked[],size_t &cycle_num, std::list<size_t> cycles[]){
    for(size_t i=0;i<vertices;i++){
        if(marked[i] != 0){
            cycles[marked[i]].push_back(i);
        }
    }

    for(size_t i=1;i<=cycle_num;i++){
        std::cout<<"Cycle num: "<<i<<" ";
        for(auto it=cycles[i].begin();it!=cycles[i].end();it++){
            std::cout<<" "<<(*it);
        }
        std::cout<<std::endl;
    }
}

void findCycles(Graph*g){
    size_t vertices=6;
    size_t* colours=new size_t[vertices]();
    size_t* marked=new size_t[vertices]();
    size_t* parents=new size_t[vertices]();

    size_t cycles_num=0;

    dfs(0,0,colours,marked,parents,cycles_num,g);
    std::list<size_t> cycles[vertices];
    for(int i=0;i<vertices;i++){
        std::cout<<marked[i];
        std::cout<<" "<<colours[i]<<std::endl;
    }
    std::cout<<std::endl;
    getCycles(vertices,marked,cycles_num,cycles);
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

    findCycles(G);
    std::cout<<*G;
    delete G;
    return 0;
}

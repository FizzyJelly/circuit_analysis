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

        for(size_t i=0;i<copy.n_vertices;i++){

            if(copy.matrix[current][i]>0){ //for each edge coming out of that node

                if(parents[i]!=i){ //node has been visited already => found cycle
                    //marking each path in new matrix to xor them later
                    bool** paths=new bool*[copy.n_vertices];
                    for(size_t t=0;t<g.n_vertices;t++)
                        paths[t]=new bool[copy.n_vertices](); //should change it to upper half matrix later..

                    size_t temp=current;
                    while(temp!=0){
                        paths[parents[temp]][temp]=true;
                        //paths[temp][parents[temp]]=true;
                        temp=parents[temp];
                    }
                    temp=i;
                    while(temp!=0){
                        if(paths[parents[temp]][temp]==false){
                            paths[parents[temp]][temp]=true;
                            //paths[temp][parents[temp]]=true;
                        } else {
                            paths[parents[temp]][temp]=false;
                            //paths[temp][parents[temp]]=false;
                        }
                        temp=parents[temp];
                    }
                    
                    std::cout<<parents[current]<<parents[i]<<std::endl;
                    std::cout<<current<<i<<std::endl;

                    for(int a=0;a<g.n_vertices;a++){
                        for(int b=0;b<g.n_vertices;b++){
                            std::cout<<paths[a][b]<<" ";
                        }
                        std::cout<<std::endl;
                    }
                    std::cout<<std::endl;

                    std::list<size_t> cycle;
                    //trace back both paths to common ancestor
                    //for(int a=0;a<g.n_vertices;a++)
                    //    std::cout<<parents[a];
                    temp=current;
                    while(paths[parents[temp]][temp]){
                        cycle.push_back(temp);
                        temp=parents[temp];
                    }

                    temp=i;
                    while(paths[parents[temp]][temp]){
                        cycle.push_front(temp);
                        temp=parents[temp];
                    }

                    cycle.push_front(temp);


                    baseCycles->push_back(cycle);

                    for(size_t t=0;t<copy.n_vertices;t++)
                        delete paths[t];

                    delete paths;

                } else { //not visited => add to queue
                    parents[i]=current;
                    queue.push(i);
                }

                copy.removeEdge(current,i); //already processed that edge
            }
        }
    }



    return *baseCycles;
}

int main(int argc, char const *argv [])
{
    Graph* G=new Graph(17);
    /*G->addEdge(0,1,1);
    G->addEdge(0,5,1);
    G->addEdge(1,2,1);
    G->addEdge(1,4,1);
    G->addEdge(2,3,1);
    G->addEdge(3,4,1);
    G->addEdge(4,5,1);*/ //sqaure

    /*G->addEdge(0,1,1);
    G->addEdge(1,2,1);
    G->addEdge(2,7,1);
    G->addEdge(2,3,1);
    G->addEdge(3,4,1);
    G->addEdge(3,5,1);
    G->addEdge(4,5,1);
    G->addEdge(5,6,1);
    G->addEdge(6,7,1);
    G->addEdge(7,8,1);
    G->addEdge(0,8,1);*/ //more complex

    G->addEdge(0,1,1);
    G->addEdge(1,2,1);
    G->addEdge(2,7,1);
    G->addEdge(2,3,1);
    G->addEdge(3,4,1);
    G->addEdge(3,5,1);
    G->addEdge(4,5,1);
    G->addEdge(5,6,1);
    G->addEdge(6,7,1);
    G->addEdge(7,8,1);
    G->addEdge(0,8,1);
    G->addEdge(1,14,1);
    G->addEdge(13,14,1);
    G->addEdge(13,16,1);
    G->addEdge(13,11,1);
    G->addEdge(11,12,1);
    G->addEdge(11,10,1);
    G->addEdge(12,10,1);
    G->addEdge(9,10,1);
    G->addEdge(9,3,1);
    G->addEdge(10,16,1);
    G->addEdge(15,16,1);
    G->addEdge(15,2,1);


    std::list<std::list<size_t>>* cycles= &findBaseCycles(*G);
    for(std::list<std::list<size_t>>::iterator it=cycles->begin();it!=cycles->end();it++){
        std::cout<<"Cycle: ";
        for(std::list<size_t>::iterator it2=it->begin();it2!=it->end();it2++)
            std::cout<<*it2;
        std::cout<<std::endl;
    }
    delete G;
    delete cycles;
    return 0;
}

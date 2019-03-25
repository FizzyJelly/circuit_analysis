#include "Graph.h"
#include <stack>
#include <iomanip>
#include <armadillo>

using namespace arma;

struct edge{
    size_t u;
    size_t v;
    double resistance;
    double current;
};


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

            if(copy.matrix[current][i]!=0){ //for each edge coming out of that node

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

                    std::list<size_t> cycle;

                    //trace back both paths to common ancestor
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
                    cycle.push_back(temp);


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

edge* transferToEdgeArray(Graph *g){
    edge* edges = new edge[g->n_edges];
    size_t index=0;
    for(size_t u=0;u<g->n_vertices;u++){
        for(size_t v=u;v<g->n_vertices;v++){
            if(g->matrix[u][v]!=0){
                edges[index].u=u;
                edges[index].v=v;
                edges[index].resistance=g->matrix[u][v];
                edges[index].current=0;
                index++;
            }
        }
    }
    return edges;
}

size_t indexInEdgeArray(edge* edges,size_t u, size_t v, size_t size){
    for(size_t i=0;i<size;i++){
        if((edges[i].u==u && edges[i].v==v) || (edges[i].u==v&&edges[i].v==u)){
            return i;
        }
    }

    return -1;
}

edge* calculateCurrents(Graph* g,std::list<std::list<size_t>> baseCycles){
    edge* edges=transferToEdgeArray(g);

    mat A=mat(g->n_edges,g->n_edges,fill::zeros);
    vec y=vec(g->n_edges,fill::zeros);
    vec x=vec(g->n_edges);

    //first Kirchhoff law
    size_t u,v;

    for(size_t e=0;e<g->n_edges;e++){
        u=edges[e].u;
        v=edges[e].v;

        //initially assume all currents are directed towards end with bigger index
        A(u,e)=1;
        A(v,e)=-1;
    }
    //second Kirchhoff law
    A.row(g->n_edges-baseCycles.size()).zeros();
    size_t index=(g->n_edges)-baseCycles.size();
    for(auto it=baseCycles.begin();it!=baseCycles.end();it++){
        auto it2=it->begin();
        do{
            u=*it2;
            v=*(++it2);
            if(it2!=it->end()){
            if(g->matrix[u][v]>0){
                if(u<v){
                    A(index,indexInEdgeArray(edges,u,v,g->n_edges))=-g->matrix[u][v];
                } else{
                    A(index,indexInEdgeArray(edges,u,v,g->n_edges))=g->matrix[u][v];
                }
            } else {
                if(u<v){
                    y(index)=-g->matrix[u][v];
                } else {
                    y(index)=g->matrix[u][v];
                }
            }}
        }while(it2!=it->end());
        std::cout<<std::endl;
        index++;
    }


    x=solve(A,y);
    std::cout<<std::endl;
    x.print();

    A.print();

    for(size_t i=0;i<g->n_edges;i++){
        edges[i].current=x(i);
    }

    return edges;
}


int main(int argc, char const *argv [])
{
    Graph* G=new Graph(9);
    /*G->addEdge(0,1,1);
    G->addEdge(0,5,1);
    G->addEdge(1,2,1);
    G->addEdge(1,4,1);
    G->addEdge(2,3,1);
    G->addEdge(3,4,1);
    G->addEdge(5,4,-1);*/

    /*G->addEdge(0,1,1);
    G->addEdge(0,3,1);
    G->addEdge(0,7,-1);
    G->addEdge(1,2,1);
    G->addEdge(2,3,1);
    G->addEdge(2,4,1);
    G->addEdge(5,4,-1);
    G->addEdge(6,4,-1);
    G->addEdge(6,7,-1);
    G->addEdge(5,7,-1);*/

    G->addEdge(0,1,1);
    G->addEdge(1,2,1);
    G->addEdge(2,7,-1);
    G->addEdge(2,3,1);
    G->addEdge(3,4,1);
    G->addEdge(3,5,1);
    G->addEdge(4,5,1);
    G->addEdge(5,6,1);
    G->addEdge(6,7,1);
    G->addEdge(7,8,1);
    G->addEdge(0,8,1);

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
    G->addEdge(15,2,1);*/


    std::list<std::list<size_t>>* cycles= &findBaseCycles(*G);
    edge* circuit=calculateCurrents(G,*cycles);
    
    for(size_t i=0;i<G->n_edges;i++){
        std::cout<<circuit[i].u<<" "<<circuit[i].v<<" "<<circuit[i].current<<std::endl;
    }
        

    delete circuit;
    delete G;
    delete cycles;
    return 0;
}

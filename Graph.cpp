#include "Graph.h"
#include <fstream>

Graph::Graph(size_t n_vertices)
{ //just vertices with no edges
    this->n_vertices=n_vertices;
    matrix=new double*[n_vertices];
    for(size_t i=0;i<n_vertices;i++)
        matrix[i]=new double[n_vertices]();

}


Graph::Graph(size_t n_vertices, std::string file_name){
    std::ifstream in;
    in.open(file_name, std::ios::in);
    in.close();
}

Graph::Graph(const Graph&g) : Graph(g.n_vertices){
    for(size_t i=0;i<g.n_vertices;i++){
        for(size_t j=0;j<g.n_vertices;j++){
            matrix[i][j]=g.matrix[i][j];
        }
    }
}

Graph::~Graph()
{
    for (size_t i = 0; i < n_vertices; i++)
    {
        delete matrix[i];
    }

    delete matrix;
}

void Graph::addEdge(size_t u, size_t v, double w){
        matrix[u][v]=w;
        matrix[v][u]=w;
}

void Graph::removeEdge(size_t u, size_t v){
        matrix[u][v]=0;
        matrix[v][u]=0;
}

std::ostream &operator<<(std::ostream &out, const Graph &G)
{

    for (size_t i = 0; i < G.n_vertices; i++)
    {
        out << "Vertex " << i << " neighbours:";
        for(size_t j=0;j<G.n_vertices;j++){
            if(G.matrix[i][j]>0)
                out<<" "<<j;
        }
        out<<std::endl;
    }
    return out;
}

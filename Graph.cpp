#include "Graph.h"

Graph::Graph(size_t n)
{ //just vertices with no edges
    size = n;
    vertices = new vertex *[n];
    for (size_t i = 0; i < size; i++)
    {
        vertices[i] = new vertex;
        vertices[i]->edges = new std::list<edge>;
    }
}

//TODO Graph() constructor reading from instream list of edges;

Graph::~Graph()
{
    for (size_t i = 0; i < size; i++)
    {
        delete vertices[i]->edges;
    }

    delete vertices;
}

void Graph::addEdge(size_t u, size_t v, double w){
    if(vertices[u]->edges->empty()){
        vertices[u]->edges->push_back(edge(v,w));
    }
    if(vertices[v]->edges->empty()){
        vertices[v]->edges->push_back(edge(u,w));
    }
}


std::ostream &operator<<(std::ostream &out, const Graph &G)
{

    for (size_t i = 0; i < G.size; i++)
    {
        out << "Vertex " << i << " neighbours:";
        typename std::list<edge>::iterator it;
        for (it = G.vertices[i]->edges->begin(); it != G.vertices[i]->edges->end(); ++it)
        {
            out << " " << (*it).endNode;
        }
        out << '\n';
    }
    return out;
}

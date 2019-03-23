#include "Graph.h"

int size;
vertex **vertices;

Graph::Graph(int n)
{ //just vertices with no edges
    size = n;
    vertices = new vertex *[n];
    for (int i = 0; i < size; i++)
    {
        vertices[i] = new vertex;
        vertices[i]->edges = new std::list<edge>;
    }
}

//Graph() constructor reading from instream list of edges;

Graph::~Graph()
{
    for (int i = 0; i < size; i++)
    {
        delete vertices[i]->edges;
    }

    delete vertices;
}

std::ostream &operator<<(std::ostream &out, const Graph &G)
{

    for (int i = 0; i < G.size; i++)
    {
        out << "Vertex " << i << " neighbours:";
        std::list<edge>::iterator it;
        for (it = G.vertices[i]->edges->begin(); it != G.vertices[i]->edges->end(); ++it)
        {
            out << " " << (*it).endNode;
        }
        out << '\n';
    }
    return out;
}

std::ostream &operator<<(std::ostream &out, const Graph *G)
{

    for (int i = 0; i < G->size; i++)
    {
        out << "Vertex " << i << " neighbours:";
        std::list<edge>::iterator it;
        for (it = G->vertices[i]->edges->begin(); it != G->vertices[i]->edges->end(); ++it)
        {
            out << " " << (*it).endNode;
        }
        out << '\n';
    }
    return out;
}
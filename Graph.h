#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <list>

struct edge
{
    size_t endNode;
    double weight;

    edge(size_t end, double w) : endNode(end), weight(w){};
};

struct vertex
{
    int id;
    std::list<edge> *edges;
};

class Graph
{

  public: //leaving it public for now
    size_t size;
    vertex **vertices;

  public:
    Graph(size_t n); //just vertices with no edges
    Graph(size_t n,std::string  file_name);

    ~Graph();
    void addEdge(size_t u, size_t v, double w); //u,v -> vertices; w -> weight
    friend std::ostream &operator<<(std::ostream &out, const Graph &G);
};

#endif
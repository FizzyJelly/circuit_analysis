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

  protected: //leaving it protected for now
    size_t size;
    vertex **vertices;

  public:
    Graph(size_t n); //just vertices with no edges
    //TODO Graph() constructor reading from instream list of edges;

    ~Graph();
    void addEdge(size_t u, size_t v, double w); //u,v -> vertices; w -> weight
    friend std::ostream &operator<<(std::ostream &out, const Graph &G);
};

#endif
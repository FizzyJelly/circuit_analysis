#include <iostream>
#include <list>

struct edge{
    int endNode;
    double weight;
};

struct vertex{
    int id;
    std::list<edge>* edges;
};

class Graph{


    public:
    int size;
    vertex** vertices;

    Graph(int n); //just vertices with no edges
    //Graph() constructor reading from instream list of edges;
    
    ~Graph();

    friend std::ostream &operator<<(std::ostream &out, const Graph &G);
    friend std::ostream &operator<<(std::ostream &out, const Graph* G);
};
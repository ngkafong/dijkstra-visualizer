#ifndef ALGORITHM_H
#define ALGORITHM_H
#include "vertex.h"

class Dijkstra
{
public:

    Dijkstra(std::map<std::string, Vertex*> vertexPool,Impl* hostImpl);
    ~Dijkstra();
    void setcurrentVertex(std::string name);
    Vertex* getcurrentVertex(){return currentVertex;};
    Vertex* getcurrentOppositeEnd(){return currentOppositeEnd;}
    Edge* getcurrentEdge(){return currentEdge;};
    bool inUnivisitedVertex(std::string name);
    bool inPriorityQueue(std::string name);
    bool run();
    bool updated;
    bool getfinished(){return finished;};

private:

    Impl* hostImpl;
    std::map<std::string, Vertex*> unvisited_vertex;
    std::map<std::string, Vertex*> priorityQueue;

    Vertex* findNextVertex();
    Vertex* currentVertex = nullptr;
    Vertex* currentOppositeEnd = nullptr;

    Edge* currentEdge = nullptr;
    std::map<std::string, Edge*> currentVertexUnvisitedEdge;

    bool finished = false;

};

#endif // ALGORITHM_H

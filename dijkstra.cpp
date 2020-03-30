#include "dijkstra.h"
#include <QDebug>
#include <QMessageBox>



Dijkstra::Dijkstra(std::map<std::string, Vertex *> vertexPool, Impl *hostImpl)
    :hostImpl(hostImpl), unvisited_vertex(vertexPool)
{
}

Dijkstra::~Dijkstra()
{
   //
}

void Dijkstra::setcurrentVertex(std::string name)
{
    currentEdge = nullptr;
    currentOppositeEnd = nullptr;

    currentVertex = unvisited_vertex[name];

    unvisited_vertex.erase(name);

    if(priorityQueue.count(name)){
        priorityQueue.erase(name);
    }




    currentVertexUnvisitedEdge = currentVertex->getconnectedEdge();

    for (std::map<std::string, Edge*>::iterator j = currentVertexUnvisitedEdge.begin(); j!= currentVertexUnvisitedEdge.end(); j++){
        if(!unvisited_vertex.count(j->second->getOtherEnd(currentVertex)->getName())){
            currentVertexUnvisitedEdge.erase(j);
        }
    }

}

bool Dijkstra::inUnivisitedVertex(std::string name)
{
    return unvisited_vertex.count(name);
}

bool Dijkstra::inPriorityQueue(std::string name)
{
    return priorityQueue.count(name);
}

bool Dijkstra::run()
{
    // if no start vertex set
    if(currentVertex == nullptr) return false;

    // if algorithm finished
    if (priorityQueue.size() == 0 && currentVertexUnvisitedEdge.size() == 0){
        currentVertex = nullptr;
        finished = true;
        return true;
    }

    if(currentVertexUnvisitedEdge.size() == 0){
        setcurrentVertex(findNextVertex()->getName());
        return false;
    }

    currentEdge = currentVertexUnvisitedEdge.begin()->second;
    currentVertexUnvisitedEdge.erase(currentVertexUnvisitedEdge.begin());

    int tentativeDistance = currentVertex->getnearestDistance() + currentEdge->getweight();
    currentOppositeEnd = currentEdge->getOtherEnd(currentVertex);
    priorityQueue[currentOppositeEnd->getName()]= currentOppositeEnd;

    int currentDistance = currentOppositeEnd ->getnearestDistance();
    updated = false;
    if (tentativeDistance < currentDistance){
        currentOppositeEnd ->setnearestDistance(tentativeDistance);
        currentOppositeEnd ->setpreviousVertex(currentVertex);
        currentOppositeEnd ->setpreviousEdge(currentEdge);
        updated = true;
    }
    return false;
}

Vertex *Dijkstra::findNextVertex()
{
    Vertex* vertex = nullptr;
    int minDistance = INT_MAX;
    for (std::map<std::string, Vertex*>::iterator i = priorityQueue.begin(); i!=priorityQueue.end(); i++){
        int nearestDistance = i->second->getnearestDistance();
        if(nearestDistance <= minDistance){
            vertex = i->second;
            minDistance = nearestDistance;
        }
    }
    return vertex;
}

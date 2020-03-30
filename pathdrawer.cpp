#include "pathdrawer.h"
#include "vertex.h"
#include "QDebug"

Pathdrawer::Pathdrawer()
{

}

void Pathdrawer::findPathEdge(Vertex *vertex)
{
    pathEdge.clear();
    for(Vertex* v= vertex; v->getpreviousEdge() != nullptr; v = v->getpreviousVertex()){
        pathEdge[v->getpreviousEdge()->getName()] = v->getpreviousEdge();
    }

}

bool Pathdrawer::inpathEdge(std::string name)
{
    return pathEdge.count(name);

}

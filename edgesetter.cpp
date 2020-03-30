#include "edgesetter.h"


Edgesetter::Edgesetter(Impl *hostImpl)
    : hostImpl(hostImpl)
{

}

void Edgesetter::setEnabled(bool enabled)
{
    this->enabled = enabled;
}

void Edgesetter::setstartVertex(Vertex *vertex)
{
    startVertex = vertex;
}

void Edgesetter::setendVertex(Vertex *vertex)
{
    endVertex = vertex;
}

void Edgesetter::setEdge()
{
    hostImpl->addEdge(startVertex, endVertex);
    reset();
}

void Edgesetter::reset()
{
    startVertex = nullptr;
    endVertex = nullptr;
}


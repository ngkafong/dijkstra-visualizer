#ifndef EDGESETTER_H
#define EDGESETTER_H
#include "vertex.h"

class Edgesetter
{
public:
    Edgesetter(Impl* hostImpl);
    bool getEnabled() {return enabled;};
    void setEnabled(bool enabled);
    Vertex* getstartVertex() {return startVertex;}
    void setstartVertex(Vertex* vertex);
    void setendVertex(Vertex* vertex);
    void setEdge();
    void reset();

private:

    Impl* hostImpl;
    bool enabled = false;
    Vertex* startVertex = nullptr;
    Vertex* endVertex = nullptr;

};

#endif // EDGESETTER_H

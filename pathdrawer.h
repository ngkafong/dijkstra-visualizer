#ifndef PATHDRAWER_H
#define PATHDRAWER_H
#include "block.h"


class Pathdrawer
{
public:
    Pathdrawer();
    void findPathEdge(Vertex* vertex);
    bool inpathEdge(std::string);

private:
    std::map<std::string, Edge*> pathEdge;
};

#endif // PATHDRAWER_H

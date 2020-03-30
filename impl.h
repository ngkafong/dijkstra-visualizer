#ifndef IMPL_H
#define IMPL_H

#include <QLabel>
#include <Map>

class Vertexsetter;
class Edgesetter;
class Block;
class Vertex;
class Edge;
class Dijkstra;
class Pathdrawer;
class Impl
{
public:

    Impl(QLabel *backgroundLabel);
    void setVertex(bool checked);
    void addVertex(QPoint vertex);
    void setEdge(bool checked);
    void addEdge(Vertex* startVertex, Vertex* endVertex);
    void setDijkstra(bool checked);
    void deleteBlock(const std::string& name);
    void runDijkstra();
    void clearDijkstra();
    void setPathDrawer(bool checked);

    Edgesetter *edgesetter;
    Dijkstra *dijkstra = nullptr;
    Pathdrawer *pathdrawer;

private:

    std::map <std::string, Vertex*> vertexPool;
    std::map <std::string, Edge*> edgePool;
    QLabel *backgroundLabel;
    Vertexsetter *vertexsetter;


    std::string getAvailName(std::string prefix);

};
#endif // IMPL_H

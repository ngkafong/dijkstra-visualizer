#ifndef VERTEX_H
#define VERTEX_H

#include <QPoint>
#include "block.h"
#include "edge.h"
#include "edgesetter.h"
#include "dijkstra.h"
#include "pathdrawer.h"

#include <QEvent>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>

class Edge;
class Vertex : public Block
{
public:
    Vertex(QPoint vertex, std::string name, Impl *hostImpl, QWidget *parent = nullptr);
    ~Vertex();
    QPoint getVertex(){return vertex;};
    void addconnectedEdge(std::string name, Edge* edge);
    void removeconnectedEdge(std::string name);
    std::map<std::string, Edge*> getconnectedEdge() {return connectedEdge;};
    int getnearestDistance(){return nearestDistance;}
    void setnearestDistance(int d);
    void setpreviousVertex(Vertex* vertex);
    Vertex* getpreviousVertex() {return previousVertex;};
    void setpreviousEdge(Edge* edge);
    Edge* getpreviousEdge() {return previousEdge;};

protected:
    bool eventFilter(QObject *, QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    std::map<std::string, Edge*> connectedEdge;
    QPoint vertex;
    int nearestDistance = INT_MAX;
    Vertex* previousVertex = nullptr;
    Edge* previousEdge = nullptr;

};
#endif // VERTEX_H

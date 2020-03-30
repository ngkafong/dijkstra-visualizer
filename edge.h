#ifndef EDGE_H
#define EDGE_H
#include "block.h"
#include "vertex.h"

class Vertex;
class Edge : public Block
{
public:
    Edge(Vertex* startPoint, Vertex* endPoint, int weight, std::string name, Impl* hostImpl, QWidget* parent);
    ~Edge();
    Vertex* getOtherEnd(Vertex* vertex);
    int getweight(){return weight;};

protected:

    bool eventFilter(QObject *, QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;



private:
    Vertex* startVertex;
    Vertex* endVertex;
    int weight;

};

#endif // EDGE_H

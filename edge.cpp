#include "edge.h"
#include <QDebug>

Edge::Edge(Vertex* startVertex, Vertex* endVertex, int weight, std::string name, Impl* hostImpl, QWidget* parent)
    :Block(name, hostImpl, parent),
    startVertex(startVertex),
    endVertex(endVertex),
    weight(weight)
{
    lower();
}

Edge::~Edge()
{
    startVertex->removeconnectedEdge(name);
    startVertex->removeconnectedEdge(name);
}

bool Edge::eventFilter(QObject *, QEvent *event)
{
    Block::eventFilter(this,event);

    return false;
}



void Edge::paintEvent(QPaintEvent *event)
{
    QPoint lefttop;

    lefttop.setX(std::max(0, std::min(startVertex->getVertex().x(), endVertex->getVertex().x())-5));
    lefttop.setY(std::max(0, std::min(startVertex->getVertex().y(), endVertex->getVertex().y())-5));

    int width = abs(startVertex->getVertex().x() -endVertex->getVertex().x())+10 ;
    int height = abs(startVertex->getVertex().y() -endVertex->getVertex().y())+10;

    setGeometry(QRect(lefttop.x(), lefttop.y(), width, height));


    QLabel::paintEvent(event);
    QPixmap image(size());

    image.fill(Qt::transparent);

    QPainter painter(&image);

    QColor color = Qt::black;

    if (hostImpl->dijkstra != nullptr){
        if (hostImpl->dijkstra->getcurrentEdge() == this){
            color = Qt::blue;
        }
    }
    if (hostImpl->pathdrawer != nullptr){
        if (hostImpl->pathdrawer->inpathEdge(name)){
            color = Qt::blue;
        }
    }

    QPen pen(color);

    pen.setWidth(3);
    painter.setPen(pen);

    QPoint A = startVertex->getVertex() - lefttop;
    QPoint B = endVertex->getVertex() - lefttop;


    painter.drawLine(A,B);



    painter.setFont(QFont("Arial",8));
    painter.drawText((A+B)/2, QString::number(weight));

    setPixmap(image);
    setMask(image.mask());


}

Vertex *Edge::getOtherEnd(Vertex *vertex)
{
    if (startVertex == vertex){
        return endVertex;
    } else {
        return startVertex;
    }
}



#include "vertex.h"
#include <QDebug>
//#include <QBitmap>



Vertex::Vertex(QPoint vertex,std::string name, Impl *hostImpl, QWidget *parent)
    : Block(name,hostImpl, parent),
      vertex(vertex)
{
    int x = vertex.x()- 18;
    int y = vertex.y()- 18;

    setGeometry(QRect(x,y,36,36));
    update();
}

Vertex::~Vertex()
{
    for (std::map<std::string, Edge*>::iterator it= connectedEdge.begin(); it != connectedEdge.end() ; ++it){
        hostImpl->deleteBlock(it->second->getName());
    }

}

void Vertex::addconnectedEdge(std::string name, Edge *edge)
{
    connectedEdge[name] = edge;
}

void Vertex::removeconnectedEdge(std::string name)
{
    connectedEdge.erase(name);
}

void Vertex::setnearestDistance(int d)
{
    nearestDistance = d;
}

void Vertex::setpreviousVertex(Vertex *vertex)
{
    previousVertex = vertex;
}

void Vertex::setpreviousEdge(Edge *edge)
{
    previousEdge = edge;
}

bool Vertex::eventFilter(QObject *, QEvent *event)
{

    Block::eventFilter(this, event);

    static QPoint lastPoint;
    static bool isHover = false;


    if (event->type() == QEvent::MouseButtonPress) {

        QMouseEvent *e = static_cast<QMouseEvent*>(event);
        if (hostImpl->dijkstra != nullptr){
            if (rect().contains(e->pos())
                    && e->button() == Qt::LeftButton) {
                if (hostImpl->dijkstra->getcurrentVertex() == nullptr && !hostImpl->dijkstra->getfinished()){
                    hostImpl->dijkstra->setcurrentVertex(name);
                    nearestDistance = 0;
                }
            }
        }

        if (hostImpl->pathdrawer != nullptr){
            if (rect().contains(e->pos())
                    && e->button() == Qt::LeftButton) {
                hostImpl->pathdrawer->findPathEdge(this);
            }
        }

        if (hostImpl->edgesetter->getEnabled() == true){
            if (rect().contains(e->pos())
                    && e->button() == Qt::LeftButton) {
                if (hostImpl->edgesetter->getstartVertex() == nullptr){
                    hostImpl->edgesetter->setstartVertex(this);
                } else {
                    hostImpl->edgesetter->setendVertex(this);
                    hostImpl->edgesetter->setEdge();
                }
            }
            return false;
        }





        if (rect().contains(e->pos())
                && e->button() == Qt::LeftButton) {
            lastPoint = e->pos();
            isHover = true;
        }

    } else if (event->type() == QEvent::MouseMove && isHover) {

        QMouseEvent *e = static_cast<QMouseEvent*>(event);

        int dx = e->pos().x() - lastPoint.x();
        int dy = e->pos().y() - lastPoint.y();// DONE TODO: get the change of y coordinate "dy"
        int new_x = x() + dx;
        int new_y = y() + dy; // DONE TODO: get the new y coordinate "new_y"

        move(new_x, new_y);
        vertex = QPoint(new_x+18, new_y+18);

    } else if (event->type() == QEvent::MouseButtonRelease && isHover) {

        isHover = false;
    }
    return false;
}

void Vertex::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);
    QPixmap image(size());

    image.fill(Qt::transparent);

    QPainter painter(&image);

    QColor color;
    if (hostImpl->edgesetter->getstartVertex() == this){
        color = Qt::yellow;
    } else if (hostImpl->dijkstra != nullptr){
        if (!hostImpl->dijkstra->inUnivisitedVertex(name)){
            color = Qt::gray;
        }
        if (hostImpl->dijkstra->inPriorityQueue(name)){
            color = Qt::cyan;
        }
        if (hostImpl->dijkstra->getcurrentOppositeEnd() == this){
            if (hostImpl->dijkstra->updated == true){
                color = Qt::green;
            } else {
                color = Qt::red;
            }
        }
        if (hostImpl->dijkstra->getcurrentVertex() == this){
            color = Qt::blue;
        }
    } else {
        color = Qt::black;
    }
    QPen pen(color);

    pen.setWidth(3);
    painter.setPen(pen);
    painter.setBrush(Qt::white);
    painter.drawEllipse(QPoint(18,18),15, 15);

    if (nearestDistance != INT_MAX){
        painter.drawText(QPoint(15,23),QString::number(nearestDistance));
    }
    setPixmap(image);
    setMask(image.mask());
}

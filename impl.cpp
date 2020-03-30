#include "impl.h"
#include "vertexsetter.h"
#include "vertex.h"
#include "edge.h"
#include "edgesetter.h"
#include "dijkstra.h"
#include "pathdrawer.h"

#include <QMessageBox>
#include <QInputDialog>

Impl::Impl(QLabel *backgroundLabel)
    :backgroundLabel(backgroundLabel){

    backgroundLabel->setStyleSheet("QLabel { background-color : white;}");
    vertexsetter = new Vertexsetter(backgroundLabel, this, backgroundLabel->parentWidget());
    edgesetter = new Edgesetter(this);

}

void Impl::setVertex(bool checked){
    vertexsetter->setVisible(checked);
}

void Impl::addVertex(QPoint vertex)
{
    std::string name = getAvailName("Vertex");
    Vertex *v = new Vertex(vertex, name, this, backgroundLabel);
    vertexPool[name] = v;
}

void Impl::setEdge(bool checked)
{
    edgesetter->setEnabled(checked);
    edgesetter->reset();
}

void Impl::addEdge(Vertex *startVertex, Vertex *endVertex)
{
    bool ok = false;
    int weight = QInputDialog::getInt(backgroundLabel->parentWidget(), "", "Please input weight value.", 0,0, 214783647, 1, &ok);
    if (ok){
        std::string name = getAvailName("Edge");
        Edge *e = new Edge(startVertex, endVertex, weight, name, this, backgroundLabel);
        startVertex->addconnectedEdge(name, e);
        endVertex->addconnectedEdge(name,e);
        edgePool[name] = e;
    }
}

void Impl::setDijkstra(bool checked)
{
    if (checked == true){
        dijkstra = new Dijkstra(vertexPool, this);
    }
    else{
        clearDijkstra();
    }
}

void Impl::deleteBlock(const std::string& name)
{
    if (vertexPool.count(name)){
        vertexPool[name]->deleteLater();
        vertexPool.erase(name);
    }
    if (edgePool.count(name)){
        edgePool[name]->deleteLater();
        edgePool.erase(name);
    }
}

void Impl::runDijkstra()
{
    if (dijkstra == nullptr) return;

    bool ok = dijkstra->run();
    if (ok){
        QMessageBox::information(backgroundLabel->parentWidget(),"", "Algorithm Finished.");
    }
}

void Impl::clearDijkstra()
{
    if(dijkstra != nullptr){
        for (std::map<std::string, Vertex*>::iterator i = vertexPool.begin(); i!=vertexPool.end(); ++i){
            i->second->setnearestDistance(INT_MAX);
            i->second->setpreviousVertex(nullptr);
            i->second->setpreviousEdge(nullptr);
        }
        delete dijkstra;
        dijkstra = nullptr;
    }
}

void Impl::setPathDrawer(bool checked)
{
    if (checked == true){
        pathdrawer = new Pathdrawer();
    }
    else{
        delete pathdrawer;
        pathdrawer = nullptr;
    }
}

std::string
Impl::getAvailName(std::string prefix)
{
    int id = 0;
    std::string ret;

    if (prefix == "Vertex"){
        do {

            ret = prefix + std::to_string(id);
            id ++;

            } while (vertexPool.count(ret));
    } else {
        do {

            ret = prefix + std::to_string(id);
            id ++;

            } while (edgePool.count(ret));
    }

    return ret;
}

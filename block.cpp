#include "block.h"
#include "edgesetter.h"
#include <QMouseEvent>


Block::Block(std::string name, Impl *hostImpl, QWidget *parent):
    QLabel(parent),
    name(name),
    hostImpl(hostImpl)
{
    setStyleSheet("border : none");
    setStyleSheet("background-color : none");
    setAutoFillBackground(false);
    setVisible(true);
    installEventFilter(this);
}

bool Block::eventFilter(QObject *, QEvent *event)
{

    if (hostImpl->edgesetter->getEnabled() == true){
        return false;
    }

    if (hostImpl->dijkstra != nullptr){
        return false;
    }

    if (event->type() == QEvent::MouseButtonPress) {

        QMouseEvent *e = static_cast<QMouseEvent*>(event);

        if (rect().contains(e->pos())
                && e->button() == Qt::RightButton) {
           rightClickAction();
        }

    }
    return false;
}

void Block::rightClickAction()
{
    hostImpl->deleteBlock(name);
};

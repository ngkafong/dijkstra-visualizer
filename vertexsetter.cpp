#include "vertexsetter.h"

#include <QEvent>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>

Vertexsetter::Vertexsetter(QLabel *templateLabel, Impl *hostImpl, QWidget *parent)
    : QLabel(parent),
      hostImpl(hostImpl)
{
    setGeometry(templateLabel->geometry());
    setAutoFillBackground(false);
    setStyleSheet("QLabel { background-color : none; }");
    setVisible(false);
    setMouseTracking(true);
    installEventFilter(this);
}

bool
Vertexsetter::eventFilter(QObject *, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {

        QMouseEvent *e = static_cast<QMouseEvent*>(event);
        if (rect().contains(e->pos())
                && e->button() == Qt::LeftButton) {
            selectedPoint = e->pos();
            update();
            hostImpl -> addVertex(selectedPoint);
        }
    }

    return false;
}



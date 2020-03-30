#ifndef POINT_H
#define POINT_H

#include "impl.h"

#include <QLabel>
#include <QPoint>
#include <QPushButton>

class Vertexsetter : public QLabel
{
public:
   Vertexsetter (QLabel *templateLabel,
   Impl *hostImpl,
          QWidget *parent = nullptr);

protected slots:
    bool eventFilter(QObject *, QEvent *event) override;

private:
    Impl *hostImpl;
    QPoint selectedPoint;
};

#endif // POINT_H


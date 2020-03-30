#ifndef BLOCK_H
#define BLOCK_H

#include "impl.h"

#include <QLabel>
#include <QBitmap>

class Block : public QLabel
{
    Q_OBJECT

public:
    Block(std::string name, Impl *hostImpl, QWidget *parent);
    std::string getName(){return name;};

protected slots:
    bool eventFilter(QObject *, QEvent *event) override;

protected:

    virtual void rightClickAction();
    Impl *hostImpl;
    std::string name;

private:

};

#endif // BLOCK_H

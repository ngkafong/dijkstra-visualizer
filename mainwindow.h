#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "impl.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_drawVertexButton_toggled(bool checked);

    void on_drawEdgeButton_toggled(bool checked);

    void on_startButton_toggled(bool checked);

    void on_stepButton_clicked();

    void on_clearButton_clicked();

    void on_showPathButton_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    Impl *impl;
};
#endif // MAINWINDOW_H

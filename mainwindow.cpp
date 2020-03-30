#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    impl = new Impl(ui->backgroundLabel);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_drawVertexButton_toggled(bool checked)
{
    if (checked == true){ ui->drawEdgeButton->setChecked(false);}
    impl->setVertex(checked);
}



void MainWindow::on_drawEdgeButton_toggled(bool checked)
{
    if (checked == true){ui->drawVertexButton->setChecked(false);}
    impl->setEdge(checked);
}

void MainWindow::on_startButton_toggled(bool checked)
{
    if (checked == true){
        ui->drawVertexButton->setChecked(false);
        ui->drawEdgeButton->setChecked(false);}
    impl->setDijkstra(checked);
}

void MainWindow::on_stepButton_clicked()
{
    impl->runDijkstra();

}

void MainWindow::on_clearButton_clicked()
{
    ui->stepButton->setChecked(false);
    ui->showPathButton->setChecked(false);
}

void MainWindow::on_showPathButton_toggled(bool checked)
{
    impl->setPathDrawer(checked);
}

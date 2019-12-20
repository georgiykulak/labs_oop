#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionEdit_triggered()
{
    QMessageBox::information(this, "Title", "Smth");
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this, "Title", "Smth");
}

void MainWindow::on_actionExit_triggered()
{
    QMessageBox::information(this, "Title", "Smth");

    QApplication::quit();
}

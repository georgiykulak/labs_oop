#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
private:
    Q_OBJECT

public:
    ~MainWindow();

    MainWindow ( QWidget * parent = nullptr );

private slots:
    void on_actionEdit_triggered ();

    void on_actionAbout_triggered ();

    void on_actionExit_triggered ();

private:
    Ui::MainWindow * ui;
};

#endif // MAINWINDOW_H //

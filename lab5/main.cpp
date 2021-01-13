#include "mainwindow.h"
#include "clock.h"

#include <QApplication>

int main ( int argc, char *argv[] )
{
    QApplication a( argc, argv );

    DigitalClock clock;
    clock.init( "Lab #5" );
    clock.show();

    return a.exec();
}

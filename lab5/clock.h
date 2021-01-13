#ifndef CLOCK_H
#define CLOCK_H

#include <QtWidgets>
#include <QLCDNumber>
#include <QString>
#include <QMenu>
#include <QMenuBar>

class DigitalClock : public QLCDNumber
{
private:
    Q_OBJECT
    QTimer* timer;

public:
    ~DigitalClock ();

    DigitalClock ( QWidget * parent = nullptr );
    
    void init ( QString progname = "Clock", int x = 400, int y = 300 );

private slots:
    void showTime ();
};

#endif // CLOCK_H //

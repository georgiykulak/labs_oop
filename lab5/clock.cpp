#include "clock.h"
#include <QtWidgets>

DigitalClock::~DigitalClock()
{
    delete timer;
}

DigitalClock::DigitalClock ( QWidget * parent )
    :   QLCDNumber( parent )
    ,   timer{ new QTimer( this ) }
{
    connect( timer, &QTimer::timeout, this, &DigitalClock::showTime );
}

void DigitalClock::init ( QString progname, int x, int y )
{
    setSegmentStyle( Filled );

    timer->start( 1000 );

    setWindowTitle( tr( progname.toLocal8Bit().data() ) );

    resize( x, y );

    setMinimumSize( 120, 90 );

    showTime();
}

void DigitalClock::showTime()
{
    QTime time = QTime::currentTime();
    QString text = time.toString( "hh:mm" );

    if ( !( time.second() % 2 ) )
    {
        text[ 2 ] = ' ';
    }

    display( text );
}

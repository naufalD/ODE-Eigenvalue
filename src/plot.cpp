#include "include/plot.h"

#include <QwtPlotGrid>

Plot::Plot( QWidget* parent) : QwtPlot(parent)
{
    setTitle( "Quantum Well ");
    setCanvasBackground( Qt::white );
    setMinimumSize(300,300);
    //setAxisScale( QwtAxis::YLeft, -1.1, 1.1 );
    //setAxisScale( QwtAxis::XBottom, 0, 50.5 );

    QwtPlotGrid* grid = new QwtPlotGrid();
    grid->attach( this );
}

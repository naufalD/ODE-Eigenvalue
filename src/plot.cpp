#include "include/plot.h"

#include <QwtPlotGrid>

Plot::Plot( QWidget* parent) : QwtPlot(parent)
{
    setTitle( "Quantum Well ");
    setCanvasBackground( Qt::white );
    setMinimumSize(300,300);
    //setAxisScale( QwtAxis::YLeft, -40, 5 );
    //setAxisScale( QwtAxis::XBottom, 0, 50.5 );

    m_curve1 = new QwtPlotCurve();
    m_curve1->setPen(Qt::blue, 3);
    m_curve1->setCurveAttribute(QwtPlotCurve::Fitted, true);
    m_curve1->attach(this);

    m_curve2 = new QwtPlotCurve();
    m_curve2->setPen(Qt::red, 3);
    m_curve2->setCurveAttribute(QwtPlotCurve::Fitted, true);
    m_curve2->attach(this);

    m_curveWell = new QwtPlotCurve();
    m_curveWell->setPen(Qt::black, 2);
    //m_curveWell->setCurveAttribute(QwtPlotCurve::Fitted, true);
    m_curveWell->attach(this);

    QwtPlotGrid* grid = new QwtPlotGrid();
    grid->attach( this );
}

void Plot::plotWell(double x, double y){
    m_pointsWell<<QPointF(x, y);
    m_curveWell->setSamples(m_pointsWell);
}

void Plot::updatePlot1(double x, double y){
    m_points1<<QPointF(x, y);
    m_curve1->setSamples(m_points1);
}

void Plot::updatePlot2(double x, double y){
    m_points2<<QPointF(x, y);
    m_curve2->setSamples(m_points2);
}

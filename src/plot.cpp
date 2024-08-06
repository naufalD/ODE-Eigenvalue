#include "include/plot.h"

#include <QwtPlotGrid>

Plot::Plot( QWidget* parent) : QwtPlot(parent)
{
    setTitle( "Quantum Well ");
    setCanvasBackground( Qt::white );
    setMinimumSize(300,300);
    //setAxisScale( QwtAxis::YLeft, -40, 5 );
    //setAxisScale( QwtAxis::XBottom, 0, 50.5 );


    for (int i {0}; i<4;++i){
        m_curve1[i] = new QwtPlotCurve();
        m_curve1[i]->setPen(Qt::blue, 1.5);
        m_curve1[i]->setCurveAttribute(QwtPlotCurve::Fitted, true);
        m_curve1[i]->attach(this);
    }

    for (int i {0}; i<4;++i){
        m_curve2[i] = new QwtPlotCurve();
        m_curve2[i]->setPen(Qt::red, 1.5);
        m_curve2[i]->setCurveAttribute(QwtPlotCurve::Fitted, true);
        m_curve2[i]->attach(this);
    }

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

void Plot::updatePlot1(int i, double x, double y){
    m_points1[i]<<QPointF(x, y);
    m_curve1[i]->setSamples(m_points1[i]);
}

void Plot::updatePlot2(int i, double x, double y){
    m_points2[i]<<QPointF(x, y);
    m_curve2[i]->setSamples(m_points2[i]);
}

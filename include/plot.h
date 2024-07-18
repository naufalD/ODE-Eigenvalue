#ifndef PLOT_H
#define PLOT_H

#include <QwtPlot>
#include <QwtPlotCurve>

class Plot : public QwtPlot
{
public:
    Plot(QWidget* parent = nullptr);
    void plotWell(double x, double y);
    void updatePlot1(double x, double y);
    void updatePlot2(double x, double y);

private:
    QwtPlotCurve* m_curve1;
    QwtPlotCurve* m_curve2;
    QwtPlotCurve* m_curveWell;
    QPolygonF m_points1;
    QPolygonF m_points2;
    QPolygonF m_pointsWell;
};

#endif // PLOT_H

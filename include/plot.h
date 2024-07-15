#ifndef PLOT_H
#define PLOT_H

#include <QwtPlot>

class Plot : public QwtPlot
{
public:
    Plot(QWidget* parent = nullptr);
};

#endif // PLOT_H

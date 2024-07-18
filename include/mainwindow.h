#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "plot.h"

#include <QWidget>
#include <QElapsedTimer>
#include <QwtPlot>
#include <QLabel>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

protected:
    virtual void timerEvent( QTimerEvent* ) QWT_OVERRIDE;

private:
    Plot *m_plot;
    QLabel *m_label;
};
#endif // MAINWINDOW_H

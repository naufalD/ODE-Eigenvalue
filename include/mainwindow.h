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
    void plotRK4();
    void plotNumerov();
    void plotRK4logd();
    void plotNumlogd();

private:
    Plot *m_plot1;
    QLabel *m_label1[4];
    Plot *m_plot2;
    QLabel *m_label2[4];
};
#endif // MAINWINDOW_H

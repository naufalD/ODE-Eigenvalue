#include "include/mainwindow.h"
#include "include/eigenvalueode.h"

#include <cmath>
#include <QLayout>

using namespace std;

static double dh {0.01};
//static double E  {-10}; //MeV
static double V0 {35}; //MeV
//static double mu  {0.50412241252*931.5}; //MeV
//static double hBar {6.582119569}; //Mev*s
//static double m {2.0141*931.5}; //MeV
static double accuracy {pow(10, -3)};
static double R {2.1};
static double xMatch {2.1};
static double farValue {pow(10,-2)};

double Vr(double radius, double V){
    if (abs(radius)<R) return -V;
    else return 0;
}

// double kSq(double radius, double E){
//     return (2*mu)*(Vr(radius, V0)+E)/pow(hBar, 2);
// }

vector<double> theFunction(double x, double E, vector<double> y){
    //return {y[1], kSq(x, E)*-y[0]};
    return {y[1], -(0.4829)*(E-Vr(x, V0))*y[0]};
}

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    m_plot = new Plot();
    m_label = new QLabel();
    for (double i {-(R+1)}; i<(R+1); i=i+0.01){
        m_plot->plotWell(i, Vr(i, V0));
    }

    double E1 {-20};
    double E2 {-0.5};
    double E {E1};
    //double EBest {E1};
    //double ErrBest {1};
    vector<double> y1 {0,0};
    vector<double> y2 {0,0};
    y1[0] = -farValue;
    y1[1]= -sqrt(-E*0.4829)*y1[0];

    y2[0] = farValue;
    y2[1]= -sqrt(-E*0.4829)*y2[0];



    double normDelta1 {1};
    double normDelta2 {1};

    for (double i {-50}; i<xMatch; i=i+dh){
        y1 = odeRK4(dh, i, E, y1, &theFunction);
    }

    for (double i {50}; i>xMatch; i=i-dh){
        y2 = odeRK4(-dh, i, E, y2, &theFunction);
    }
    normDelta1 = deltaNormWave(y1, y2);

    double rounds {0};

    while (abs(normDelta2)>accuracy&&rounds<1000){

        E = (E1+E2)/2.0;
        rounds +=1;

        y1[0] = -farValue;
        y1[1]= -sqrt(-E*0.4829)*y1[0];

        y2[0] = farValue;
        y2[1]= -sqrt(-E*0.4829)*y2[0];

        for (double i {-50}; i<xMatch; i=i+dh){
            y1 = odeRK4(dh, i, E, y1, &theFunction);
        }

        for (double i {50}; i>xMatch; i=i-dh){
            y2 = odeRK4(-dh, i, E, y2, &theFunction);
        }

        normDelta2 = deltaNormWave(y1, y2);

        if (normDelta1*normDelta2<0){
            E2 = E;
        }
        else{
            E1 = E;
            normDelta1 = normDelta2;
        }
    }
    double renorm = y1[0]/y2[0];

    y1[0] = -farValue;
    y1[1]= -sqrt(-E*0.4829)*y1[0];

    y2[0] = farValue;
    y2[1]= -sqrt(-E*0.4829)*y2[0];

    for (double i {-50}; i<xMatch; i=i+dh){
        y1 = odeRK4(dh, i, E, y1, &theFunction);
        if (i>-(R+2)) m_plot->updatePlot1(i, y1[0]*pow(10,-8));
    }

    for (double i {50}; i>xMatch; i=i-dh){
        y2 = odeRK4(-dh, i, E, y2, &theFunction);
        if (i<(R+2)) m_plot->updatePlot2(i, y2[0]*renorm*pow(10,-8));
    }
    m_label->setText(QString::number(E));

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(m_plot);
    layout->addWidget(m_label);
}

void MainWindow::timerEvent(QTimerEvent*){

}



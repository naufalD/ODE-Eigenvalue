#include "include/mainwindow.h"
#include "include/eigenvalueode.h"

#include <cmath>
#include <QLayout>

using namespace std;


static double V0 {40}; //eV
static double mu  {0.510*pow(10,6)}; //eV
static double hBarc {1974.6}; //eV*Angstrom
static double constQ {(2*mu)/pow(hBarc,2)};
//static double constQ {0.0483};

static double dh {0.01};
static double accuracy {pow(10, -6)};
static double R {3*0.529}; // angstrom
static double xMatch {0.529};
static double farValue {0.00001};
static double farX {15};
static double startE {0};
static double endE {5};
static int numberLevels {4};


double Vr(double radius, double V){
    //return pow(radius, 2);
    if (abs(radius)<R) return 0;
    else return V0;
}

 double kSq(double radius, double E){
    return -(constQ)*(E-Vr(radius, V0));
}

 double kSq2(double radius, double E){
     return (constQ)*(E-Vr(radius, V0));
 }

vector<double> theFunction(double x, double E, vector<double> y){
    return {y[1], kSq(x, E)*y[0]};
}

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    m_plot1 = new Plot();
    m_plot1->setTitle("Runge-Kutta 4");
    m_plot2 = new Plot();
    m_plot2->setTitle("Numerov");
    for (int index {0};index<numberLevels;++index){
        m_label1[index] = new QLabel();
        m_label2[index] = new QLabel();
    }

    for (double i {-(R+3)}; i<(R+3); i=i+dh){
        m_plot1->plotWell(i, Vr(i, V0));
        m_plot2->plotWell(i, Vr(i, V0));
    }

    plotRK4();
    plotNumerov();

    QHBoxLayout* layout1 = new QHBoxLayout();
    QVBoxLayout* layout11 = new QVBoxLayout();
    for (int index {0};index<numberLevels;++index) layout11->addWidget(m_label1[index]);
    layout1->addWidget(m_plot1);
    layout1->addLayout(layout11);


    QHBoxLayout* layout2 = new QHBoxLayout();
    QVBoxLayout* layout21 = new QVBoxLayout();
    for (int index {0};index<numberLevels;++index) layout21->addWidget(m_label2[index]);
    layout2->addWidget(m_plot2);
    layout2->addLayout(layout21);


    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addLayout(layout1);
    layout->addLayout(layout2);
}

void MainWindow::plotRK4(){
    double E1 {startE};
    double E2 {endE};
    double E {E1};
    vector<double> y1 {0,0};
    vector<double> y2 {0,0};
    int sizeLeft {static_cast<int>((xMatch+farX)/dh)};
    int sizeRight {static_cast<int>((abs(xMatch-farX))/dh)};


    for (int index {0}; index<numberLevels; ++index){
        y1[0] = farValue;
        y1[1]= -sqrt(E*constQ)*y1[0];
        y2[0] = farValue;
        y2[1]= y1[1];

        double normDelta1 {1};
        double normDelta2 {1};

        for (int i {0}; i<sizeLeft; ++i){
            y1 = odeRK4(dh, -farX+i*dh, E, y1, &theFunction);
        }

        for (int i {0}; i<sizeRight; ++i){
             y2 = odeRK4(-dh, farX-i*dh, E, y2, &theFunction);
        }
        normDelta1 = deltaNormWave(y1, y2);

        double errorTerm {1};
        double rounds {0};
        vector<double> leftWave(sizeLeft, 0);
        vector<double> rightWave(sizeRight, 0);


        while (abs(errorTerm)>accuracy&&rounds<1000){

            E = (E1+E2)/2.0;
            rounds +=1;

            y1[0] = -farValue;
            y1[1]= -sqrt(E*constQ)*y1[0];
            y2[0] = farValue;
            y2[1]= y1[1];

            for (int i {0}; i<sizeLeft; ++i){
                y1 = odeRK4(dh, -farX+i*dh, E, y1, &theFunction);
                leftWave[i] = y1[0];
            }

            for (int i {0}; i<sizeRight; ++i){
                y2 = odeRK4(-dh, farX-i*dh, E, y2, &theFunction);
                rightWave[i] = y2[0];
            }

            normDelta2 = deltaNormWave(y1, y2);

            if (normDelta1*normDelta2<0){
                E2 = E;
            }
            else{
                E1 = E;
                normDelta1 = normDelta2;
            }
            errorTerm = E1-E2;
        }

        double renorm = y1[0]/y2[0];
        double sum {0};

        for (int i {0}; i<sizeLeft; ++i){
            leftWave[i] = pow(leftWave[i],2);
            if (abs(leftWave[i])>sum) sum = leftWave[i];
        }
        for (int i {0}; i<sizeRight; ++i){
            rightWave[i] = pow(rightWave[i]*renorm,2);
            if (abs(leftWave[i])>sum) sum = rightWave[i];
        }



        for (int i {0}; i<sizeLeft; ++i){
            m_plot1->updatePlot1(index, -farX+i*dh, leftWave[i]/sum+E);
        }
        for (int i {0}; i<sizeRight; ++i){
            m_plot1->updatePlot2(index, farX-i*dh, rightWave[i]/sum+E);
        }

        m_label1[index]->setText(QString::number(E)+" eV");
        E1 = E;
        if (E+20>V0) E2=V0;
        else E2 = E+20;
    }
}

void MainWindow::plotNumerov(){
    double E1 {startE};
    double E2 {endE};
    double E {E1};

    for (int index {0};index<numberLevels; ++index){

        double y11 {-farValue};
        double y12 {-farValue};
        double y1temp {0};
        double y21 {farValue};
        double y22 {farValue};
        double y2temp {0};

        int sizeLeft {static_cast<int>((xMatch+farX)/dh)};
        int sizeRight {static_cast<int>((abs(xMatch-farX))/dh)};

        double normDelta1 {1};
        double normDelta2 {1};

        for (int i {0}; i<sizeLeft; ++i){
            y1temp = numerovODE(dh, -farX+i*dh, E, y11, y12, &kSq2);
            if (i<sizeLeft-1){
                y12=y11;
                y11=y1temp;
            }
        }

        for (int i {0}; i<sizeRight; ++i){
            y2temp = numerovODE(-dh, farX-i*dh, E, y21, y22, &kSq2);
            if (i<sizeRight-1){
                y22=y21;
                y21=y2temp;
            }
        }
        normDelta1 = deltaNormWaveNumerov({y1temp, y11}, {y2temp, y21});

        double errorTerm {1};
        double rounds {0};
        vector<double> leftWave(sizeLeft, 0);
        vector<double> rightWave(sizeRight, 0);

        while (abs(errorTerm)>accuracy&&rounds<10){
            E = (E1+E2)/2.0;
            rounds +=1;

            for (int i {0}; i<sizeLeft; ++i){
                y1temp = numerovODE(dh, -farX+i*dh, E, y11, y12, &kSq2);
                leftWave[i] = y1temp;
                if (i<sizeLeft-1){
                    y12=y11;
                    y11=y1temp;
                }
            }

            for (int i {0}; i<sizeRight; ++i){
                y2temp = numerovODE(-dh, farX-i*dh, E, y21, y22, &kSq2);
                rightWave[i] = y2temp;
                if (i<sizeRight-1){
                    y22=y21;
                    y21=y2temp;
                }
            }

            normDelta2 = deltaNormWaveNumerov({y1temp, y11}, {y2temp, y21});

            if (normDelta1*normDelta2<0){
                E2 = E;
            }
            else{
                E1 = E;
                normDelta1 = normDelta2;
            }
            errorTerm = E2-E1;
        }

        double renorm = y1temp/y2temp;
        double sum {0};

        for (int i {0}; i<sizeLeft; ++i){
            leftWave[i] = pow(leftWave[i],2);
            if (abs(leftWave[i])>sum) sum = leftWave[i];
        }
        for (int i {0}; i<sizeRight; ++i){
            rightWave[i] = pow(rightWave[i]*renorm,2);
            if (abs(rightWave[i])>sum) sum = rightWave[i];
        }

        for (int i {0}; i<sizeLeft; ++i){
            m_plot2->updatePlot1(index, -farX+i*dh, leftWave[i]/sum+E);
        }
        for (int i {0}; i<sizeRight; ++i){
            m_plot2->updatePlot2(index, farX-i*dh, rightWave[i]/sum+E);
        }

        m_label2[index]->setText(QString::number(E)+" eV");
        E1 = E;
        if (E+20>V0)E2 = V0;
        else E2 = E+20;
    }
}

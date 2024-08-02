#include "include/eigenvalueode.h"

#include <cmath>

double numerovODE(double h, double t, double E, double yMinus1, double yMinus2, function<double(double, double)> kSq){
    double tempH {pow(h, 2)/12.0};
    double tempNum {0};
    double numerator1 {0};
    double numerator2 {0};

    tempNum = 2.0*(1.0-5.0*tempH*kSq(t-h, E));
    numerator1 = tempNum*yMinus1;

    tempNum = (1.0+tempH*kSq(t-2*h, E));
    numerator2 = tempNum*yMinus2;

    double denominator {1.0+tempH*kSq(t,E)};

    numerator2 = (numerator1-numerator2)/denominator;
    return numerator2;
}

vector<double> odeRK4(double h, double t, double E, vector<double> yMinus1,  function<vector<double>(double, double, vector<double>)> theFunction){
    int size {static_cast<int>(yMinus1.size())};
    vector<double> temp(size, 0);

    vector<double> k1 {theFunction(t-h, E, yMinus1)};
    for (int i {0}; i<size;++i){
        k1[i] = h*k1[i];
        temp[i] = yMinus1[i]+ k1[i]/2.0;
    }

    vector<double> k2 {theFunction(t-(h/2.0),E, temp)};
    for (int i {0}; i<size;++i){
        k2[i] = h*k2[i];
        temp[i] = yMinus1[i]+ k2[i]/2.0;
    }


    vector<double> k3 {theFunction(t-(h/2.0),E, temp)};
    for (int i {0}; i<size;++i){
        k3[i] = h*k3[i];
        temp[i] = yMinus1[i]+ k3[i];
    }

    vector<double> k4 {theFunction(t,E, temp)};
    for (int i {0}; i<size;++i) k4[i] = h*k4[i];

    vector<double> toReturn(size, 0);
    for (int i {0}; i<size;++i) toReturn[i] = yMinus1[i] +(1.0/6.0)*(k1[i]+2.0*k2[i]+2.0*k3[i]+k4[i]);

    return toReturn;
}

double deltaNormWave(vector<double> yL, vector<double>yR){
    double L {0};
    double R {0};
    L = yL[1]/yL[0];
    R = yR[1]/yR[0];

    return (L-R)/(L+R);
}

double deltaNormWaveNumerov(vector<double> yL, vector<double>yR){
    double L {0};
    double R {0};
    L = (yL[0]-yL[1])*yR[0];
    R = (yR[0]-yR[1])*yL[0];

    return (L-R)/(L+R);
}

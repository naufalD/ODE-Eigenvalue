#include "include/eigenvalueode.h"

#include <cmath>

vector<double> numerovODE(double h, vector<double> kSq, vector<double> yMinus1, vector<double> yMinus2,  function<vector<double>(double, vector<double>)> theFunction){
    int size {static_cast<int>(yMinus1.size())};
    double tempH {pow(h, 2)/12};
    double tempNum {0};
    vector<double> numerator1(size, 0);
    vector<double> numerator2(size, 0);

    tempNum = (1-5*tempH*kSq[1])*2;
    for (int i {0}; i<size;++i) numerator1[i] = tempNum*yMinus1[i];

    tempNum = (1+tempH*kSq[0]);
    for (int i {0}; i<size;++i) numerator2[i] = tempNum*yMinus2[i];

    double denominator {1+pow(h,2)*kSq[2]/12};

    for (int i {0}; i<size;++i) numerator2[i] = (numerator1[i]-numerator1[i])/denominator;
    return numerator2;
}

vector<double> odeRK4(double h, double t, double kSq, vector<double> yMinus1,  function<vector<double>(double, double, vector<double>)> theFunction){
    int size {static_cast<int>(yMinus1.size())};
    vector<double> temp(size, 0);

    vector<double> k1 {theFunction(t-h, kSq, yMinus1)};
    for (int i {0}; i<size;++i){
        k1[i] = h*k1[i];
        temp[i] = yMinus1[i]+ k1[i]/2.0;
    }

    vector<double> k2 {theFunction(t-(h/2.0),kSq, temp)};
    for (int i {0}; i<size;++i){
        k2[i] = h*k2[i];
        temp[i] = yMinus1[i]+ k2[i]/2.0;
    }


    vector<double> k3 {theFunction(t-(h/2.0),kSq, temp)};
    for (int i {0}; i<size;++i){
        k3[i] = h*k3[i];
        temp[i] = yMinus1[i]+ k3[i];
    }

    vector<double> k4 {theFunction(t,kSq, temp)};
    for (int i {0}; i<size;++i) k4[i] = h*k4[i];

    vector<double> toReturn(size, 0);
    for (int i {0}; i<size;++i) toReturn[i] = yMinus1[i] +(1.0/6.0)*(k1[i]+2*k2[i]+2*k3[i]+k4[i]);

    return toReturn;
}

double deltaNormWave(vector<double> yL, vector<double>yR){
    double L {0};
    double R {0};
    L = yL[1]/yL[0];
    R = yR[1]/yR[0];

    return (L-R)/(L+R);
}

#include "include/eigenvalueode.h"

#include <cmath>

double kSq(double x){
    return pow(x, 2);
}

vector<double> odeRK4(double h, double t, vector<double> yMinus1,  function<vector<double>(double, vector<double>)> theFunction){
    vector<double> k1 {theFunction(t-h, yMinus1)};
    k1 = {h*k1[0], h*k1[1]};
    vector<double> k2 {theFunction(t-(h/2.0), {yMinus1[0]+(k1[0]/2.0), yMinus1[1]+(k1[1]/2.0)})};
    k2 = {h*k2[0], h*k2[1]};
    vector<double> k3 {theFunction(t-(h/2.0), {yMinus1[0]+(k1[0]/2.0), yMinus1[1]+(k2[1]/2.0)})};
    k3 = {h*k3[0], h*k3[1]};
    vector<double> k4 {theFunction(t, {yMinus1[0]+k3[0], yMinus1[1]+k3[1]})};
    k4 = {h*k4[0], h*k4[1]};
    return {yMinus1[0] +(1.0/6.0)*(k1[0]+2*k2[0]+2*k3[0]+k4[0]), yMinus1[1] +(1.0/6.0)*(k1[1]+2*k2[1]+2*k3[1]+k4[1])};
}



double numerovODE(double h, double t, vector<double> yMinus1,  function<vector<double>(double, vector<double>)> theFunction){
    double numerator1 {2*theFunction(yMinus1)*(1-(5/12)*pow(h,2)*kSq())};
    double numerator2 {theFunction(yMinus1)*(1+(5/12)*pow(h,2)*kSq())};
    double denominator {1+pow(h,2)*kSq()/12}
}

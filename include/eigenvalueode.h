#ifndef EIGENVALUEODE_H
#define EIGENVALUEODE_H

#include <functional>

using namespace std;


vector<double> numerovODE(double h, vector<double> kSq, vector<double> yMinus1, vector<double> yMinus2,  function<vector<double>(double, vector<double>)> theFunction);
vector<double> odeRK4(double h, double t, double E, vector<double> yMinus1, function<vector<double>(double, double, vector<double>)> theFunction);
double deltaNormWave(vector<double> yL, vector<double>yR);

#endif // EIGENVALUEODE_H

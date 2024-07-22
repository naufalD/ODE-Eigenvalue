#ifndef EIGENVALUEODE_H
#define EIGENVALUEODE_H

#include <functional>

using namespace std;

double numerovODE(double h, double t, double E, double yMinus1, double yMinus2, function<double(double, double)> kSq);
vector<double> odeRK4(double h, double t, double E, vector<double> yMinus1, function<vector<double>(double, double, vector<double>)> theFunction);
double deltaNormWave(vector<double> yL, vector<double>yR);
double deltaNormWaveNumerov(vector<double> yL, vector<double>yR);

#endif // EIGENVALUEODE_H

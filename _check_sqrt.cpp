#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>
#include <list>
#include <functional>
#include <queue>
#include <iterator>
#include <cmath>

using namespace std;

const double EPS = 1e-6;

// Newton's formula: x_n+1 = x_n - f(x_n) / f'(x_n)
// square root: x_n+1 = (1/2) * (x_n + a / x_n);
// cubic root: x_n+1 = (1/3) * (2 * x_n + a / x_n^2);
double SqrtNewton(int x) {
    if (x == 0)
        return 0;
    double res = x;
    for (int i = 0; i < 50; ++i)
        res = 0.5 * (res + x / res);
    return res;
}

double SqrtBinSearch(int x) {
    double l = 0, r = x;
    for (int i = 0; i < 50; ++i) {
        double m = (l + r) / 2;
        if (m * m <= x)
            l = m;
        else
            r = m;
    }
    return (l + r) / 2;
}

int main()
{
    for (int i = 0; i < 1000 * 1000; ++i)
        if (fabs(sqrt(1. * i) - SqrtNewton(i)) >= EPS || fabs(sqrt(1. * i) - SqrtBinSearch(i)) >= EPS)
            cerr << "Error! - " << i << endl;
    cerr << "Done!\n";
    return 0;
}      


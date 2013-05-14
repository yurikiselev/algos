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

double Pow(double x, int n) {
    bool negativ = n < 0;
    n = abs(n);
    double res = 1.;
    while (n) {
        if (n & 1)
            res *= x;
        x *= x;
        n /= 2;
    }
    return (negativ ? 1. / res : res);
}

int main()
{
    for (int i = 0; i < 1000 * 1000; ++i) {
        double x = 1. * (rand() % 2000) / 1000.;
        if (rand() % 2)
            x = -x;
        int n = rand() % 100;
        if (fabs(pow(x, n) - Pow(x, n)) >= EPS)
            cerr << "Error! - " << i << endl;
        if (i % 100000 == 0)
            printf("x = %.6lf, n = %d, pow(x, n) = %.9lf\n", x, n, pow(x, n));
    }
    cerr << "Done!\n";
    return 0;
}      


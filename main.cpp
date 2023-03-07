#include <iostream>
#include "Jacobi.h"
#include <vector>
using namespace std;

int main() {
    vector<vector<double>> a{{2, -1, 0}, {-1, 2, -1}, {0, -1, 2}};
    double eps = 1e-15;
    int nMaxIterNum = 100;
    Jacobi ja(a, eps, nMaxIterNum);
    ja.calEigen();
    return 0;
}

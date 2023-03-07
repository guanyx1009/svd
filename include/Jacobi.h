//
// Created by guanyx on 23-3-5.
//

#ifndef SVD_JACOBI_H
#define SVD_JACOBI_H

#include <vector>
#include <iostream>
#include <cmath>

class Jacobi{
public:
    double m_Eps;
    int m_nMaxIterNum;
    int m_nDim;
    std::vector<std::vector<double>> m_a; // symmetric matrix;
    std::vector<std::vector<double>> m_eigenVec;

public:
    Jacobi() {}
    ~Jacobi() {}
    Jacobi(const std::vector<std::vector<double>> &rhs, double Eps, int nMaxIterNum);
    void calEigen();
    void findMaxElement(int &row, int &col, double &maxElement);
    void Givens(int p, int q);
    void output();
};

Jacobi::Jacobi(const std::vector<std::vector<double>> &rhs, double Eps, int nMaxIterNum) {
    this->m_a = rhs;
    this->m_Eps = Eps;
    this->m_nMaxIterNum = nMaxIterNum;
    this->m_nDim = rhs.size();
    this->m_eigenVec.resize(m_nDim);
    for (int i = 0; i < m_nDim; i++)
    {
        m_eigenVec[i].resize(m_nDim, 0.0);
        m_eigenVec[i][i] = 1.0;
    }
}

void Jacobi::calEigen() {
    // Verify that it is a symmetric matrix
    for (int i = 0; i < m_nDim; i++)
    {
        for (int j = 0; j < m_nDim; j++)
        {
            if (i != j)
            {
                if (m_a[i][j] != m_a[j][i])
                {
                    std::cout << "matrix is not symmetry" << std::endl;
                    exit(1);
                }
            }
        }
    }

    int nCount = 0;
    double maxElement;
    int row, col;

    while(nCount < m_nMaxIterNum)
    {
        findMaxElement(row, col, maxElement);

        if (maxElement < m_Eps) break;

        Givens(row, col);
        nCount++;
    }

    std::cout << "iterate number " << nCount << std::endl;
    output();
}

void Jacobi::findMaxElement(int &row, int &col, double &maxElement) {
    maxElement = fabs(m_a[0][1]);
    row = 0, col = 1;
    for (int i = 0; i < m_nDim; i++)
    {
        for (int j = 0; j < m_nDim; j++)
        {
            double element = fabs(m_a[i][j]);
            if ((element > maxElement) && (i != j))
            {
                maxElement = element;
                row = i;
                col = j;
            }
        }
    }
}

void Jacobi::Givens(const int p, const int q) {
    // calculate rotation angle;
    double theta, sn, cs, sn2theta, cs2theta;
    if (fabs(m_a[p][p] - m_a[q][q]) < 1e-15)
    {
        if (m_a[p][q] < 0)
        {
            sn = -1 / sqrt(2);
            cs = 1 / sqrt(2);
            sn2theta = -1;
            cs2theta = 0;
        }
        else if (m_a[p][q] > 0 )
        {
            sn = 1 / sqrt(2);
            cs = 1 / sqrt(2);
            sn2theta = 1;
            cs2theta = 0;
        }
    }
    else
    {
        theta = 0.5 * atan2(2 * m_a[p][q], (m_a[p][p] - m_a[q][q]));
        sn = sin(theta);
        cs = cos(theta);
        sn2theta = sin(2 * theta);
        cs2theta = cos(2 * theta);
    }


    // calculate each element of matrix a
    double app = m_a[p][p];
    double aqq = m_a[q][q];
    double apq = m_a[p][q];

    m_a[p][p] = app * cs * cs + aqq * sn * sn + apq * sn2theta;
    m_a[q][q] = app * sn * sn + aqq * cs * cs - apq * sn2theta;
    m_a[p][q] = 0.5 * (aqq - app) * sn2theta + apq * cs2theta;
    m_a[q][p] = m_a[p][q];

    for (int i = 0; i < m_nDim; i++)
    {
        if ((i != p) && (i != q))
        {
            double api = m_a[p][i];
            double aqi = m_a[q][i];

            m_a[p][i] = cs * api + sn * aqi;
            m_a[q][i] = cs * aqi - sn * api;
            m_a[i][p] = m_a[p][i];
            m_a[i][q] = m_a[q][i];
        }
    }

    // calculate eigen vector
    for (int i = 0; i < m_nDim; i++)
    {
        double Eip = m_eigenVec[i][p];
        double Eiq = m_eigenVec[i][q];

        m_eigenVec[i][p] = Eip * cs + Eiq * sn;
        m_eigenVec[i][q] = Eiq * cs - Eip * sn;
    }
}

void Jacobi::output() {
    for (int i = 0; i < m_nDim; i++)
    {
        std::cout << "eigen value = ";
        std::cout << m_a[i][i] << " vector" << std::endl;
        for (int j = 0; j < m_nDim; j++)
        {
            std::cout << m_eigenVec[j][i] << "\t";
        }
        std::cout << std::endl;
    }
}

#endif //SVD_JACOBI_H

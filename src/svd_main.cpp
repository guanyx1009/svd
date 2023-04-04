//
// Created by guanyx on 23-3-27.
//
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include "host_func.h"
#include <Eigen/Dense>
#include <chrono>
#include <opencv2/core.hpp>
#include <opencv2/core/eigen.hpp>
#include <string>
float * B;
float * AUX1;
float *U, *V;

int main(int argc, char** argv) {
    char input [100], fileName[] = {"Matrix/"};
    chdir("../");
    FILE *fp;
    if (argc == 1){
        do
        {
            printf ("Insert matrix name: \n");
            scanf ("%s", input);
            strcat(fileName, input);
        }
        while(openFile(&fp, fileName, "r") == false);
    }
    else if (argc == 2){
        sprintf(fileName, "Matrix/%s", argv[1]);
        if (openFile(&fp, fileName, "r") == false)
            exit(1);
    }


    float *matrix;
    int rows, columns;
    fillRowMajorOrderMatrix(&fp, &matrix, &rows, &columns);
    fclose(fp);

    Eigen::MatrixXd eigenMatrix(rows,columns);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            eigenMatrix(i, j) = matrix[i * columns + j];

    cv::Mat cvA(4, 4, CV_32F);
    cv::eigen2cv(eigenMatrix, cvA);
    cv::Mat u,w,vt;
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;


    cv::SVD::compute(cvA,w,u,vt,cv::SVD::MODIFY_A| cv::SVD::FULL_UV);

    auto t1_eigen = high_resolution_clock::now();
    Eigen::JacobiSVD<Eigen::MatrixXd> svd(eigenMatrix, Eigen::ComputeThinU | Eigen::ComputeThinV);
    auto t2_eigen = high_resolution_clock::now();

/* Getting number of milliseconds as a double. */
    duration<double, std::milli> ms_double_eigen = t2_eigen - t1_eigen;

    std::cout << "Its singular values are:" << std::endl << svd.singularValues() << std::endl;
//    std::cout << "Its left singular vectors are the columns of the thin U matrix:" << std::endl << svd.matrixU() << std::endl;
//    std::cout << "Its right singular vectors are the columns of the thin V matrix:" << std::endl << svd.matrixV() << std::endl;

    // Column order matrix

    createColumnMajorOrderMatrix(&B, matrix, rows, columns, &U, &V);
    // initialize AUX1 array to zero
    initializeArray (&AUX1, columns);
    // Open new file to store the singular values
    sprintf(fileName, "SingularValues/C/Singular values CPP2 %dX%d.txt", rows, columns);
    openFile(&fp, fileName, "w");

    //compute one sided jacobi

    int iterations = svd_one_sided_jacobi_CPP(rows, columns);

    printf("iterations: %d \n", iterations);
    fprintf(fp, "iterations: %d \n", iterations);

    float *U_res = (float*)malloc(rows * rows * sizeof(float));
    float *V_res = (float*)malloc(columns * columns * sizeof(float));
    initializeArray (&U_res, rows * rows);
    initializeArray (&V_res, columns * columns);
    descentOrdering(AUX1, columns, &U_res, &V_res, U, V, rows, columns);
    //print array and save on file
    printAndSaveArray (&fp, AUX1, columns);

    fclose(fp);
    std::cout << "U" << std::endl;
    bool isUSame = true;
    Eigen::MatrixXd eigenU = svd.matrixU();
    Eigen::MatrixXd eigenV = svd.matrixV();
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
//            std::cout << U_res[i + j * rows] << " ";
            if (fabsf(fabsf(U_res[i + j * rows]) - fabsf((float)eigenU(i, j))) > 1e-4)
                isUSame = false;
        }
//        std::cout << std::endl;
    }
    std::cout << "V" << std::endl;
    bool isVSame = true;
    for (int i = 0; i < columns; i++)
    {
        for (int j = 0; j < columns; j++)
        {
//            std::cout << V_res[i + j * columns] << " ";
            if (fabsf(fabsf(V_res[i + j * columns]) - fabsf((float)eigenV(i, j))) > 1e-4)
                isVSame = false;
        }
//        std::cout << std::endl;
    }
    std::cout << "U " << isUSame << std::endl;
    std::cout << "V " << isVSame << std::endl;
    const Eigen::VectorXd S = svd.singularValues();
    bool isValSame = true;
    for (int i = 0; i < columns; i++)
    {
        if (fabsf((float)S(i) - AUX1[i]) > 1e-4)
            isValSame = false;
    }
    std::cout << "svd value " << isValSame << std::endl;
    //free the memory
    free(matrix);
    free(U_res);
    free(V_res);
    free(U);
    free(V);
    free(B);
    free(AUX1);

    return 0;
}
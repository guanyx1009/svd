//
// Created by guanyx on 23-3-27.
//

#ifndef SVD_HOST_FUNC_H
#define SVD_HOST_FUNC_H

bool openFile(FILE** fp,const char * fileName, const char * mode);

void fillRowMajorOrderMatrix (FILE** fp, float ** matrix, int * rows, int * columns);

void createColumnMajorOrderMatrix (float ** matCol, float * matRow, int rows, int columns, float **U, float **V);

void initializeArray (float ** arr, int dim);

int svd_one_sided_jacobi_CPP (int rows, int columns);

void descentOrdering (float * arr, int dim, float **U_res, float **V_res, float *U, float *V, int rows, int columns);

void printAndSaveArray (FILE** fp, float * arr, int dim);

//std::vector<std::vector<float>> vec{ { 1.2f, 2.5f, 5.6f, -2.5f },
//				{ -3.6f, 9.2f, 0.5f, 7.2f },
//				{ 4.3f, 1.3f, 9.4f, -3.4f },
//				{ 6.4f, 0.1f, -3.7f, 0.9f } };
//const int rows{ 4 }, cols{ 4 };

//std::vector<std::vector<float>> vec{ { 1.2f, 2.5f, 5.6f, -2.5f },
//				{ -3.6f, 9.2f, 0.5f, 7.2f },
//				{ 4.3f, 1.3f, 9.4f, -3.4f } };
//const int rows{ 3 }, cols{ 4 };

#endif //SVD_HOST_FUNC_H

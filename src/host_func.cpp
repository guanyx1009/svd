//
// Created by guanyx on 23-3-27.
//

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include "host_func.h"

#define MAXCHAR 30000

bool openFile(FILE** fp,const char * fileName, const char * mode){
    if ((*fp = fopen(fileName, mode)) != NULL)
    {
        //printf("File %s in %s opened \n", fileName, directory);
        return true;
    }

    else
    {
        printf("Error while opening file \n");
        return false;
    }
}

void fillRowMajorOrderMatrix (FILE** fp, float ** matrix, int * rows, int * columns) {
    char buf[MAXCHAR];
    char *numChar; //array element (saved as ascii)
    *matrix = (float*)malloc(sizeof(float));
    (*rows) = 0;
    (*columns) = 0;
    int numMatrixEle = 0;
    while (fgets(buf, MAXCHAR, *fp) != NULL){
        numChar = strtok(buf, " ");
        *columns = 0;
        while (numChar != NULL){
            (*matrix)[numMatrixEle] = atof(numChar);
            //printf("A[%d][%d]: %2.9f \t", *rows, *columns, (*matrix)[numMatrixEle]);
            numChar = strtok(NULL, " ");
            (*columns)++;
            numMatrixEle++;
            *matrix= static_cast<float *>(realloc(*matrix, (numMatrixEle + 1) * sizeof(float)));
        }
        //printf("\n");
        (*rows)++;
    }
}

void createColumnMajorOrderMatrix(float ** matCol, float * matRow, int rows, int columns, float **U, float **V){
    *matCol = (float*)malloc(rows * columns * sizeof(float));
    *U = (float*)malloc(rows * rows * sizeof(float));
    *V = (float*)malloc(columns * columns * sizeof(float));
    memset(*U, 0, rows * rows*sizeof(float));
    memset(*V, 0, columns * columns*sizeof(float));
    if(*matCol == NULL || *U == NULL || *V == NULL)
    {
        printf("Out of memory\n");
        exit(1);
    }
    for (int i = 0; i < columns; i++){
        for (int j = 0; j < rows; j++){
            (*matCol)[i*rows+j] = matRow[j*columns+i];
            //printf("matCol[%d]: %2.9f \n", i*rows+j, matCol[i*rows+j]);
        }
    }

    for (int i = 0; i < rows; i++)
    {
        (*U)[i * rows + i] = 1;
    }

    for (int i = 0; i < columns; i++)
    {
        (*V)[i*columns + i] = 1;
    }
}

void initializeArray (float ** arr, int dim){
    *arr = (float*)malloc(dim*sizeof(float));
    memset(*arr, 0, dim*sizeof(*arr[0]));
}

bool sortByVal(const std::pair<float, int> &a, const std::pair<float, int> &b) {
    return a.first > b.first;
}
void descentOrdering (float * arr, int dim, float **U_res, float **V_res, float *U, float *V, int rows, int columns){
    std::vector<std::pair<float, int>> vGroup;
    for (int i = 0; i < dim; i++)
    {
        vGroup.push_back({arr[i], i});
    }
    std::sort(vGroup.begin(), vGroup.end(), sortByVal);
    int k = 0;
    for (auto t : vGroup)
    {
        arr[k] = t.first;
        int index = t.second;
        memcpy(*U_res + k * rows, U + index * rows, rows*sizeof(float));
        memcpy(*V_res + k * columns, V + index * columns, columns*sizeof(float));
        k++;
    }


//    for (int i = 0; i < dim; i++)
//    {
//        for (int j = 0; j < dim; j++)             //Loop for comparing other values
//        {
//            if (arr[j] < arr[i])                //Comparing other array elements
//            {
//                float tmp = arr[i];         //Using temporary variable for storing last value
//                arr[i] = arr[j];            //replacing value
//                arr[j] = tmp;             //storing last value
//            }
//        }
//    }
}

void printAndSaveArray (FILE** fp, float * arr, int dim){
    for (int i = 0; i < dim; i++){
//        printf ("arr[%d]: %f \n", i, arr[i]);
        fprintf(*fp, "%f\n", arr[i]);
    }
}



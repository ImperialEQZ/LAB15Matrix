#include "matrix.h"
//размещает в динамической памяти матрицу размером nRows на nCols. Возвращает матрицу.
matrix getMemMatrix(int nRows, int nCols) {
    int **values = (int **) malloc(sizeof(int*) * nRows);
    for (int i = 0; i < nRows; i++)
        values[i] = (int *) malloc(sizeof(int) * nCols);
    return (matrix){values, nRows, nCols};
}
/*размещает в динамической памяти массив из nMatrices матриц размером nRows на nCols.
Возвращает указатель на нулевую матрицу */
matrix *getMemArrayOfMatrices(int nMatrices,
                              int nRows, int nCols) {
    matrix *ms = (matrix*) malloc(sizeof(matrix) * nMatrices);
    for (int i = 0; i < nMatrices; i++)
        ms[i] = getMemMatrix(nRows, nCols);
    return ms;
}
//освобождает память, выделенную под хранение матрицы m.
void freeMemMatrix(matrix *m) {
    for (size_t i = 0; i < m->nRows; i++)
        free(m->values [i]);

    free(m->values );

    m->values = NULL;
}
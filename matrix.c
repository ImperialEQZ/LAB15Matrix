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
matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols) {
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
//освобождает память, выделенную под хранение массива ms из nMatrices матриц.
void freeMemMatrices(matrix *ms, int nMatrices) {
    for (size_t i = 0; i < nMatrices; i++)
        freeMemMatrix(&ms[i]);
}
//ввод матрицы m.
void inputMatrix(matrix *m) {
    for (size_t i = 0; i < m->nRows; i++)
        for (size_t j = 0; j < m->nCols; j++)
            scanf("%d", &m->values[i] [j]);
}
// ввод массива из nMatrices матриц, хранящейся по адресу ms.
void inputMatrices(matrix *ms, int nMatrices){
    for (size_t i = 0; i < nMatrices; i++)
        inputMatrix(&ms[i]);
}
//вывод матрицы m.
void outputMatrix(matrix m) {
    for (size_t i = 0; i < m.nRows; i++)
        for (size_t j = 0; j < m.nCols; j++)
            printf("%d", m.values[i] [j]);
}
//вывод массива из nMatrices матриц, хранящейся по адресу ms.
void outputMatrices(matrix *ms, int nMatrices) {
    for (size_t i = 0; i < nMatrices; i++)
        outputMatrix(ms[i]);
}
//обмен строк с порядковыми номерами i1 и i2 в матрице m.
void swapRows(matrix m, int i1, int i2) {
    int *imatrix = m.values[i1];

    memcpy(&m.values[i1], &m.values[i2], sizeof(int*));
    memcpy(&m.values[i2], &imatrix, sizeof(int*));
}
//обмен колонок с порядковыми номерами j1 и j2 в матрице m.
void swapColumns(matrix m, int j1, int j2) {
    for (size_t i = 0; i < m.nRows; i++) {
        int j1matrix = m.values[i] [j1];

        memcpy(&m.values[i] [j1], &m.values[i] [j2], sizeof(int*));
        memcpy(&m.values[i] [j2], &j1matrix, sizeof(int*));
    }
}
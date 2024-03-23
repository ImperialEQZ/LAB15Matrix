#include "matrix.h"
#include "matrix.c"

/*Дана квадратная матрица, все элементы которой различны. Поменять местами
строки, в которых находятся максимальный и минимальный элементы */
void Lab16_task1(matrix *m) {
    int min = getMinValuePos(*m).rowIndex;
    int max = getMaxValuePos(*m).rowIndex;
    swapRows(m, max, min);
}
//тест
void test_Lab16_task1() {
    matrix m = createMatrixFromArray((int[]) {
        3, 3, 3,
        4, 4, 4,
        5, 5, 5},
                                     3, 3);
    matrix m_test = createMatrixFromArray((int[]) {
        5, 5, 5,
        4, 4, 4,
        3, 3, 3},
                                          3, 3);
    Lab16_task1(&m);

    assert(areTwoMatricesEqual(&m, &m_test));

    freeMemMatrix(&m);
    freeMemMatrix(&m_test);
}
//Номер 2 лаб 16 (а)
int getMax(int *a, int n) {

    int max = a[0];
    for(size_t i = 0; i < n; i++) {
        if(max < a[i])
            max = a[i];
    }

    return max;
}
//Номер 2 лаб 16 (b)
void sortRowsByMinElement(matrix m) {
    insertionSortRowsMatrixByRowCriteria(&m, getMax);
}

void Lab16_task2(matrix *m) {
    sortRowsByMinElement(*m);
}
//тест
void test_Lab16_task2() {
    matrix m = createMatrixFromArray((int[]) {
        23, 7, 7,
        21, 7, 7,
        19, 7, 7},
                                     3, 3);
    matrix m_test = createMatrixFromArray((int[]) {
        19, 7, 7,
        21, 7, 7,
        23, 7, 7},
                                          3, 3);
    Lab16_task2(&m);

    assert(areTwoMatricesEqual(&m, &m_test));

    freeMemMatrix(&m);
    freeMemMatrix(&m_test);
}
//номер 3 лаб 16 (a)
int getMin(int *a, int n) {

    int min = a[0];
    for (size_t i = 1; i < n; i++) {
        if(a[i] < min)
            min = a[i];
    }

    return min;
}
//номер 3 лаб 16 (b)
void sortColsByMinElement(matrix *m) {
    selectionSortColsMatrixByColCriteria(*m, getMin);
}

void Lab16_task3(matrix *m) {
    sortColsByMinElement(m);
}
//тест (с пособия)
void test_Lab16_task3() {
    matrix m = createMatrixFromArray((int[]) {
        3, 5, 2, 4, 3, 3,
        2, 5, 1, 8, 2, 7,
        6, 1, 4, 4, 8, 3},
                                     3, 6);
    matrix m_test = createMatrixFromArray((int[]) {
        5, 2, 3, 3, 3, 4,
        5, 1, 2, 2, 7, 8,
        1, 4, 6, 8, 3, 4},
                                          3, 6);
    Lab16_task3(&m);

    assert(areTwoMatricesEqual(&m, &m_test));

    freeMemMatrix(&m);
    freeMemMatrix(&m_test);
}

matrix mulMatrices(matrix m1, matrix m2) {

    if(m1.nRows * m1.nCols == m2.nRows * m2.nCols){
    matrix result = getMemMatrix(m1.nRows, m2.nCols);
    for (int i = 0; i < m1.nRows; i++) {
        for (int j = 0; j < m2.nCols; j++) {
            result.values[i][j] = 0;
            for (int k = 0; k < m1.nCols; k++) {
                result.values[i][j] += m1.values[i][k] * m2.values[k][j];
                }
            }
        }

        return result;
    }
}

void getSquareOfMatrixIfSymmetric(matrix *m) {
    if(isSymmetricMatrix(m)){
    matrix temp = mulMatrices(*m, *m);
    freeMemMatrix(m);
    *m = temp;
    }
}

void Lab16_task4(matrix *m) {
    getSquareOfMatrixIfSymmetric(m);
}
void test_Lab16_task4() {
    matrix m = createMatrixFromArray((int[]) {
        3, -2, 1,
        -2, 0, -4,
        1, -4, 2,},
                                     3, 3);
    matrix m_test = createMatrixFromArray((int[]) {
        14,      -10,     13,
        -10,     20,      -10,
        13,      -10,     21
                                          },
                                          3, 3);
    Lab16_task4(&m);
    assert(areTwoMatricesEqual(&m, &m_test));
    freeMemMatrix(&m);
    freeMemMatrix(&m_test);
}

int main() {
    //test_Lab16_task1();
    //test_Lab16_task2();
    //test_Lab16_task3();
    test_Lab16_task4();
}
/*int main() {
    int data[] = {3, -2, 1,
                  -2, 0, -4,
                  1, -4, 2,};


    matrix m = createMatrixFromArray(data, 3, 3);
    outputMatrix(m);

    Lab16_task4(&m);

    outputMatrix(m);
    freeMemMatrix(&m);

    return 0;
}*/
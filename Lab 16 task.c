#include "matrix.h"
#include "matrix.c"
#include <math.h>

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

bool isUnique(long long *a, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i] == a[j] && i != j)
                return false;
        }
    }
    return true;
}
//getSum из библиотеки
/*long long getSum(int *a, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum;
}*/

void transposeIfMatrixHasNotEqualSumOfRows(matrix *m) {
    long long temp_sum[m->nRows];
    for (int i = 0; i < m->nRows; i++) {
        temp_sum[i] = getSum(m->values[i], m->nCols);
    }

    if (isUnique(temp_sum, m->nRows))
        transposeSquareMatrix(m);
}

void Lab16_task5(matrix *m) {
    transposeIfMatrixHasNotEqualSumOfRows(m);
}
void test_Lab16_task5() {
    matrix m = createMatrixFromArray((int[]) {
        10,	9,	8,
        7,	6, 5,
        4,	3,	2},
                                     3, 3);
    matrix m_test = createMatrixFromArray((int[]) {
        10,	7,	4,
        9,	6,	3,
        8,	5,	2},
                                          3, 3);
    Lab16_task5(&m);

    assert(areTwoMatricesEqual(&m, &m_test));

    freeMemMatrix(&m);
    freeMemMatrix(&m_test);
}

bool isMutuallyInverseMatrices(matrix m1, matrix m2) {
    if (m1.nCols != m2.nCols || m1.nRows != m2.nRows)
        return false;
    else {
        matrix mul_m = mulMatrices(m1, m2);
        return isEMatrix(&mul_m);
    }
}

bool Lab16_task6(matrix m1, matrix m2) {
    return isMutuallyInverseMatrices(m1, m2);
}
void test_Lab16_task6() {
    int data1[] = {3,	4,
                  5,	7,};

    int data2[] = {7, -4,
                   -5,3};


    matrix m1 = createMatrixFromArray(data1, 2, 2);
    matrix m2 = createMatrixFromArray(data2, 2, 2);

    assert(Lab16_task6(m1, m2));

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

int max(int a, int b){
    return a > b ? a : b;
}

long long findSumOfMaxesOfPseudoDiagonal(matrix m) {
    long long max_sum_S = 0;
    int max_number = 0;
    for (int i = 1; i < m.nCols; i++) {
        int i_rows = 0;
        int i_cols = i;
        max_number = m.values[i_rows][i_cols];
        while (i_cols < m.nCols && i_rows < m.nRows) {
            max_number = max(max_number, m.values[i_rows] [i_cols]);
            i_rows++;
            i_cols++;
        }
        max_sum_S += max_number;
    }
    for (int i = 1; i < m.nRows; i++) {
        int i_row = i;
        int i_col = 0;
        max_number = m.values[i_row][i_col];
        while (i_col < m.nRows && i_row < m.nRows) {
            max_number = max(max_number, m.values[i_row][i_col]);
            i_row++;
            i_col++;
        }
        max_sum_S += max_number;
    }
    return max_sum_S;
}

long long Lab16_task7(matrix m) {
    return findSumOfMaxesOfPseudoDiagonal(m);
}

void test_Lab16_task7() {
//Пример из пособия
    matrix m = createMatrixFromArray((int[]) {
        3, 2, 5, 4,
        1, 3, 6, 3,
        3, 2, 1, 2},
                                     3, 4);
    assert(Lab16_task7(m) == 20);
    freeMemMatrix(&m);
}

int getMinInArea(matrix m) {
    position max_pos = getMaxValuePos(m);

    int min = m.values[max_pos.rowIndex][max_pos.colIndex];
    int row = max_pos.rowIndex - 1;
    int elementary_col;

    if(max_pos.colIndex - 1 >= 0) {
        elementary_col = max_pos.colIndex - 1;
    } else {
        elementary_col = 0;
    }

    int col = elementary_col;
    int col_final;

    if(max_pos.colIndex + 1 <= m.nCols - 1) {
        col_final = max_pos.colIndex + 1;
    } else {
        col_final = m.nCols - 1;
    }

    for (int i = row; i >= 0; i--) {
        for (int j = col; j <= col_final; j++)
            min = min < m.values[i][j] ? min : m.values[i][j];

        if(elementary_col - 1 >= 0) {
            elementary_col = elementary_col - 1;
        } else {
            elementary_col = 0;
        }

        col = elementary_col;

        if(col_final + 1 <= m.nCols - 1) {
            col_final = col_final + 1;
        } else {
            col_final = m.nCols - 1;
        }
    }

    return min;
}

int Lab16_task8(matrix m) {
    return getMinInArea(m);
}

void test_Lab16_task8() {
//Пример из пособия
    matrix m = createMatrixFromArray((int[]) {
        6, 8, 9, 2,
        7, 12, 3, 4,
        10, 11, 5, 1},
                                 3, 4);
    assert(Lab16_task8(m) == 6);
    freeMemMatrix(&m);
}

float getDistance(int *a, int n) {

    float dist = 0;
    for (int i = 0; i < n; i++) {
        dist += a[i] * a[i];
    }
    dist = sqrt(dist);
    return dist;
}

void insertionSortRowsMatrixByRowCriteriaF(matrix *m,
                                           float (*criteria)(int *, int)) {
    float temp[m->nRows];
    float mem_num;
    for (int i = 0; i < m->nRows; i++) {
        float res = criteria(m->values[i], m->nCols);
        temp[i] = res;
    }
    int min_id;
    for (int j = 0; j < m->nRows; j++) {
        min_id = j;
        for (int i = j + 1; i < m->nRows; i++) {
            if (temp[i] < temp[min_id]) {
                min_id = i;
            }
        }
        if (min_id != j) {
            mem_num = temp[j];
            temp[j] = temp[min_id];
            temp[min_id] = mem_num;
            swapRows(m, j, min_id);
        }
    }
}

void sortByDistances(matrix *m) {
    insertionSortRowsMatrixByRowCriteriaF(m, getDistance);
}


void Lab16_task9(matrix *m) {
    sortByDistances(m);
}
void test_Lab16_task9() {
    matrix m = createMatrixFromArray((int[]) {
        5, -20,
        10, -10,
        -8, -25},
                                     3, 2);
    matrix m_test = createMatrixFromArray((int[]) {
        10, -10,
        5, -20,
        -8, -25},
                                          3, 2);
    Lab16_task9(&m);

    assert(areTwoMatricesEqual(&m, &m_test));

    freeMemMatrix(&m);
    freeMemMatrix(&m_test);
}

int cmp_long_long(const void *pa, const void *pb) {

    if (*(long long int *) pa - *(long long int *) pb < 0)
        return -1;
    if (*(long long int *) pa - *(long long int *) pb > 0)
        return 1;
    return 0;
}

int countNUnique(long long *a, int n) {
    int count = 0;
    int is_unique = 0;
    for (int i = 0; i < n - 1; i++) {
        if (!is_unique && a[i] == a[i + 1]) {
            count += 1;
            is_unique = 1;
        } else
            is_unique = 0;
    }
    return count;
}
int countEqClassesByRowsSum(matrix m) {
    long long temp[m.nRows];
    for (int i = 0; i < m.nRows; i++) {
        temp[i] = getSum(m.values[i], m.nCols);
    }

    qsort(temp, m.nRows, sizeof(long long int), cmp_long_long);

    return countNUnique(temp, m.nRows);
}

int Lab16_task10(matrix m) {
    return countEqClassesByRowsSum(m);
}

void test_Lab16_task10() {
    matrix m = createMatrixFromArray((int[]) {7, 1,//8
                                              2, 7,//9
                                              5, 4,//9
                                              4, 3,//7
                                              1, 6,//7
                                              8, 0},//8
                                     6, 2);
//кол-во уникальных строк, с одинаковой суммой
    assert(Lab16_task10(m) == 3);
    freeMemMatrix(&m);
}


int main() {
    //test_Lab16_task1();
    //test_Lab16_task2();
    //test_Lab16_task3();
    //test_Lab16_task4();
    //test_Lab16_task5();
    //test_Lab16_task6();
    //test_Lab16_task7();
    //test_Lab16_task8();
    //test_Lab16_task9();
    test_Lab16_task10();
}

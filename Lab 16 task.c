#include "matrix.h"
#include "matrix.c"

/*Дана квадратная матрица, все элементы которой различны. Поменять местами
строки, в которых находятся максимальный и минимальный элементы */
void task1(matrix *m) {
    int min = getMinValuePos(*m).rowIndex;
    int max = getMaxValuePos(*m).rowIndex;
    swapRows(m, max, min);
}
void test_task1() {
    matrix m = createMatrixFromArray((int[]) {1, 1, 1,
                                              2, 2, 2,
                                              3, 3, 3},
                                     3, 3);
    matrix m_test = createMatrixFromArray((int[]) {3, 3, 3,
                                                   2, 2, 2,
                                                   1, 1, 1},
                                          3, 3);
    task1(&m);
    assert(areTwoMatricesEqual(&m, &m_test));
    freeMemMatrix(&m);
    freeMemMatrix(&m_test);
}


int main() {
    test_task1();
}

#include "matrix.h"
#include "matrix.c"

/*Дана квадратная матрица, все элементы которой различны. Поменять местами
строки, в которых находятся максимальный и минимальный элементы */
void Lab16_task1(matrix *m) {
    int min = getMinValuePos(*m).rowIndex;
    int max = getMaxValuePos(*m).rowIndex;
    swapRows(m, max, min);
}
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


int main() {
    test_Lab16_task1();
}

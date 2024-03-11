#include "matrix.h"

void swap(void *a, void *b) {
    void *tmp = a;
    a = b;
    b = tmp;
}

size_t getMaxElementIndexInArray(const int a[], size_t n) {

    int maxIndex = 0;

    for(size_t i = 1; i < n; i++){
        if(a[i] > a[maxIndex]){
            maxIndex = i;
        }
    }

    return maxIndex;
}

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
//освобождает память, выделенную под хранение матрицы m. (старая версия)
/*void freeMemMatrix(matrix *m) {
    for (size_t i = 0; i < m->nRows; i++)
        free(m->values [i]);

    free(m->values );

    m->values = NULL;
}*/
//освобождает память, выделенную под хранение матрицы m (новая)
void freeMemMatrix(matrix *m) {
    for (int i = 0; i < m->nRows; i++){
        for (int j = 0; j < m->nCols; j++){
            m->values[i] = NULL;
            m->values[j] = NULL;
        }
    }
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
void inputMatrices(matrix *ms, int nMatrices) {
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
/* выполняет сортировку вставками строк
матрицы m по неубыванию значения функции criteria применяемой для
строк. */
void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int*, int)) {
    int *values = malloc(sizeof(int) * m.nRows);

    for (size_t i = 0; i < m.nRows; i++)
        values[i] = criteria(m.values[i], m.nCols);

    for (size_t i = 1; i < m.nRows; i++) {

        int j = i - 1;

        while (values[i] < values[j] && j >= 0) {
            values[j + 1] = values[j];
            swapRows(m, j + 1, j);
            --j;
        }

        values[j + 1] = values[i];
    }
}
/*выполняет сортировку выбором столбцов
матрицы m по неубыванию значения функции criteria применяемой для столбцов
*/
void selectionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int*, int)) {
    int *values = malloc(sizeof(int) * m.nCols);

    for (size_t i = 0; i < m.nCols; i++) {
        int *col = malloc( sizeof(int) * m.nRows);

        for (size_t j = 0; j < m.nRows; j++)
            col[j] = m.values[j][i];

        values[i] = criteria(col, m.nRows);
    }

    for (int i = m.nCols - 1; i > 0; --i) {

        int max = getMaxElementIndexInArray(values, i + 1);

        if (max != i) {
            swap(values + max, values + i);

            for (size_t j = 0; j < m.nRows; j++)
                swap(&m.values[j] [max], &m.values[j][i]);
        }
    }
}
/*возвращает ’истина’, если матрица m
является квадратной, ложь – в противном случае */
bool isSquareMatrix(matrix *m) {
    return m->nRows == m->nCols;
}
//возвращает ’истина’, если матрицы m1 и m2 равны, иначе - ложь
bool areTwoMatricesEqual(matrix *m1, matrix *m2) {
    if (m1->nCols != m2->nCols || m1->nRows != m2->nRows)
        return 0;

    for (size_t i = 0; i < m1->nRows; i++)
        if (memcmp(m1->values[i], m2->values[i], sizeof(int) * m1->nCols))
            return 0;

    return 1;
}
//возвращает ’истина’, если матрица m является единичной, иначе - ложь
bool isEMatrix(matrix *m) {
//т.к Е матрица квадратная, то проверяем:
    if (!isSquareMatrix(m))
        return 0;

    for (size_t i = 0; i < m->nRows; i++) {
        if (m->values[i] [i] != 1)
            return 0;

        for (size_t j = 0; j < m->nCols; j++) {
            if (i != j && m->values[i] [j] != 0)
                return 0;
        }
    }

    return 1;
}
//возвращает ’истина’, если матрица m является симметричной, иначе - ложь
bool isSymmetricMatrix(matrix *m) {
    if (!isSquareMatrix(m))
        return 0;

    for (size_t i = 0; i < m->nRows; i++) {
        for ( size_t j = 0; j < m->nCols; j++) {
            if ( m->values[i] [j] != m->values[j] [i])
                return 0;
        }
    }

    return 1;
}
//транспонирует квадратную матрицу m
void transposeSquareMatrix(matrix *m) {
    if (!isSquareMatrix(m))
        return;

    for (size_t i = 0; i < m->nRows - 1; i++) {
        for (size_t j = i + 1; j < m->nRows; ++j ) {
            swap(&m->values[i] [j], &m->values[j] [i]);
        }
    }
}
//транспонирует матрицу m
void transposeMatrix(matrix *m) {
    matrix result = getMemMatrix(m->nCols, m->nRows);

    for (int col = 0; col < m->nCols; col++) {
        for (int row = 0, j = col; row < m->nRows; row++) {
            result.values[col] [row] = m->values[row] [j];
        }
    }

    memcpy(m, &result, sizeof(matrix));
}
//возвращает позицию минимального элемента матрицы m
position getMinValuePos(matrix m) {
    position pos;

    int min = INT_MAX;

    for (size_t i = 0; i < m.nRows; i++) {
        for (size_t j = 0; j < m.nCols; j++) {
            if (m.values[i] [j] < min) {
                min = m.values[i] [j];
                pos.rowIndex = i + 1;
                pos.colIndex = j + 1;
            }
        }
    }

    return pos;
}
//возвращает позицию максимального элемента матрицы m
position getMaxValuePos(matrix m) {
    position pos;

    int max = INT_MIN;

    for (size_t i = 0; i < m.nRows; i++) {
        for (size_t j = 0; j < m.nCols; j++) {
            if (m.values[i][j] > max) {
                max = m.values[i][j];
                pos.rowIndex = i + 1;
                pos.colIndex = j + 1;
            }
        }
    }

    return pos;
}
/*возвращает матрицу размера nRows на nCols, построенную из элементов массива a
 * функция из методички */
matrix createMatrixFromArray(const int *a, int nRows, int nCols) {
    matrix m = getMemMatrix(nRows, nCols);
    int k = 0;
    for (int i = 0; i < nRows; i++)
        for (int j = 0; j < nCols; j++)
            m.values[i][j] = a[k++];
    return m;
}
/*возвращает указатель на нулевую матрицу массива из nMatrices матриц, размещенных
в динамической памяти, построенных из элементов массива a.
Функция также из методички */
matrix *createArrayOfMatrixFromArray(const int *values,
                                     size_t nMatrices, size_t nRows, size_t nCols) {

    matrix *ms = getMemArrayOfMatrices(nMatrices, nRows, nCols);

    int l = 0;
    for (size_t k = 0; k < nMatrices; k++)
        for (size_t i = 0; i < nRows; i++)
            for (size_t j = 0; j < nCols; j++)
                ms[k].values[i][j] = values[l++];
    return ms;
}
//подсчет количества value значений
int countValues(const int *a, int n, int value) {
    int count = 0;
    for (size_t i = 0; i < n; i++) {
        if (a[i] == value) {
            ++count;
        }
    }

    return count;
}
//возвращает количество строк в которых все элементы равны 0.
int countZeroRows(matrix m) {
    int result = 0;
    for (size_t i = 0; i < m.nRows; i++) {
        int count = countValues(m.values[i], m.nCols, 0);
//Если количество найденных нулевых элементов = общему количеству столбцов в матрице, то увеличивается result
        if (count == m.nCols)
            ++result;
    }

    return result;
}
//Тест (с методички)
void test_countZeroRows() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    1, 1, 0,
                    0, 0, 0,
                    0, 0, 1,
                    0, 0, 0,
                    0, 1, 1,
            },
            5, 3
    );

    assert(countZeroRows(m) == 2);
    freeMemMatrix(&m);
}

int main() {
    //test_countZeroRows();
    matrix a = getMemMatrix(2,2);

    inputMatrix(&a);

    swapColumns(a,0,1);

    outputMatrix(a);

    freeMemMatrix(&a);
}
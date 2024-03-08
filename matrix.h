//
// Created by Александр on 06.03.2024.
//
#ifndef LAB15MATRIX_MATRIX_H
#define LAB15MATRIX_MATRIX_H
#include <stdio.h>
#include <malloc.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <memory.h>
typedef struct matrix {
    int **values; // элементы матрицы
    int nRows; // количество рядов
    int nCols; // количество столбцов
} matrix;

typedef struct position {
    int rowIndex;
    int colIndex;
} position;

#endif //LAB15MATRIX_MATRIX_H

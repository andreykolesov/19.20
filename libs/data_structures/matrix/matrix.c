#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <memory.h>

matrix getMemMatrix(int nRows, int nCols) {
    int **values = (int **) malloc(sizeof(int *) * nRows);

    for (int i = 0; i < nRows; i++)
        values[i] = (int *) malloc(sizeof(int) * nCols);
    return (matrix) {values, nRows, nCols};
}

matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols) {
    matrix *ms = (matrix *) malloc(sizeof(matrix) * nMatrices);

    for (int i = 0; i < nMatrices; i++)
        ms[i] = getMemMatrix(nRows, nCols);
    return ms;
}

void freeMemMatrix(matrix *m) {
    for (int i = 0; i < m->nRows; i++)
        free(m->values[i]);

    free(m->values);
}

void freeMemMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++)
        freeMemMatrix(&ms[i]);

    free(ms);
}

void inputMatrix(matrix *m) {
    for (int i = 0; i < m->nRows; i++)
        for (int j = 0; j < m->nCols; j++)
            scanf("%d", &(m->values[i][j]));
}

void inputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++)
        inputMatrix(&ms[i]);
}

void outputMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++)
            printf("%d", m.values[i][j]);

        printf("\n");
    }
}

void outputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        outputMatrix(ms[i]);

        printf("\n");
    }
}

void swapRows(matrix m, int i1, int i2) {
    assert (i1 >= 0 && i1 < m.nRows);
    assert (i2 >= 0 && i2 < m.nRows);

    int *temp = m.values[i1];
    m.values[i1] = m.values[i2];
    m.values[i2] = temp;
}

void swapColumns(matrix m, int j1, int j2) {
    assert (j1 >= 0 && j1 < m.nCols);
    assert (j2 >= 0 && j2 < m.nCols);

    for (int i = 0; i < m.nRows; i++) {
        int temp = m.values[i][j1];
        m.values[i][j1] = m.values[i][j2];
        m.values[i][j2] = temp;
    }
}

void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int *, int)) {
    for (int i = 1; i < m.nRows; i++) {
        int key = criteria(m.values[i], m.nCols);
        int j = i - 1;

        while (j >= 0 && criteria(m.values[j], m.nCols) > key) {
            swapRows(m, j, j + 1);
            j--;
        }
    }
}

void selectionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int *, int)) {
    int *col_values = (int *) malloc(sizeof(int) * m.nCols);

    for (int i = 0; i < m.nCols; i++) {
        int *cols = (int *) malloc(sizeof(int) * m.nRows);

        for (int j = 0; j < m.nRows; j++) {
            cols[j] = m.values[j][i];
        }

        col_values[i] = criteria(cols, m.nRows);
    }

    for (int i = 0; i < m.nCols - 1; i++) {
        int min_index = i;

        for (int j = i + 1; j < m.nCols; j++) {
            if (col_values[j] < col_values[min_index])
                min_index = j;
        }

        swapColumns(m, min_index, i);
        int temp = col_values[min_index];
        col_values[min_index] = col_values[i];
        col_values[i] = temp;
    }
}

bool isSquareMatrix(matrix *m) {
    return m->nRows == m->nCols;
}

bool areTwoMatricesEqual(matrix *m1, matrix *m2) {
    if (m1->nRows != m2->nRows || m1->nCols != m2->nCols)
        return false;

    for (int i = 0; i < m1->nRows; i++) {
        if (memcmp(m1->values[i], m2->values[i], sizeof(int) * m1->nCols) != 0)
            return false;
    }

    return true;
}

bool isEMatrix(matrix *m) {
    if (m->nRows != m->nCols)
        return false;

    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            if ((i == j && m->values[i][j] != 1) || (i != j && m->values[i][j] != 0))
                return false;
        }
    }

    return true;
}

bool isSymmetricMatrix(matrix *m) {
    if (m->nRows != m->nCols)
        return false;

    for (int i = 0; i < m->nRows; i++)
        for (int j = i + 1; j < m->nCols; j++)
            if (m->values[i][j] != m->values[j][i])
                return false;

    return true;
}

void transposeSquareMatrix(matrix *m) {
    for (int i = 0; i < m->nRows; i++) {
        for (int j = i + 1; j < m->nCols; j++) {
            int temp = m->values[i][j];
            m->values[i][j] = m->values[j][i];
            m->values[j][i] = temp;
        }
    }
}

void transposeMatrix(matrix *m) {
    matrix transposed = getMemMatrix(m->nCols, m->nRows);

    for (int i = 0; i < m->nRows; i++)
        for (int j = 0; j < m->nCols; j++)
            transposed.values[j][i] = m->values[i][j];

    freeMemMatrix(m);

    *m = transposed;
}

position getMinValuePos(matrix m) {
    int min_value = INT_MAX;
    position min_pos = {0, 0};

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] < min_value) {
                min_value = m.values[i][j];
                min_pos.rowIndex = i;
                min_pos.colIndex = j;
            }
        }
    }

    return min_pos;
}

position getMaxValuePos(matrix m) {
    int max_value = INT_MIN;
    position max_pos = {0, 0};

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] > max_value) {
                max_value = m.values[i][j];
                max_pos.rowIndex = i;
                max_pos.colIndex = j;
            }
        }
    }

    return max_pos;
}

matrix createMatrixFromArray(const int *a, int nRows, int nCols) {
    matrix m = getMemMatrix(nRows, nCols);
    int k = 0;

    for (int i = 0; i < nRows; i++)
        for (int j = 0; j < nCols; j++)
            m.values[i][j] = a[k++];

    return m;
}

matrix *createArrayOfMatrixFromArray(const int *values, size_t nMatrices, size_t nRows, size_t nCols) {
    matrix *ms = getMemArrayOfMatrices(nMatrices, nRows, nCols);
    int l = 0;

    for (size_t k = 0; k < nMatrices; k++)
        for (size_t i = 0; i < nRows; i++)
            for (size_t j = 0; j < nCols; j++)
                ms[k].values[i][j] = values[l++];

    return ms;
}


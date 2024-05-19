#ifndef UNTITLED11_FILL_MATRIX_H
#define UNTITLED11_FILL_MATRIX_H

#include <stdio.h>
#include <assert.h>
#include "../../data_structures/matrix/matrix.h"

typedef struct coord {
    int row_1;
    int col_1;
    int row_2;
    int col_2;
} coord;

void fillMatrix(const char *filename) {
    FILE *file = fopen(filename, "rb");

    int n;
    fread(&n, sizeof(int), 1, file);

    matrix m = getMemMatrix(n, n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            m.values[i][j] = 0;

    coord c;

    while (fread(&c, sizeof(coord), 1, file) == 1)
        for (int i = c.row_1; i <= c.row_2; i++)
            for (int j = c.col_1; j <= c.col_2; j++)
                m.values[i][j]++;

    fclose(file);

    file = fopen(filename, "wb");

    fwrite(&n, sizeof(int), 1, file);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fwrite(&m.values[i][j], sizeof(int), 1, file);

    freeMemMatrix(&m);
    fclose(file);
}

void test_fillMatrix_1_empty_file() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.20\\task_1_test_1";

    FILE* file = fopen(filename, "wb");

    int n = 0;

    fwrite(&n, sizeof(int), 1, file);

    fclose(file);

    fillMatrix(filename);

    file = fopen(filename, "rb");

    fread(&n, sizeof(int), 1, file);

    fclose(file);

    assert(n == 0);
}

void test_fillMatrix_2_unit_matrix() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.20\\task_1_test_2";

    FILE* file = fopen(filename, "wb");

    int n = 1;

    fwrite(&n, sizeof(int), 1, file);

    coord c = {.row_1=0, .col_1=0, .row_2=0, .col_2=0};

    fwrite(&c, sizeof(coord), 1, file);

    fclose(file);

    fillMatrix(filename);

    file = fopen(filename, "rb");

    fread(&n, sizeof(int), 1, file);

    int x;

    fread(&x, sizeof(int), 1, file);

    fclose(file);

    assert(n == 1);
    assert(x == 1);
}


void test_fillMatrix_3_more_matrix_element() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.20\\task_1_test_3";

    FILE* file = fopen(filename, "wb");

    int n = 3;

    fwrite(&n, sizeof(int), 1, file);

    coord c1 = {.row_1=1, .col_1=1, .row_2=2, .col_2=2};
    coord c2 = {.row_1=0, .col_1=0, .row_2=1, .col_2=1};

    fwrite(&c1, sizeof(coord), 1, file);
    fwrite(&c2, sizeof(coord), 1, file);

    fclose(file);

    fillMatrix(filename);

    file = fopen(filename, "rb");

    fread(&n, sizeof(int), 1, file);

    matrix m = getMemMatrix(n, n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fread(&m.values[i][j], sizeof(int), 1, file);

    matrix check = createMatrixFromArray((int[]) {1, 1, 0,
                                                     1, 2, 1,
                                                     0, 1, 1}, 3, 3);

    assert(n == 3);
    assert(areTwoMatricesEqual(&m, &check));

    freeMemMatrix(&m);
    freeMemMatrix(&check);
    fclose(file);
}


void test_fillMatrix() {
    test_fillMatrix_1_empty_file();
    test_fillMatrix_2_unit_matrix();
    test_fillMatrix_3_more_matrix_element();
}

#endif //UNTITLED11_FILL_MATRIX_H

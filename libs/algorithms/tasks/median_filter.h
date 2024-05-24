#ifndef UNTITLED11_MEDIAN_FILTER_H
#define UNTITLED11_MEDIAN_FILTER_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <malloc.h>

#include "../../data_structures/matrix/matrix.h"

int cmp(const void *a, const void *b) {
    return *(const unsigned int *) a - *(const unsigned int *) b;
}

int getMedianInArea(matrix *m, const int i, const int j, const int filter) {
    int border = filter * 2 + 1;

    int *temp = (int *) malloc((border * border) * sizeof(int));

    int size = 0;
    for (int row_i = i - filter; row_i <= i + filter; row_i++)
        for (int col_j = j - filter; col_j <= j + filter; col_j++)
            if (row_i != i || col_j != j) {
                temp[size] = m->values[row_i][col_j];
                size++;
            }

    qsort(temp, size, sizeof(int), cmp);

    int result = (temp[size / 2 - 1] + temp[size / 2]) / 2;

    free(temp);

    return result;
}

void medianFilter(const char *filename) {
    FILE *file = fopen(filename, "rb");

    int n, filter;
    fread(&n, sizeof(int), 1, file);
    fread(&filter, sizeof(int), 1, file);

    filter /= 2;

    matrix m = getMemMatrix(n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fread(&m.values[i][j], sizeof(int), 1, file);

    for (int i = filter; i < n - filter; i++)
        for (int j = filter; j < n - filter; j++)
            m.values[i][j] = getMedianInArea(&m, i, j, filter);

    fclose(file);

    file = fopen(filename, "wb");

    filter = filter * 2 + 1;

    fwrite(&n, sizeof(int), 1, file);
    fwrite(&filter, sizeof(int), 1, file);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fwrite(&m.values[i][j], sizeof(int), 1, file);

    freeMemMatrix(&m);

    fclose(file);
}

void test_medianFilter_1_empty_file() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.20\\task_3_test_1";

    FILE *file = fopen(filename, "wb");

    int n = 0;
    int filter = 7;
    fwrite(&n, sizeof(int), 1, file);
    fwrite(&filter, sizeof(int), 1, file);

    fclose(file);

    medianFilter(filename);

    file = fopen(filename, "rb");

    fread(&n, sizeof(int), 1, file);
    fread(&filter, sizeof(int), 1, file);

    fclose(file);

    assert(n == 0);
    assert(filter == 7);
}


void test_medianFilter_2_unit_file() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.20\\task_3_test_2";

    FILE *file = fopen(filename, "wb");

    int n = 1;
    int x = 10;
    int filter = 7;
    fwrite(&n, sizeof(int), 1, file);
    fwrite(&filter, sizeof(int), 1, file);
    fwrite(&x, sizeof(int), 1, file);

    fclose(file);

    medianFilter(filename);

    file = fopen(filename, "rb");

    fread(&n, sizeof(int), 1, file);
    fread(&filter, sizeof(int), 1, file);
    fread(&x, sizeof(int), 1, file);

    fclose(file);

    assert(n == 1);
    assert(filter == 7);
    assert(x == 10);
}


void test_medianFilter_3_small_matrix() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.20\\task_3_test_3";

    FILE *file = fopen(filename, "wb");

    int n = 3;
    int filter = 3;
    fwrite(&n, sizeof(int), 1, file);
    fwrite(&filter, sizeof(int), 1, file);

    matrix mat = createMatrixFromArray((int[]) {10, 20, 30,
                                                25, 35, 45,
                                                15, 25, 35}, n, n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fwrite(&mat.values[i][j], sizeof(int), 1, file);

    fclose(file);

    medianFilter(filename);

    file = fopen(filename, "rb");

    fread(&n, sizeof(int), 1, file);
    fread(&filter, sizeof(int), 1, file);

    matrix res = getMemMatrix(n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fread(&res.values[i][j], sizeof(int), 1, file);

    matrix check = createMatrixFromArray((int[]) {10, 20, 30,
                                                  25, 25, 45,
                                                  15, 25, 35}, n, n);

    fclose(file);

    assert(n == 3);
    assert(filter == 3);
    assert(areTwoMatricesEqual(&res, &check));

    freeMemMatrix(&mat);
    freeMemMatrix(&res);
    freeMemMatrix(&check);
}


void test_medianFilter_4_average_matrix() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.20\\task_3_test_4";

    FILE *file = fopen(filename, "wb");

    int n = 5;
    int filter = 5;
    fwrite(&n, sizeof(int), 1, file);
    fwrite(&filter, sizeof(int), 1, file);

    matrix mat = createMatrixFromArray((int[]) {10, 20, 30, 40, 50,
                                                15, 24, 16, 17, 56,
                                                34, 54, 12, 56, 78,
                                                14, 45, 34, 47, 56,
                                                17, 15, 24, 56, 62}, n, n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fwrite(&mat.values[i][j], sizeof(int), 1, file);

    fclose(file);

    medianFilter(filename);

    file = fopen(filename, "rb");

    fread(&n, sizeof(int), 1, file);
    fread(&filter, sizeof(int), 1, file);

    matrix res = getMemMatrix(n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fread(&res.values[i][j], sizeof(int), 1, file);

    matrix check = createMatrixFromArray((int[]) {10, 20, 30, 40, 50,
                                                  15, 24, 16, 17, 56,
                                                  34, 54, 34, 56, 78,
                                                  14, 45, 34, 47, 56,
                                                  17, 15, 24, 56, 62}, n, n);

    fclose(file);

    assert(n == 5);
    assert(filter == 5);
    assert(areTwoMatricesEqual(&res, &check));

    freeMemMatrix(&mat);
    freeMemMatrix(&res);
    freeMemMatrix(&check);
}


void test_medianFilter_5_big_matrix() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.20\\task_3_test_5";

    FILE *file = fopen(filename, "wb");

    int n = 7;
    int filter = 7;
    fwrite(&n, sizeof(int), 1, file);
    fwrite(&filter, sizeof(int), 1, file);

    matrix mat = createMatrixFromArray((int[]) {10, 20, 30, 40, 50, 60, 70,
                                                15, 24, 36, 47, 56, 62, 68,
                                                12, 18, 34, 44, 52, 66, 78,
                                                14, 25, 34, 47, 56, 69, 69,
                                                17, 19, 34, 46, 56, 59, 67,
                                                13, 25, 34, 47, 56, 69, 69,
                                                16, 23, 31, 42, 59, 69, 73}, n, n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fwrite(&mat.values[i][j], sizeof(int), 1, file);

    fclose(file);

    medianFilter(filename);

    file = fopen(filename, "rb");

    fread(&n, sizeof(int), 1, file);
    fread(&filter, sizeof(int), 1, file);

    matrix res = getMemMatrix(n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fread(&res.values[i][j], sizeof(int), 1, file);

    matrix check = createMatrixFromArray((int[]) {10, 20, 30, 40, 50, 60, 70,
                                                  15, 24, 36, 47, 56, 62, 68,
                                                  12, 18, 34, 44, 52, 66, 78,
                                                  14, 25, 34, 45, 56, 69, 69,
                                                  17, 19, 34, 46, 56, 59, 67,
                                                  13, 25, 34, 47, 56, 69, 69,
                                                  16, 23, 31, 42, 59, 69, 73}, n, n);

    fclose(file);

    assert(n == 7);
    assert(filter == 7);
    assert(areTwoMatricesEqual(&res, &check));

    freeMemMatrix(&mat);
    freeMemMatrix(&res);
    freeMemMatrix(&check);
}


void test_medianFilter() {
    test_medianFilter_1_empty_file();
    test_medianFilter_2_unit_file();
    test_medianFilter_3_small_matrix();
    test_medianFilter_4_average_matrix();
    test_medianFilter_5_big_matrix();
}

#endif //UNTITLED11_MEDIAN_FILTER_H

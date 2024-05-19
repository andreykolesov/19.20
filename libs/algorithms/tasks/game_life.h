#ifndef UNTITLED11_GAME_LIFE_H
#define UNTITLED11_GAME_LIFE_H

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "../../data_structures/matrix/matrix.h"

int is_point_alive(matrix *m, int i, int j) {
    bool is_alive = m->values[i][j];

    int left_i = i > 0 ? i - 1 : i;
    int right_i = i < m->nRows - 1 ? i + 1 : i;
    int left_j = j > 0 ? j - 1 : j;
    int right_j = j < m->nCols - 1 ? j + 1 : j;

    int amount_units = 0;

    for (int row_i = left_i; row_i <= right_i; row_i++)
        for (int col_j = left_j; col_j <= right_j; col_j++)
            if (m->values[row_i][col_j] && (row_i != i || col_j != j))
                amount_units++;

    if (is_alive && (amount_units < 2))
        return 0;

    if (is_alive && (amount_units == 2 || amount_units == 3))
        return 1;

    if (is_alive && amount_units > 3)
        return 0;

    if (!is_alive && amount_units == 3)
        return 1;

    return 0;
}

void gameLife(const char *filename) {
    FILE *file = fopen(filename, "rb");
    int r, c;

    fread(&r, sizeof(int), 1, file);
    fread(&c, sizeof(int), 1, file);

    matrix mat = getMemMatrix(r, c);

    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            fread(&mat.values[i][j], sizeof(int), 1, file);

    matrix res_matrix = getMemMatrix(r, c);

    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            res_matrix.values[i][j] = is_point_alive(&mat, i, j);

    fclose(file);

    file = fopen(filename, "wb");

    fwrite(&r, sizeof(int), 1, file);
    fwrite(&c, sizeof(int), 1, file);

    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            fwrite(&res_matrix.values[i][j], sizeof(int), 1, file);

    freeMemMatrix(&mat);
    freeMemMatrix(&res_matrix);

    fclose(file);
}

void test_game_life_1_empty_file() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.20\\task_2_test_1";

    FILE *file = fopen(filename, "wb");

    int n = 0;
    int m = 0;

    fwrite(&n, sizeof(int), 1, file);
    fwrite(&m, sizeof(int), 1, file);

    fclose(file);

    gameLife(filename);

    file = fopen(filename, "rb");

    fread(&n, sizeof(int), 1, file);
    fread(&m, sizeof(int), 1, file);

    assert(n == 0);
    assert(m == 0);

    fclose(file);
}

void test_game_life_2_unit_file() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.20\\task_2_test_2";

    FILE *file = fopen(filename, "wb");

    int n = 1;
    int m = 1;
    int x = 0;

    fwrite(&n, sizeof(int), 1, file);
    fwrite(&m, sizeof(int), 1, file);
    fwrite(&x, sizeof(int), 1, file);

    fclose(file);

    gameLife(filename);

    file = fopen(filename, "rb");

    fread(&n, sizeof(int), 1, file);
    fread(&m, sizeof(int), 1, file);
    fread(&x, sizeof(int), 1, file);

    assert(n == 1);
    assert(m == 1);
    assert(x == 0);

    fclose(file);
}

void test_game_life_3_more_elements() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.20\\task_2_test_3";

    FILE *file = fopen(filename, "wb");

    int n = 4;
    int m = 3;

    fwrite(&n, sizeof(int), 1, file);
    fwrite(&m, sizeof(int), 1, file);

    matrix mat = createMatrixFromArray((int[]) {0, 1, 0,
                                                0, 0, 1,
                                                1, 1, 1,
                                                0, 0, 0}, n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            fwrite(&mat.values[i][j], sizeof(int), 1, file);

    fclose(file);

    gameLife(filename);

    file = fopen(filename, "rb");

    fread(&n, sizeof(int), 1, file);
    fread(&m, sizeof(int), 1, file);

    matrix res = getMemMatrix(n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            fread(&res.values[i][j], sizeof(int), 1, file);

    matrix check = createMatrixFromArray((int[]) {0, 0, 0,
                                                  1, 0, 1,
                                                  0, 1, 1,
                                                  0, 1, 0}, n, m);

    assert(n == 4);
    assert(m == 3);
    assert(areTwoMatricesEqual(&res, &check));

    freeMemMatrix(&mat);
    freeMemMatrix(&res);
    freeMemMatrix(&check);

    fclose(file);
}

void test_gameLife() {
    test_game_life_1_empty_file();
    test_game_life_2_unit_file();
    test_game_life_3_more_elements();
}

#endif //UNTITLED11_GAME_LIFE_H

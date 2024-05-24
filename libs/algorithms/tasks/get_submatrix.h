#ifndef UNTITLED11_GET_SUBMATRIX_H
#define UNTITLED11_GET_SUBMATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../../data_structures/matrix/matrix.h"

#define MAX 100

int min(int x, int y) {
    return (x < y) ? x : y;
}

int getSubmatrix(matrix mat) {
    int nums[MAX][MAX];
    int res = 0;

    for (int i = 0; i < mat.nRows; i++) {
        for (int j = 0; j < mat.nCols; j++) {
            if (mat.values[i][j] == 0) {
                nums[i][j] = 0;
            } else {
                nums[i][j] = (j == 0) ? 1 : nums[i][j - 1] + 1;
                int min_val = nums[i][j];

                for (int k = i; k >= 0; k--) {
                    min_val = min(min_val, nums[k][j]);
                    res += min_val;
                }
            }
        }
    }

    return res;
}

void test_getSubmatrix_1_empty_matrix() {
    matrix m = createMatrixFromArray((int[]) {}, 0, 0);

    int result = getSubmatrix(m);

    freeMemMatrix(&m);

    assert(result == 0);
}

void test_getSubmatrix_2_unit_matrix() {
    matrix m = createMatrixFromArray((int[]) {1}, 1, 1);

    int result = getSubmatrix(m);

    freeMemMatrix(&m);

    assert(result == 1);
}

void test_getSubmatrix_3_more_element() {
    matrix m = createMatrixFromArray((int[]) {1, 0, 1,
                                              1, 1, 0,
                                              1, 1, 0}, 3, 3);

    int result = getSubmatrix(m);

    freeMemMatrix(&m);

    assert(result == 13);
}

void test_getSubmatrix() {
    test_getSubmatrix_1_empty_matrix();
    test_getSubmatrix_2_unit_matrix();
    test_getSubmatrix_3_more_element();
}

#endif //UNTITLED11_GET_SUBMATRIX_H

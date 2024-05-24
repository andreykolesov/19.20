#ifndef UNTITLED11_GET_BINARY_TREE_H
#define UNTITLED11_GET_BINARY_TREE_H

#include <stdio.h>
#include <assert.h>

#include "../../data_structures/vector/vector.h"

void print_vector(vector *v) {
    for (int i = 0; i < v->size; i++)
        printf("%d ", getVectorValue(v, i));
    printf("\n");
}

int get_max_vector(vector *v) {
    if (v->size == 0)
        return (int) -1e4;

    int max = getVectorValue(v, 0);
    for (int i = 1; i < v->size; i++) {
        int x = getVectorValue(v, i);
        if (max < x)
            max = x;
    }

    return max;
}

int get_index_vector(vector *v, int x) {
    int i = -1;
    for (int j = 0; j < v->size; j++)
        if (getVectorValue(v, j) == x)
            i = j;
    return i;
}

void getBinaryTree(vector *nums, vector *result) {
    if (nums->size == 0) {
        pushBack(result, -1);
        return;
    } else if (nums->size == 1) {
        int x = getVectorValue(nums, 0);
        pushBack(result, x);
        return;
    }

    int max = get_max_vector(nums);
    int index = get_index_vector(nums, max);
    pushBack(result, max);

    vector left = createVector(index + 1);
    for (int i = 0; i < index; i++)
        pushBack(&left, getVectorValue(nums, i));

    vector right = createVector(nums->size - index + 1);
    for (int i = index + 1; i < nums->size; i++)
        pushBack(&right, getVectorValue(nums, i));

    getBinaryTree(&left, result);
    getBinaryTree(&right, result);

    deleteVector(&left);
    deleteVector(&right);
}


vector generateTree(vector *v) {
    vector result = createVector(32);
    getBinaryTree(v, &result);

    return result;
}

void test_generateTree_1_empty_file() {
    vector v = createVector(12);
    v = generateTree(&v);

    assert(getVectorValue(&v, 0) == -1);

    deleteVector(&v);
}


void test_generateTree_2_one_element() {
    vector v = createVector(12);
    pushBack(&v, 3);

    v = generateTree(&v);

    assert(getVectorValue(&v, 0) == 3);

    deleteVector(&v);
}


void test_generateTree_3_sorted_element_up() {
    vector v = createVector(12);
    pushBack(&v, 3);
    pushBack(&v, 4);
    pushBack(&v, 5);

    v = generateTree(&v);

    assert(getVectorValue(&v, 0) == 5);
    assert(getVectorValue(&v, 1) == 4);
    assert(getVectorValue(&v, 2) == 3);
    assert(getVectorValue(&v, 3) == -1);
    assert(getVectorValue(&v, 4) == -1);

    deleteVector(&v);
}


void test_generateTree_4_sorted_element_down() {
    vector v = createVector(12);
    pushBack(&v, 5);
    pushBack(&v, 4);
    pushBack(&v, 3);

    v = generateTree(&v);

    assert(getVectorValue(&v, 0) == 5);
    assert(getVectorValue(&v, 1) == -1);
    assert(getVectorValue(&v, 2) == 4);
    assert(getVectorValue(&v, 3) == -1);
    assert(getVectorValue(&v, 4) == 3);

    deleteVector(&v);
}


void test_generateTree_5_random_element() {
    vector v = createVector(12);
    pushBack(&v, 3);
    pushBack(&v, 2);
    pushBack(&v, 1);
    pushBack(&v, 6);
    pushBack(&v, 0);
    pushBack(&v, 5);

    v = generateTree(&v);

    assert(getVectorValue(&v, 0) == 6);
    assert(getVectorValue(&v, 1) == 3);
    assert(getVectorValue(&v, 2) == -1);
    assert(getVectorValue(&v, 3) == 2);
    assert(getVectorValue(&v, 4) == -1);
    assert(getVectorValue(&v, 5) == 1);
    assert(getVectorValue(&v, 6) == 5);
    assert(getVectorValue(&v, 7) == 0);
    assert(getVectorValue(&v, 8) == -1);

    deleteVector(&v);
}


void test_generateTree() {
    test_generateTree_1_empty_file();
    test_generateTree_2_one_element();
    test_generateTree_3_sorted_element_up();
    test_generateTree_4_sorted_element_down();
    test_generateTree_5_random_element();
}

#endif //UNTITLED11_GET_BINARY_TREE_H

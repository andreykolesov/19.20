#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include "array.h"


void inputArray_(int a[], const size_t n) {
    for (size_t i = 0; i < n; i++)
        scanf("%d", a + i);
}


void outputArray_(const int a[], const size_t n) {
    for (size_t i = 0; i < n; i++)
        printf("%d ", *(a + i));
    printf("\n");
}


size_t linearSearch_(const int a[], const size_t n, int x) {
    for (size_t i = 0; i < n; i++)
        if (a[i] == x)
            return i;
    return n;
}


size_t binarySearch_(const int a[], const size_t n, int x) {
    if (a[0] > x || n == 0)
        return n;

    size_t left = 0;
    size_t right = n - 1;

    while (left <= right) {
        size_t middle = left + (right - left) / 2;

        if (a[middle] < x)
            left = middle + 1;
        else if (a[middle] > x)
            right = middle - 1;
        else
            return middle;
    }

    return n;
}


size_t binarySearchMoreOrEqual_(const int a[], const size_t n, int x) {
    if (a[0] >= x)
        return 0;

    size_t left = 0;
    size_t right = n;

    while (right - left > 1) {
        size_t middle = left + (right - left) / 2;

        if (a[middle] < x)
            left = middle;
        else
            right = middle;
    }

    return right;
}


void insert_(int a[], size_t *n, size_t pos, int value) {
    assert(pos < *n);

    if (*n != 0) {
        size_t low_bound = (pos == 0) ? SIZE_MAX : pos;
        (*n)++;

        for (size_t i = *n; i != low_bound; i--)
            a[i] = a[i - 1];

        a[pos] = value;
    } else {
        (*n)++;
        a[pos] = value;
    }
}


void append_(int a[], size_t *n, int value) {
    a[*n] = value;
    (*n)++;
}


void deleteByPosSaveOrder_(int a[], size_t *n, size_t pos) {
    for (size_t i = pos; i < *n; i++)
        a[i] = a[i + 1];
    (*n)--;
}


void deleteByPosUnsaveOrder_(int a[], size_t *n, size_t pos) {
    a[pos] = a[*n - 1];
    (*n)--;
}


int all_(const int a[], size_t n, int (*predicate)(int)) {
    for (size_t i = 0; i < n; i++)
        if (!predicate(a[i]))
            return 0;
    return 1;
}


int any_(const int a[], size_t n, int (*predicate)(int)) {
    for (size_t i = 0; i < n; i++)
        if (predicate(a[i]))
            return 1;
    return 0;
}


void forEach_(const int source[], int dest[], size_t n, int(*predicate)(int)) {
    for (size_t i = 0; i < n; i++)
        dest[i] = predicate(source[i]);
}


int countIf_(const int a[], size_t n, int(*predicate)(int)) {
    int res = 0;

    for (size_t i = 0; i < n; i++)
        if (predicate(a[i]))
            res++;

    return res;
}


void deleteIf_(int a[], size_t *n, int(*deletePredicate)(int)) {
    size_t i_read = 0;
    while (i_read < *n && !deletePredicate(a[i_read]))
        i_read++;

    size_t i_write = i_read;
    while (i_read < *n) {
        if (!deletePredicate(a[i_read])) {
            a[i_write] = a[i_read];
            i_write++;
        }

        i_read++;
    }

    (*n) = i_write;
}

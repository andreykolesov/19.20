#include <stdio.h>
#include "vector.h"
#include <stdlib.h>

vector createVector(size_t n) {
    vector v;

    v.data = malloc(sizeof(int) * n);
    v.size = 0;
    v.capacity = n;

    if (v.data == NULL) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }

    return v;
}

void reserve(vector *v, size_t newCapacity) {
    if (newCapacity == 0) {
        deleteVector(v);
    } else {
        int *new_data = realloc(v->data, newCapacity * sizeof(int));

        if (new_data == NULL) {
            fprintf(stderr, "bad alloc");
            exit(1);
        }

        v->data = new_data;
        v->capacity = newCapacity;

        if (v->size > newCapacity) {
            v->size = newCapacity;
        }
    }
}

void clear(vector *v) {
    v->size = 0;
}

void shrinkToFit(vector *v) {
    reserve(v, v->size);
}

void deleteVector(vector *v) {
    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}

bool isEmpty(vector *v) {
    return v->size == 0;
}

bool isFull(vector *v) {
    return v->size == v->capacity;
}

int getVectorValue(vector *v, size_t i) {
    return v->data[i];
}

void pushBack(vector *v, int x) {
    if (isFull(v)) {
        size_t new_capacity;

        if (v->capacity == 0)
            new_capacity = 1;
        else
            new_capacity = v->capacity * 2;

        reserve(v, new_capacity);
    }

    v->data[v->size] = x;
    v->size++;
}

void popBack(vector *v) {
    if (isEmpty(v)) {
        fprintf(stderr, "vector is empty");
        exit(1);
    }

    v->size--;
}

int *atVector(vector *v, size_t index) {
    if (index >= v->capacity) {
        fprintf(stderr, "IndexError: a[%lld] is not exists", index);
        exit(1);
    }

    return &v->data[index];
}

int *back(vector *v) {
    if (isEmpty(v)) {
        fprintf(stderr, "vector is empty");
        exit(1);
    }

    return &v->data[v->size - 1];
}

int *front(vector *v) {
    if (isEmpty(v)) {
        fprintf(stderr, "vector is empty");
        exit(1);
    }

    return &v->data[0];
}
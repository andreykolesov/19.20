#include <stdio.h>
#include "vectorVoid.h"
#include <stdlib.h>
#include <memory.h>

vectorVoid createVectorV(size_t n, size_t baseTypeSize) {
    vectorVoid v;

    v.data = malloc(baseTypeSize * n);
    v.size = 0;
    v.capacity = n;
    v.baseTypeSize = baseTypeSize;

    if (v.data == NULL) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }

    return v;
}

void reserveV(vectorVoid *v, size_t newCapacity) {
    if (newCapacity == 0) {
        deleteVectorV(v);
    } else {
        int *new_data = realloc(v->data, newCapacity * v->baseTypeSize);

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

void clearV(vectorVoid *v) {
    v->size = 0;
}

void shrinkToFitV(vectorVoid *v) {
    reserveV(v, v->size);
}

void deleteVectorV(vectorVoid *v) {
    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
    v->baseTypeSize = 0;
}

bool isEmptyV(vectorVoid *v) {
    return v->size == 0;
}

bool isFullV(vectorVoid *v) {
    return v->size == v->capacity;
}

void getVectorValueV(vectorVoid *v, size_t index, void *destination) {
    char *source = (char *) v->data + index * v->baseTypeSize;
    memcpy(destination, source, v->baseTypeSize);
}

void setVectorValueV(vectorVoid *v, size_t index, void *source) {
    if (index >= v->capacity) {
        fprintf(stderr, "IndexError: a[%lld] is not exists", index);
        exit(1);
    }

    char *address = (char *) v->data + index * v->baseTypeSize;
    memcpy(address, source, v->baseTypeSize);
}

void popBackV(vectorVoid *v) {
    if (isEmptyV(v)) {
        fprintf(stderr, "vector is empty");
        exit(1);
    }

    v->size--;
}

void pushBackV(vectorVoid *v, int *source) {
    if (isFullV(v)) {
        size_t new_capacity;

        if (v->capacity == 0)
            new_capacity = 1;
        else
            new_capacity = v->capacity * 2;

        reserveV(v, new_capacity);
    }

    setVectorValueV(v, v->size, source);
    v->size++;
}
#include <assert.h>
#include <stdlib.h>

#include "unordered_array_set.h"

unordered_array_set unordered_array_set_create(size_t capacity) {
    return (unordered_array_set) {
            malloc(sizeof(int) * capacity),
            0,
            capacity
    };
}

unordered_array_set unordered_array_set_create_from_array(const int *a, size_t size) {
    unordered_array_set set = unordered_array_set_create(size);
    for (size_t i = 0; i < size; i++)
        unordered_array_set_insert(&set, a[i]);

    return set;
}

bool unordered_array_set_isAbleAppend(unordered_array_set *set) {
    return (set->size < set->capacity);
}

void unordered_array_set_insert(unordered_array_set *set, int value) {
    if (unordered_array_set_in(set, value) == set->size) {
        unordered_array_set_isAbleAppend(set);
        append_(set->data, &set->size, value);
    }
}

size_t unordered_array_set_in(unordered_array_set *set, int value) {
    return linearSearch_(set->data, set->size, value);
}

bool unordered_array_set_isEqual(unordered_array_set set1, unordered_array_set set2) {
    return unordered_array_set_isSubset(set1, set2) && unordered_array_set_isSubset(set2, set1);
}

bool unordered_array_set_isSubset(unordered_array_set subset, unordered_array_set set) {
    if (subset.size > set.size)
        return false;

    for (int i = 0; i < subset.size; i++) {
        if (unordered_array_set_in(&set, subset.data[i]) == set.size) {
            return false;
        }
    }

    return true;
}

void unordered_array_set_deleteElement(unordered_array_set *set, int value) {
    size_t pos = unordered_array_set_in(set, value);

    if (pos != set->size)
        deleteByPosSaveOrder_(set->data, &set->size, pos);
}

unordered_array_set unordered_array_set_union(unordered_array_set set1, unordered_array_set set2) {
    size_t new_capacity = set1.size + set2.size;
    unordered_array_set set = unordered_array_set_create(new_capacity);

    for (int i = 0; i < set1.size; i++)
        unordered_array_set_insert(&set, set1.data[i]);

    for (int i = 0; i < set2.size; i++)
        if (unordered_array_set_in(&set, set2.data[i]) == set.size)
            unordered_array_set_insert(&set, set2.data[i]);

    return set;
}

unordered_array_set unordered_array_set_intersection(unordered_array_set set1, unordered_array_set set2) {
    size_t new_capacity = set1.size;
    unordered_array_set set = unordered_array_set_create(new_capacity);

    for (int i = 0; i < set2.size; i++)
        if (unordered_array_set_in(&set1, set2.data[i]) != set1.size)
            unordered_array_set_insert(&set, set2.data[i]);

    return set;
}

unordered_array_set unordered_array_set_difference(unordered_array_set set1, unordered_array_set set2) {
    size_t new_capacity = set1.size;
    unordered_array_set set = unordered_array_set_create(new_capacity);

    for (int i = 0; i < set1.size; i++)
        if (unordered_array_set_in(&set2, set1.data[i]) == set2.size)
            unordered_array_set_insert(&set, set1.data[i]);

    return set;
}

unordered_array_set unordered_array_set_complement(unordered_array_set set, unordered_array_set universumSet) {
    assert(unordered_array_set_isSubset(set, universumSet));

    size_t new_capacity = universumSet.size;
    unordered_array_set result = unordered_array_set_create(new_capacity);

    for (int i = 0; i < universumSet.size; i++)
        unordered_array_set_insert(&result, universumSet.data[i]);

    for (int i = 0; i < set.size; i++)
        unordered_array_set_deleteElement(&result, set.data[i]);

    return result;
}

unordered_array_set unordered_array_set_symmetricDifference(unordered_array_set set1, unordered_array_set set2) {
    unordered_array_set result1 = unordered_array_set_create(set1.size);
    unordered_array_set result2 = unordered_array_set_create(set2.size);

    for (int i = 0; i < set1.size; i++)
        if (unordered_array_set_in(&set2, set1.data[i]) == set2.size)
            unordered_array_set_insert(&result1, set1.data[i]);

    for (int i = 0; i < set2.size; i++)
        if (unordered_array_set_in(&set1, set2.data[i]) == set1.size)
            unordered_array_set_insert(&result2, set2.data[i]);

    unordered_array_set all_result = unordered_array_set_union(result1, result2);
    unordered_array_set_delete(&result1);
    unordered_array_set_delete(&result2);

    return all_result;
}

void unordered_array_set_delete(unordered_array_set *set) {
    free(set->data);
    set->data = NULL;
    set->size = 0;
    set->capacity = 0;
}

void unordered_array_set_print(unordered_array_set set) {
    printf("{ ");
    for (size_t i = 0; i < set.size; i++) {
        printf("%d ", set.data[i]);
    }
    printf("}\n");
}
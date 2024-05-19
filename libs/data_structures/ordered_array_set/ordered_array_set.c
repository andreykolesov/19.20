#include <assert.h>
#include <stdlib.h>

#include "ordered_array_set.h"

ordered_array_set ordered_array_set_create(size_t capacity) {
    return (ordered_array_set) {
            malloc(sizeof(int) * capacity),
            0,
            capacity
    };
}

ordered_array_set ordered_array_set_create_from_array(const int *a, size_t size) {
    ordered_array_set set = ordered_array_set_create(size);
    for (size_t i = 0; i < size; i++)
        ordered_array_set_insert(&set, a[i]);
    return set;
}

size_t ordered_array_set_in(ordered_array_set *set, int value) {
    return binarySearch_(set->data, set->size, value);
}

bool ordered_array_set_isEqual(ordered_array_set set1, ordered_array_set set2) {
    if (set1.size != set2.size)
        return false;

    return (memcmp(set1.data, set2.data, set1.size * sizeof(int))) == 0;
}

bool ordered_array_set_isSubset(ordered_array_set subset, ordered_array_set set) {
    if (subset.size > set.size)
        return false;

    for (int i = 0; i < subset.size; i++) {
        if (ordered_array_set_in(&set, subset.data[i]) == set.size) {
            return false;
        }
    }

    return true;
}

bool ordered_array_set_isAbleAppend(ordered_array_set *set) {
    return (set->size < set->capacity);
}

void ordered_array_set_insert(ordered_array_set *set, int value) {
    if (ordered_array_set_in(set, value) == set->size) {
        ordered_array_set_isAbleAppend(set);
        append_(set->data, &set->size, value);
    }
}

void ordered_array_set_deleteElement(ordered_array_set *set, int value) {
    size_t pos = ordered_array_set_in(set, value);

    if (pos != set->size)
        deleteByPosSaveOrder_(set->data, &set->size, pos);
}

ordered_array_set ordered_array_set_union(ordered_array_set set1, ordered_array_set set2) {
    size_t new_capacity = set1.size + set2.size;
    ordered_array_set set = ordered_array_set_create(new_capacity);

    size_t i = 0, j = 0;

    while (i < set1.size && j < set2.size) {
        if (set1.data[i] < set2.data[j]) {
            ordered_array_set_insert(&set, set1.data[i++]);
        } else if (set1.data[i] > set2.data[j]) {
            ordered_array_set_insert(&set, set2.data[j++]);
        } else {
            ordered_array_set_insert(&set, set1.data[i++]);
            j++;
        }
    }

    while (i < set1.size) {
        ordered_array_set_insert(&set, set1.data[i++]);
    }

    while (j < set2.size) {
        ordered_array_set_insert(&set, set2.data[j++]);
    }

    return set;
}

ordered_array_set ordered_array_set_intersection(ordered_array_set set1, ordered_array_set set2) {
    size_t new_capacity = set1.size;
    ordered_array_set set = ordered_array_set_create(new_capacity);

    for (int i = 0; i < set2.size; i++)
        if (ordered_array_set_in(&set1, set2.data[i]) != set1.size)
            ordered_array_set_insert(&set, set2.data[i]);

    return set;
}

ordered_array_set ordered_array_set_difference(ordered_array_set set1, ordered_array_set set2) {
    size_t new_capacity = set1.size;
    ordered_array_set set = ordered_array_set_create(new_capacity);

    for (int i = 0; i < set1.size; i++)
        if (ordered_array_set_in(&set2, set1.data[i]) == set2.size)
            ordered_array_set_insert(&set, set1.data[i]);

    return set;
}

ordered_array_set ordered_array_set_symmetricDifference(ordered_array_set set1, ordered_array_set set2) {
    ordered_array_set result1 = ordered_array_set_create(set1.size);
    ordered_array_set result2 = ordered_array_set_create(set2.size);

    for (int i = 0; i < set1.size; i++)
        if (ordered_array_set_in(&set2, set1.data[i]) == set2.size)
            ordered_array_set_insert(&result1, set1.data[i]);

    for (int i = 0; i < set2.size; i++)
        if (ordered_array_set_in(&set1, set2.data[i]) == set1.size)
            ordered_array_set_insert(&result2, set2.data[i]);

    ordered_array_set all_result = ordered_array_set_union(result1, result2);
    ordered_array_set_delete(&result1);
    ordered_array_set_delete(&result2);

    return all_result;
}

ordered_array_set ordered_array_set_complement(ordered_array_set set, ordered_array_set universumSet) {
    assert(ordered_array_set_isSubset(set, universumSet));

    size_t new_capacity = universumSet.size;
    ordered_array_set result = ordered_array_set_create(new_capacity);

    for (int i = 0; i < universumSet.size; i++)
        ordered_array_set_insert(&result, universumSet.data[i]);

    for (int i = 0; i < set.size; i++)
        ordered_array_set_deleteElement(&result, set.data[i]);

    return result;
}

void ordered_array_set_delete(ordered_array_set *set) {
    free(set->data);
    set->data = NULL;
    set->size = 0;
    set->capacity = 0;
}

void ordered_array_set_print(ordered_array_set set) {
    printf("{ ");
    for (size_t i = 0; i < set.size; i++) {
        printf("%d ", set.data[i]);
    }

    printf("}\n");
}
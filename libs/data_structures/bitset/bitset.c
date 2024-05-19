#include <stdio.h>
#include <assert.h>

#include "bitset.h"

bitset bitset_create(unsigned maxValue) {
    assert (maxValue < 32);
    return (bitset) {0, maxValue};
}

bitset bitset_create_from_array(const unsigned int a[], size_t size, unsigned max_value) {
    assert(size < 32);
    bitset set = bitset_create(max_value);

    for (size_t i = 0; i < size; i++)
        bitset_insert(&set, a[i]);

    return set;
}

bool bitset_in(bitset set, unsigned int value) {
    if (value > set.maxValue)
        return false;

    return (set.values & (1 << value)) != 0;
}

bool bitset_isEqual(bitset set1, bitset set2) {
    return set1.values == set2.values;
}

bool bitset_isSubset(bitset subset, bitset set) {
    return (set.values & subset.values) == subset.values;
}

void bitset_insert(bitset *set, unsigned int value) {
    set->values = set->values | (1 << value);
}

void bitset_deleteElement(bitset *set, unsigned int value) {
    assert(value <= set->maxValue);
    set->values = set->values & ~(1 << value);
}

bitset bitset_union(bitset set1, bitset set2) {
    assert(set1.maxValue == set2.maxValue);
    return (bitset) {set1.values | set2.values, set1.maxValue > set2.maxValue?
                    set1.maxValue : set2.maxValue};
}

bitset bitset_intersection(bitset set1, bitset set2) {
    assert(set1.maxValue == set2.maxValue);
    return (bitset) {set1.values & set2.values, set1.maxValue};
}

bitset bitset_difference(bitset set1, bitset set2) {
    assert(set1.maxValue == set2.maxValue);
    return (bitset) {set1.values & ~set2.values, set1.maxValue};
}

bitset bitset_symmetricDifference(bitset set1, bitset set2) {
    assert(set1.maxValue == set2.maxValue);
    return (bitset) {set1.values ^ set2.values, set1.maxValue};
}

bitset bitset_complement(bitset set) {
    uint32_t universum = (1 << (set.maxValue + 1)) - 1;
    return (bitset) {set.values ^ universum, set.maxValue};
}


void bitset_print(bitset set) {
    printf("{");
    int isEmpty = 1;

    for (int i = 0; i <= set.maxValue; ++i) {
        if (bitset_in(set, i)) {
            printf("%d, ", i);
            isEmpty = 0;
        }
    }

    if (isEmpty)
        printf("}\n");
    else
        printf("\b\b}\n");
}





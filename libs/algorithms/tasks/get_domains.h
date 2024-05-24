#ifndef UNTITLED11_GET_DOMAINS_H
#define UNTITLED11_GET_DOMAINS_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../../data_structures/string/string_.h"

#define MAX_LENGTH_DOMAIN 128
#define MAX_DOMAIN 64

typedef struct domain {
    char name[MAX_LENGTH_DOMAIN];
    int amount;
} domain;

typedef struct domains {
    domain data[MAX_DOMAIN];
    size_t size;
} domains;

int getWordToDot(char *begin_search, WordDescriptor *word) {
    word->begin = findNonSpace(begin_search);
    if (*word->begin == '\0')
        return false;

    size_t len = strlen_(begin_search);
    word->end = find(word->begin, word->begin + len, '.');

    if (word->end == word->begin + len || *word->end == '\n')
        word->end -= 2;

    return true;
}

void push_domain_in_domains(domains *ds, domain *d) {
    ds->data[ds->size].amount = d->amount;
    copy(d->name, d->name + strlen_(d->name) + 1, ds->data[ds->size].name);
    ds->size++;
}

void merge_equal_domains(domains *ds) {
    for (int i = 0; i < ds->size; i++)
        for (int j = i + 1; j < ds->size; j++) {
            if (strcmp_(ds->data[i].name, ds->data[j].name) == 0 && ds->data[i].amount >= 0 &&
                ds->data[j].amount >= 0) {
                ds->data[i].amount += ds->data[j].amount;
                ds->data[j].amount = -1;
            }

        }
}

void getDomains(char *s, domains *ds) {
    char *read_ptr = s;

    WordDescriptor amount_as_text, name_domain;
    getWordWithoutSpace(read_ptr, &amount_as_text);

    read_ptr = amount_as_text.end + 1;

    getWordWithoutSpace(read_ptr, &name_domain);

    int k = 1;
    int amount = 0;
    read_ptr = amount_as_text.end;

    while (read_ptr >= amount_as_text.begin) {
        amount += k * (*read_ptr - '0');
        k *= 10;
        read_ptr--;
    }

    read_ptr = name_domain.begin;
    _bag.size = 0;

    while (getWordToDot(read_ptr, &_bag.words[_bag.size])) {
        read_ptr = _bag.words[_bag.size].end + 1;
        _bag.size++;
    }

    for (int i = 0; i < _bag.size; i++) {
        domain d = {.amount = amount};

        char *begin = d.name;
        begin = copy(_bag.words[i].begin, _bag.words[i].end + 1, begin);

        for (int j = i + 1; j < _bag.size; j++)
            begin = copy(_bag.words[j].begin, _bag.words[j].end + 1, begin);

        push_domain_in_domains(ds, &d);
    }

    freeBag(&_bag);
}

void getDomainsInFile(const char *filename) {
    FILE *file = fopen(filename, "r");

    domains ds = {.size = 0};

    while (fgets(stringBuffer_, 256, file)) {
        getDomains(stringBuffer_, &ds);
        freeString(stringBuffer_);
    }

    merge_equal_domains(&ds);

    fclose(file);

    file = fopen(filename, "w");

    for (int i = 0; i < ds.size; i++) {
        if (ds.data[i].amount >= 0)
            fprintf(file, "%d %s\n", ds.data[i].amount, ds.data[i].name);
    }

    fclose(file);
}

void test_getDomainsInFile_1_empty_file() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.20\\task_4_test_1";

    FILE *file = fopen(filename, "w");
    fclose(file);

    getDomainsInFile(filename);

    file = fopen(filename, "r");

    char dest[100] = "";
    fscanf(file, "%s", dest);

    fclose(file);

    assert(strcmp_(dest, "") == 0);
}


void test_getDomainsInFile_2_one_domain() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.20\\task_4_test_2";

    FILE *file = fopen(filename, "w");

    char s[100] = "900 discuss.codeforces.com";
    fprintf(file, "%s\n", s);

    fclose(file);

    getDomainsInFile(filename);

    file = fopen(filename, "r");

    char dest1[100] = "";
    char dest2[100] = "";
    char dest3[100] = "";
    fgets(dest1, sizeof(dest1), file);
    fgets(dest2, sizeof(dest2), file);
    fgets(dest3, sizeof(dest3), file);

    fclose(file);

    assert(strcmp_(dest1, "900 discuss.codeforces.com\n") == 0);
    assert(strcmp_(dest2, "900 codeforces.com\n") == 0);
    assert(strcmp_(dest3, "900 com\n") == 0);
}


void test_getDomainsInFile_3_more_domain() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.20\\task_4_test_3";

    FILE *file = fopen(filename, "w");

    char s1[100] = "900 discuss.codeforces.com";
    char s2[100] = "69 mail.com";
    fprintf(file, "%s\n", s1);
    fprintf(file, "%s\n", s2);

    fclose(file);

    getDomainsInFile(filename);

    file = fopen(filename, "r");

    char dest1[100] = "";
    char dest2[100] = "";
    char dest3[100] = "";
    char dest4[100] = "";
    fgets(dest1, sizeof(dest1), file);
    fgets(dest2, sizeof(dest2), file);
    fgets(dest3, sizeof(dest3), file);
    fgets(dest4, sizeof(dest4), file);

    fclose(file);

    assert(strcmp_(dest1, "900 discuss.codeforces.com\n") == 0);
    assert(strcmp_(dest2, "900 codeforces.com\n") == 0);
    assert(strcmp_(dest3, "969 com\n") == 0);
    assert(strcmp_(dest4, "69 mail.com\n") == 0);
}


void test_getDomainsInFile() {
    test_getDomainsInFile_1_empty_file();
    test_getDomainsInFile_2_one_domain();
    test_getDomainsInFile_3_more_domain();
}

#endif //UNTITLED11_GET_DOMAINS_H

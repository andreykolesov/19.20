
#ifndef UNTITLED11_AUTO_FILL_H
#define UNTITLED11_AUTO_FILL_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../../data_structures/string/string_.h"

#define MAX_REQUEST 128

typedef struct request {
    WordDescriptor sequence;
    int position;
} request;

typedef struct requests {
    request request[MAX_REQUEST];
    size_t size;
} requests;

void freeRequests(requests *rs) {
    for (int i = 0; i < rs->size; i++) {
        rs->request[i].position = 0;
        rs->request[i].sequence.begin = NULL;
        rs->request[i].sequence.end = NULL;
    }

    rs->size = 0;
}

void printRequest(request *r) {
    printf("%d ", r->position);
    printWord(r->sequence);
}

void autoFill(const char *filename) {
    FILE *file = fopen(filename, "r");

    long long int n, q;
    fscanf(file, "%lld", &n);
    fscanf(file, "%lld", &q);

    _bag.size = 0;
    char *begin = stringBuffer_;
    for (int i = 0; i < n; i++) {
        fscanf(file, "%s", begin);
        getWordWithoutSpace(begin, &_bag.words[_bag.size]);
        begin = _bag.words[_bag.size].end + 1;
        _bag.size++;
    }

    requests rs = {.size = 0};
    for (int i = 0; i < q; i++) {
        fscanf(file, "%d", &rs.request[i].position);
        fscanf(file, "%s", begin);
        getWordWithoutSpace(begin, &rs.request[i].sequence);
        begin = rs.request[i].sequence.end + 1;
        rs.size++;
    }

    fclose(file);

    file = fopen(filename, "w");

    for (int i = 0; i < q; i++) {
        int amount = 0;
        for (int j = 0; j < n; j++) {
            if (isSubWord(rs.request[i].sequence, _bag.words[j])) {
                amount++;

                if (amount == rs.request[i].position)
                    fprintf(file, "%d\n", j + 1);
            }
        }

        if (amount < rs.request[i].position)
            fprintf(file, "-1\n");
    }

    fclose(file);

    freeString(stringBuffer_);
    freeBag(&_bag);
    freeRequests(&rs);
}

void test_autoFill_1_empty_file() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.20\\task_11_test_1";

    FILE *file = fopen(filename, "w");

    int n = 0;
    int q = 0;
    fprintf(file, "%d %d \n", n, q);

    fclose(file);

    autoFill(filename);

    file = fopen(filename, "r");

    char res[100] = "";
    fgets(res, 100, file);

    fclose(file);

    assert(strcmp_(res, "") == 0);
}

void test_autoFill_2_zero_q() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.20\\task_11_test_2";

    FILE *file = fopen(filename, "w");

    int n = 3;
    int q = 0;
    fprintf(file, "%d %d \n", n, q);
    fprintf(file, "aa\n");
    fprintf(file, "d\n");
    fprintf(file, "mamama\n");

    fclose(file);

    autoFill(filename);

    file = fopen(filename, "r");

    char res[100] = "";
    fgets(res, 100, file);

    fclose(file);

    assert(strcmp_(res, "") == 0);
}

void test_autoFill_3_different_element() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.20\\task_11_test_3";

    FILE *file = fopen(filename, "w");

    int n = 10;
    int q = 3;
    fprintf(file, "%d %d \n", n, q);
    fprintf(file, "aa    \n");
    fprintf(file, "aaa   \n");
    fprintf(file, "aab   \n");
    fprintf(file, "ab    \n");
    fprintf(file, "abc   \n");
    fprintf(file, "ac    \n");
    fprintf(file, "ba    \n");
    fprintf(file, "daa   \n");
    fprintf(file, "dab   \n");
    fprintf(file, "dadba \n");
    fprintf(file, "4 a   \n");
    fprintf(file, "2 da   \n");
    fprintf(file, "4 da \n");

    fclose(file);

    autoFill(filename);

    file = fopen(filename, "r");

    int n1, n2, n3;
    fscanf(file, "%d\n", &n1);
    fscanf(file, "%d\n", &n2);
    fscanf(file, "%d\n", &n3);

    fclose(file);

    assert(n1 == 4);
    assert(n2 == 9);
    assert(n3 == -1);
}

void test_autoFill() {
    test_autoFill_1_empty_file();
    test_autoFill_2_zero_q();
    test_autoFill_3_different_element();
}

#endif //UNTITLED11_AUTO_FILL_H

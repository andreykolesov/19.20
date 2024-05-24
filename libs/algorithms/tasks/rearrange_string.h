#ifndef UNTITLED11_REARRANGE_STRING_H
#define UNTITLED11_REARRANGE_STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../../data_structures/string/string_.h"

void rearrangeString(const char* s, char* res, const int a[], const int n) {
    for (int i = 0; i < n; i++)
        res[i] = s[a[i]];
}

void rearrangeStringInFile(const char* filename) {
    FILE* file = fopen(filename, "r");

    char s[1024] = "";
    fscanf(file, "%s", s);

    size_t len = strlen_(s);
    int* numbers = (int *) malloc(len * sizeof(int));

    for (int i = 0; i < len; i++)
        fscanf(file, "%d", numbers + i);

    fclose(file);

    char res[1024] = "";
    rearrangeString(s, res, numbers, len);

    file = fopen(filename, "w");

    fprintf(file, "%s", res);

    fclose(file);

    free(numbers);
}

void test_rearrangeStringInFile_1_empty_file() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.20\\task_8_test_1";

    FILE* file = fopen(filename, "w");
    fclose(file);

    rearrangeStringInFile(filename);

    file = fopen(filename, "r");

    char res[100] = "";
    fscanf(file, "%s", res);

    fclose(file);

    assert(strcmp_(res, "") == 0);
}


void test_rearrangeStringInFile_2_one_element() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.20\\task_8_test_2";

    FILE* file = fopen(filename, "w");

    fprintf(file, "s\n");
    fprintf(file, "0");

    fclose(file);

    rearrangeStringInFile(filename);

    file = fopen(filename, "r");

    char res[100] = "";
    fscanf(file, "%s", res);

    fclose(file);

    assert(strcmp_(res, "s") == 0);
}


void test_rearrangeStringInFile_3_more_element() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.20\\task_8_test_3";

    FILE* file = fopen(filename, "w");

    fprintf(file, "abap\n");
    fprintf(file, "0 3 2 1");

    fclose(file);

    rearrangeStringInFile(filename);

    file = fopen(filename, "r");

    char res[100] = "";
    fscanf(file, "%s", res);

    fclose(file);

    assert(strcmp_(res, "apab") == 0);
}

void test_rearrangeStringInFile() {
    test_rearrangeStringInFile_1_empty_file();
    test_rearrangeStringInFile_2_one_element();
    test_rearrangeStringInFile_3_more_element();
}

#endif //UNTITLED11_REARRANGE_STRING_H

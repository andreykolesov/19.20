#ifndef UNTITLED11_GENERATE_NUMBERS_H
#define UNTITLED11_GENERATE_NUMBERS_H

#include <stdio.h>
#include <string.h>
#include <assert.h>

void generateNumbers(const char *filename) {
    int num[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    FILE *file = fopen(filename, "r");

    char res[10] = "";
    char s[10] = "";
    fscanf(file, "%s", s);

    fclose(file);

    unsigned int len_s = strlen(s);

    char *rec_ptr = res;
    char *read_ptr = s;
    unsigned int i_index = 0;
    unsigned int d_index = len_s;

    while (i_index != d_index) {
        if (*read_ptr == 'I') {
            *rec_ptr = (char) (num[i_index] + '0');
            i_index++;
        } else {
            *rec_ptr = (char) (num[d_index] + '0');
            d_index--;
        }

        read_ptr++;
        rec_ptr++;
    }

    *rec_ptr = (char) (num[i_index] + '0');

    file = fopen(filename, "w");

    fprintf(file, "%s", res);

    fclose(file);
}

void test_generateNumbers_1_empty_file() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.20\\task_6_test_1";

    FILE *file = fopen(filename, "w");
    fclose(file);

    generateNumbers(filename);

    file = fopen(filename, "r");

    int nums;
    fscanf(file, "%d", &nums);

    fclose(file);

    assert(nums == 1);
}


void test_generateNumbers_2_unit_length() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.20\\task_6_test_2";

    FILE *file = fopen(filename, "w");

    fprintf(file, "I");

    fclose(file);

    generateNumbers(filename);

    file = fopen(filename, "r");

    int nums;
    fscanf(file, "%d", &nums);

    fclose(file);

    assert(nums == 12);
}


void test_generateNumbers_3_average_length() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.20\\task_6_test_3";

    FILE *file = fopen(filename, "w");

    fprintf(file, "IIID");

    fclose(file);

    generateNumbers(filename);

    file = fopen(filename, "r");

    int nums;
    fscanf(file, "%d", &nums);

    fclose(file);

    assert(nums == 12354);
}


void test_generateNumbers_4_max_length() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.20\\task_6_test_4";

    FILE *file = fopen(filename, "w");

    fprintf(file, "IIIIIIII");

    fclose(file);

    generateNumbers(filename);

    file = fopen(filename, "r");

    int nums;
    fscanf(file, "%d", &nums);

    fclose(file);

    assert(nums == 123456789);
}


void test_generateNumbers() {
    test_generateNumbers_1_empty_file();
    test_generateNumbers_2_unit_length();
    test_generateNumbers_3_average_length();
    test_generateNumbers_4_max_length();
}

#endif //UNTITLED11_GENERATE_NUMBERS_H

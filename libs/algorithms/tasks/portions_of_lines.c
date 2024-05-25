#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <source file> <target file> <N>\n", argv[0]);
        return 1;
    }

    FILE *sourceFile, *targetFile;
    int N, number;

    sourceFile = fopen(argv[1], "r");
    if (sourceFile == NULL) {
        printf("Failed to open source file..\n");
        return 1;
    }

    targetFile = fopen(argv[2], "w");
    if (targetFile == NULL) {
        printf("Failed to open target file.\n");
        fclose(sourceFile);
        return 1;
    }

    N = atoi(argv[3]);

    while (fscanf(sourceFile, "%d", &number) != EOF) {
        if (number < N) {
            fprintf(targetFile, "%d\n", number);
        }
    }

    fclose(sourceFile);
    fclose(targetFile);

    return 0;
}
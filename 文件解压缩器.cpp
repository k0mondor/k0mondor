#include <stdio.h>
#include <stdlib.h>

void decompressFile(const char *inputFileName, const char *outputFileName) {
    FILE *inputFile = fopen(inputFileName, "r");
    FILE *outputFile = fopen(outputFileName, "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    int count;
    char currentChar;

    while (fscanf(inputFile, "%d%c", &count, &currentChar) == 2) {
        // Write 'count' times 'currentChar' to the output file
        for (int i = 0; i < count; i++) {
            fputc(currentChar, outputFile);
        }
    }

    fclose(inputFile);
    fclose(outputFile);
}

int main() {
    const char *inputFileName = "compressed.txt";  // 压缩文件名
    const char *outputFileName = "decompressed.txt"; // 解压后的文件名

    decompressFile(inputFileName, outputFileName);

    printf("File decompressed successfully!\n");

    return 0;
}


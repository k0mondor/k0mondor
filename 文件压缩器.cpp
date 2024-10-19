#include <stdio.h>
#include <stdlib.h>

void compressFile(const char *inputFileName, const char *outputFileName) {
    FILE *inputFile = fopen(inputFileName, "r");
    FILE *outputFile = fopen(outputFileName, "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    char currentChar, prevChar;
    int count = 1;
    
    prevChar = fgetc(inputFile);
    if (prevChar == EOF) {
        printf("Input file is empty.\n");
        fclose(inputFile);
        fclose(outputFile);
        return;
    }

    while ((currentChar = fgetc(inputFile)) != EOF) {
        if (currentChar == prevChar) {
            count++;
        } else {
            // Write the character and its count to the output file
            if (count > 1) {
                fprintf(outputFile, "%d%c", count, prevChar);
            } else {
                fprintf(outputFile, "%c", prevChar);
            }
            prevChar = currentChar;
            count = 1;
        }
    }
    
    // Write the last character and its count
    if (count > 1) {
        fprintf(outputFile, "%d%c", count, prevChar);
    } else {
        fprintf(outputFile, "%c", prevChar);
    }

    fclose(inputFile);
    fclose(outputFile);
}

int main() {
    const char *inputFileName = "input.txt";
    const char *outputFileName = "compressed.txt";

    compressFile(inputFileName, outputFileName);

    printf("File compressed successfully!\n");

    return 0;
}


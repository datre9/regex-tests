#include <stdio.h>
#include <stdlib.h>

char *readFile(char *filename);

int main() {
    char *fileContents = readFile("../adventures-of-huckleberry-finn.txt");

    printf("%s", fileContents);

    free(fileContents);
    return 0;
}

char *readFile(char *filename) {
    FILE *file;
    file = fopen(filename, "r");

    if (file == NULL) return NULL;

    fseek(file, 0, SEEK_END);
    int length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *string = malloc(sizeof(char) * (length + 1));

    char c;
    int i = 0;
    while((c = fgetc(file)) != EOF) {
        string[i] = c;
        i++;
    }
    string[i] = '\0';

    fclose(file);

    return string;
}
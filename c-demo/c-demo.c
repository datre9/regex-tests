#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define PCRE2_CODE_UNIT_WIDTH 8
#include <pcre2.h>

char *readFile(char *filename);
char *stringAppend(char *s1, char *s2);

int main()
{
    char *data = readFile("../adventures-of-huckleberry-finn.txt");
    char *pattern = "finn|huckleberry";
    char *toWrite = "id;time(ns);memory(B)\n";

    PCRE2_SIZE offset = 0;
    PCRE2_SIZE *ovector;
    int errorcode;
    PCRE2_SIZE erroroffset;
    pcre2_code_8 *re = pcre2_compile_8((PCRE2_SPTR8)pattern, PCRE2_ZERO_TERMINATED, PCRE2_CASELESS, &errorcode, &erroroffset, NULL);
    pcre2_match_data_8 *match_data = pcre2_match_data_create_from_pattern_8(re, NULL);
    int length = strlen(data);

    LARGE_INTEGER frequency;
    LARGE_INTEGER start, end;
    QueryPerformanceFrequency(&frequency);

    for (int i = 0; i < 1000; i++)
    {
        offset = 0;

        QueryPerformanceCounter(&start);
        while (pcre2_match_8(re, (PCRE2_SPTR8)data, length, offset, 0, match_data, NULL) == 1)
        {
            ovector = pcre2_get_ovector_pointer_8(match_data);
            offset = ovector[1];
        }
        QueryPerformanceCounter(&end);

        double time = (double)(end.QuadPart - start.QuadPart) * 1e9 / (double)frequency.QuadPart;

        char indexStr[50];
        sprintf(indexStr, "%d;%.0f;placeholder\n", i, time);

        char *temp = toWrite;
        toWrite = stringAppend(toWrite, indexStr);
        free(temp);
    }

    FILE *fptr;
    fptr = fopen("results.csv", "w");
    fprintf(fptr, toWrite);
    fclose(fptr);

    free(toWrite);
    pcre2_match_data_free_8(match_data);
    pcre2_code_free_8(re);
    free(data);
    return 0;
}

char *stringAppend(char *s1, char *s2)
{
    int s1Length = strlen(s1);
    int s2Length = strlen(s2);
    int size = s1Length + s2Length + 1;
    char *s = calloc(size, sizeof(char));

    for (int i = 0; i < s1Length; i++)
        s[i] = s1[i];
    for (int i = 0; i < s2Length; i++)
        s[i + s1Length] = s2[i];

    s[size - 1] = '\0';
    return s;
}

char *readFile(char *filename)
{
    FILE *file;
    file = fopen(filename, "r");

    if (file == NULL)
        return NULL;

    fseek(file, 0, SEEK_END);
    int length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *string = malloc(sizeof(char) * (length + 1));

    char c;
    int i = 0;
    while ((c = fgetc(file)) != EOF)
    {
        string[i] = c;
        i++;
    }
    string[i] = '\0';

    fclose(file);

    return string;
}
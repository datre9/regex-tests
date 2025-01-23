#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define PCRE2_CODE_UNIT_WIDTH 8
#include <pcre2.h>

char *readFile(char *filename);
char *stringAppend(char *s1, char *s2);
void benchmark(char *text, char *regex, char *title);

char *toWrite = "";

int main()
{
    char *abc1 = readFile("../abc1.txt");
    char *abc2 = readFile("../abc2.txt");
    char *abc3 = readFile("../abc3.txt");

    char *regexKMP = "(ab)+";
    char *regexAC = "ac|aca|cab|ab";
    char *regexSS = "(a|b)(b|c)";
    char *regexWC = "a..b..c..";
    char *regexNE = "d";

    benchmark(abc1, regexKMP, "KMP1");
    benchmark(abc2, regexKMP, "KMP2");
    benchmark(abc3, regexKMP, "KMP3");

    benchmark(abc1, regexAC, "AC1");
    benchmark(abc2, regexAC, "AC2");
    benchmark(abc3, regexAC, "AC3");
    
    benchmark(abc1, regexSS, "SS1");
    benchmark(abc2, regexSS, "SS2");
    benchmark(abc3, regexSS, "SS3");
    
    benchmark(abc1, regexWC, "WC1");
    benchmark(abc2, regexWC, "WC2");
    benchmark(abc3, regexWC, "WC3");
    
    benchmark(abc1, regexNE, "NE1");
    benchmark(abc2, regexNE, "NE2");
    benchmark(abc3, regexNE, "NE3");


    FILE *fptr;
    fptr = fopen("pcre2_results.csv", "w");
    fprintf(fptr, toWrite);
    fclose(fptr);

    free(toWrite);
    free(abc1);
    return 0;
}

void benchmark(char *text, char *regex, char *title)
{
    char *newWrite;

    newWrite = stringAppend(toWrite, title);
    free(toWrite);
    toWrite = newWrite;
    newWrite = stringAppend(toWrite, "\n");
    free(toWrite);
    toWrite = newWrite;


    PCRE2_SIZE offset = 0;
    PCRE2_SIZE *ovector;
    int errorcode;
    PCRE2_SIZE erroroffset;
    pcre2_code_8 *re = pcre2_compile_8((PCRE2_SPTR8)regex, PCRE2_ZERO_TERMINATED, 0, &errorcode, &erroroffset, NULL);

    if (!re)
    {
        fprintf(stderr, "PCRE2 compilation failed at offset %zu: %d\n", erroroffset, errorcode);
        exit(1);
    }

    pcre2_match_data_8 *match_data = pcre2_match_data_create_from_pattern_8(re, NULL);
    int length = strlen(text);

    LARGE_INTEGER frequency;
    LARGE_INTEGER start, end;
    QueryPerformanceFrequency(&frequency);

    for (int i = 0; i < 1000; i++)
    {
        offset = 0;

        QueryPerformanceCounter(&start);
        while (offset < length)
        {
            int rc = pcre2_match_8(re, (PCRE2_SPTR8)text, length, offset, 0, match_data, NULL);
            if (rc < 0)
            {
                break;
            }

            ovector = pcre2_get_ovector_pointer_8(match_data);
            offset = ovector[1];

            if (ovector[0] == ovector[1])
                offset++;

        }
        QueryPerformanceCounter(&end);

        double time = (double)(end.QuadPart - start.QuadPart) * 1e9 / (double)frequency.QuadPart;

        char indexStr[50];
        sprintf(indexStr, "%.9g\n", (time / 1000000));

        char *temp = toWrite;
        toWrite = stringAppend(toWrite, indexStr);
        free(temp);
    }

    pcre2_match_data_free_8(match_data);
    pcre2_code_free_8(re);
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
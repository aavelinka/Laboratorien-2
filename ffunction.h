#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/////////////////////////////////////////////////////////////////////
//прототипы функций

char* name_of_file();
void scunf_file(const char* filename);
void printf_file(const char *filename);
int count_c(const char *filename, char c);
char* input_string();
int input_index(const char *filename);
void reverse_substring(const char *filename, int index1, int index2);

/////////////////////////////////////////////////////////////////////


char* name_of_file() {
    int len_str = 0;
    int capacity = 1; 
    char* s = (char*)malloc(capacity * sizeof(char)); 

    char c = getchar(); 

    while ((c = getchar()) != '\n') {
        if (len_str + 1 >= capacity) {
            capacity *= 2;
            s = realloc(s, capacity * sizeof(char));
        }

        s[len_str++] = c;
    }
    s[len_str] = '\0';

    if(strcmp(s + len_str - 4, ".txt") != 0){
        s = realloc(s, len_str + 5);
        strcat(s, ".txt");
    }

    return s;
}

void scunf_file(const char* filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file for writing.\n");
        return;
    }
    rewind(stdin);

    puts("Enter data to write to the file (press Enter to finish):");

    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        fputc(c, file);
    }
    fputc(c, file);

    fclose(file);
}


void printf_file(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file for reading.\n");
        return;
    }

    puts("Data from file:");

    int c;
    while ((c = fgetc(file)) != EOF) {
        putchar(c);
    }

    printf("\n");
    fclose(file);
}
char* input_string() {
    int len_str = 0;
    int capacity = 1; 
    char* s = (char*)malloc(capacity * sizeof(char)); 

    char c = getchar(); 

    while ((c = getchar()) != '\n') {
        if (len_str + 1 >= capacity) {
            capacity *= 2;
            s = realloc(s, capacity * sizeof(char));
        }

        s[len_str++] = c;
    }

    s[len_str] = '\0';

    return s;
}

int count_c(const char *filename, char element) {
    int sum = 0;
    char c;
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file.\n");
        return -1;
    }
    while ((c = fgetc(file)) != EOF) {
        if(c == element) {
            sum++;
        }
    }

    return sum;
}

long size_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Не удалось открыть файл");
        return -1;
    }
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fclose(file);
    
    return size;
}

int input_index(const char *filename) {
    int index = -1;
    if(scanf(" %d", &index) != 1 || index >= size_file(filename)) {
        puts("Sorry, but your request is not correct");
    }
    return index;
}

void reverse_substring(const char *filename, int index1, int index2) {
    FILE *file = fopen(filename, "r+");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }


    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);


    if (index1 < 0 || index2 < 0 || index1 >= fileSize || index2 >= fileSize) {
        fclose(file);
        printf("Invalid indices.\n");
        return;
    }


    if (index1 < index2) {
        for (int i = 0; i < (index2 - index1 + 1) / 2; i++) {
            fseek(file, index1 + i, SEEK_SET);
            char tmp1;
            fread(&tmp1, sizeof(char), 1, file);

            fseek(file, index2 - i, SEEK_SET);
            char tmp2;
            fread(&tmp2, sizeof(char), 1, file);

            fseek(file, index1 + i, SEEK_SET);
            fwrite(&tmp2, sizeof(char), 1, file);

            fseek(file, index2 - i, SEEK_SET);
            fwrite(&tmp1, sizeof(char), 1, file);
        }
    } else {
        for (int i = 0; i < (index1 - index2 + 1) / 2; i++) {

            fseek(file, index2 + i, SEEK_SET);
            char tmp1;
            fread(&tmp1, sizeof(char), 1, file);

            fseek(file, index1 - i, SEEK_SET);
            char tmp2;
            fread(&tmp2, sizeof(char), 1, file);

            fseek(file, index2 + i, SEEK_SET);
            fwrite(&tmp2, sizeof(char), 1, file);

            fseek(file, index1 - i, SEEK_SET);
            fwrite(&tmp1, sizeof(char), 1, file);
        }
    }

    fclose(file);
}

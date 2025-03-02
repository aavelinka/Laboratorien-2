#include "ffunction.h"

int main(int argc, char *argv[]) {
    char *filename;
    if (argc > 1) {
        filename = argv[1];
    } else {
        printf("Enter file name: ");
        filename = name_of_file();
    }

    do {
        puts("Please, choose the option:");
        printf("Writing text to a file and outputting it - 1\n");
        printf("Count how many times a symbol in a file - 2\n");
        printf("Reverse a substring in a file - 3\n");


        char option;
        scanf(" %c", &option); 

        switch (option) {
            case '1': {
                scunf_file(filename);
                printf_file(filename);
                break;
            }
            case '2': {
                char c;
                scunf_file(filename);
                printf("Please, choose the symbol: ");
                scanf(" %c", &c); 
                int count = count_c(filename, c);
                printf("The count of symbol '%c' in file: %d\n", c, count);
                break;
            }
            case '3': {
                puts("Please, choose start and end of substring: ");
                printf("Start: ");
                int index_1 = input_index(filename);
                if (index_1 == -1) {
                    continue;
                }
                printf("End: ");
                int index_2 = input_index(filename);
                if (index_2 == -1) {
                    continue;
                }
                reverse_substring(filename, index_1, index_2);
                printf_file(filename);
                break;
            }
            default:
                puts("Sorry, but your request is not correct");
        }


        rewind(stdin);
    } while (puts("Do you want to run the program again?\nSelect: 1 - Continue, 0 - EXIT"), getchar() == '1');

    puts("Good job, dear! See you later ;)");
    return 0;
}

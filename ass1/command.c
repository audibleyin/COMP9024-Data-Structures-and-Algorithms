//
// Created by Rui.Mu on 2019-08-22.
//
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define WORD_SIZE 30
#define MAX_LENGTH 1024

// read vocabularies from stdin
void read_vocabularies_from_stdin(char **vocabularies, int *number_of_vocabularies) {
    int input = 0, index = 0;
    char word[30];
    // read from stdin / command line
    // aaaaaa  aaa  a a a a

    while ((input = getchar()) != EOF) {
        if (!isalpha(input)) {
            if (strlen(word) > 0) {
                if (*number_of_vocabularies == 0 || strcmp(word, vocabularies[*number_of_vocabularies - 1]) != 0) {
                    vocabularies[*number_of_vocabularies] = malloc(WORD_SIZE * sizeof(char));
                    strcpy(vocabularies[*number_of_vocabularies], word);
                    // plus + 1
                    *number_of_vocabularies = *number_of_vocabularies + 1;
                }
            }
            index = 0;
        } else {
            word[index] = input;
            index++;
        }
        word[index] = '\0';
    }

    // the last
    if (strlen(word) > 0) {
        strcpy(vocabularies[*number_of_vocabularies], word);
        *number_of_vocabularies = *number_of_vocabularies + 1;
    }

    // print vocabularies
    if (*number_of_vocabularies > 0) {
        printf("Dictionary\n");
        for (int i = 0; i < *number_of_vocabularies; i++) printf("%d: %s\n", i, vocabularies[i]);
    }
}

// read vocabularies from stdin
void read_numbers_from_stdin(int *numbers, int *number_count) {
    int input = 0,index = 0;
    int number = 0;
    // read from stdin / command line
    // aaaaaa  aaa  a a a a
    while ((input = getchar()) != EOF) {
        if (!isalpha(input)) {
            if (index > 0) {
                numbers[*number_count] = number;
                *number_count = *number_count + 1;
            }
            index = 0;
            number = 0;
        }
        number = number * 10 + index - '0';
    }

    // the last
    if (index > 0) {
        numbers[*number_count] = number;
        *number_count = *number_count + 1;
    }

    // print vocabularies
    if (*number_count > 0) {
        printf("Dictionary\n");
        for (int i = 0; i < *number_count; i++) printf("%d: %d\n", i, numbers[i]);
    }
}

// main
void read_string(int argc, char *argv[]) {
    //
    char **vocabularies;
    vocabularies = malloc(MAX_LENGTH * sizeof(char *));
    // number of vocabularies
    int number_of_vocabularies = 0;
    // read words from command line
    read_vocabularies_from_stdin(vocabularies, &number_of_vocabularies);
}

// main
void read_numbers(int argc, char *argv[]) {
    int *numbers = malloc(MAX_LENGTH * sizeof(int));
    // number of vocabularies
    int number_of_vocabularies = 0;
    // read words from command line
    read_numbers_from_stdin(numbers, &number_of_vocabularies);
}

int main(int argc, char *argv[]){
    printf("argv %d:",argv);
}
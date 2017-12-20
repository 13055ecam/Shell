#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "stats.h"
#include "clnup.h"
#include "shrink.h"
#include <unistd.h>

#define STATS  1
#define SHRINK 2
#define CLNUP  4
#define SORTN  8

/**
 * Split the string input by the space character and store it in the argv array.
 */
void splitByArg(char *input, char argv[50][50]) {
    int i = 0;
    const char *sep = " ";
    char *token = strtok(input, sep);
    while (token != NULL) {
        strcpy(argv[i], token);
        token = strtok(NULL, sep);
        i++;
    }
}

/**
 * Read the standard input up to CR and return a pointer to the string.
 */
char *readSTDIN() {
#define BUF_SIZE 1024
    char buffer[BUF_SIZE];
    char *content = malloc(sizeof(char) * BUF_SIZE);
    if (content == NULL) {
        perror("Failed to allocate content");
        return NULL;
    }
    fgets(buffer, BUF_SIZE, stdin);
    buffer[strlen(buffer)-1] = '\0';
    strcpy(content, buffer);
    if (ferror(stdin)) {
        free(content);
        perror("Error reading from stdin.");
        return NULL;
    }
    return content;
#undef BUF_SIZE
}

/**
 * Execute the selected command by acting as an interpreter and reading the its
 * input from the stdin.
 */
int main(void) {
    char *input;
    int operation = 0;
    char argv[25][50];

    printf("This is the launch terminal of our projet.                     \n" \
           "The commands are stats, shrink, clnup, sortn and exit.         \n" \
           "Type `<command> --help' to get more information on the command.\n");

    for (;;) {
        printf(">>> ");
        input = readSTDIN();
        if (input == NULL) {
            // error reading from stdin
            return 1;
        }
        bzero(argv, sizeof argv);
        splitByArg(input, argv);

        // simple and naive comparaison to determine the selected operation
        if (!strcmp(argv[0], "stats")) {
            operation = STATS;
        } else if (!strcmp(argv[0], "shrink")) {
            operation = SHRINK;
        } else if (!strcmp(argv[0], "clnup")) {
            operation = CLNUP;
        } else if (!strcmp(argv[0], "sortn")) {
            operation = SORTN;
        } else if (!strcmp(argv[0], "exit")) {
            // end of program
            return 0;
        } else {
            fprintf(stderr, "The command %s is unknow\n", argv[0]);
        }

        // redirect the program to the selected operation
        switch (operation) {
            case STATS:
                if (!strcmp(argv[1], "--help")) {
                    printf("Write <stats> to show all informations about "     \
                           "this folder \n");
                }
                stats(NULL);
                break;

            case SHRINK:
                if (!strcmp(argv[1], "--help")) {
                    printf("Write <shrink> to compress several files of this " \
                           "folder \n");
                }
                int min_size = atoi(argv[2]);
                if (min_size == 0) {
                    fprintf(stderr, "Missing or invalide minimal compressing"  \
                                    "size, assigning 1MiB by default.");
                }
                shrink(min_size);
                break;

            case CLNUP:
                if (!strcmp(argv[1], "--help")) {
                    printf("Write <clnup> to sort files of this folder in "    \
                           "multiple folders according the type file \n");
                }
                clnup(NULL);
                break;
                
            case SORTN:
                if (!strcmp(argv[1], "--help")) {
                    printf("Write <sortn> \n");
                }
                clnup(NULL);
                break;
        }
    }
}

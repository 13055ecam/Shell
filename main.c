#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>
#include "shrink.h"
#include "stats.h"
#include "clnup.h"

/**
 * Structure that represent a command.
 */
struct command {
    const char name[32];            // name of the command
    const char help[512];           // --help message
    int (*execute)(char [25][50]);  // pointer to function
};


/**
 * Split the string input by the space character
 * and store it in the argv array.
 */
void split_by_arg(char *input, char argv[50][50]) {
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
 * Read the standard input up to CR and
 * return a pointer to the string.
 */
char *read_stdin() {
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
 * Execute the selected command by acting as an interpreter
 * and reading the its input from the stdin.
 */
int main(void) {
    char *input;
    int operation;
    char argv[25][50];

    const struct command commands[] = {
        {
            .name    = "stats",
            .execute = stats,
            .help    = "Write `stats` to show all informations about this folder\n",
        },
        {
            .name    = "shrink",
            .execute = shrink,
            .help    = "Write `shrink` to compress several files of this folder\n",
        },
        {
            .name    = "clnup",
            .execute = clnup,
            .help    = "Write `clnup` to sort files of this folder in multiple folders according " \
                       "the type file \n",
        },
        {0}
    };

    printf("This is the launch terminal of our projet.                     \n" \
           "The commands are stats, shrink, clnup, sortn and exit.         \n" \
           "Type `<command> --help` to get more information on the command.\n");

    for (;;) {
        printf(">>> ");
        input = read_stdin();
        if (input == NULL) {
            // error reading from stdin
            return 1;
        }
        bzero(argv, sizeof argv);
        split_by_arg(input, argv);
        free(input);

        operation = -1;
        for (int i = 0; *(commands[i].name) && operation == -1; i++) {
            if (strcmp(argv[0], commands[i].name) == 0) {
                operation = i;
            }
        }
        if (operation == -1) {
            // unknown command parsed
            if (strcmp(argv[0], "exit") == 0 ||
                strcmp(argv[0], "quit") == 0) {
                fprintf(stdout, "Bye\n");
                return 0;
            }
            fprintf(stderr, "The command %s is unknown.\n", argv[0]);
            continue;
        }
        if (strcmp(argv[1], "--help") == 0) {
            fprintf(stdout, "%s", commands[operation].help);
            continue;
        }
        (*commands[operation].execute)(argv);
    }
}

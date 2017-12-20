#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "stats.h"
#include "clnup.h"
#include "shrink.h"
#include <unistd.h>

/**
 *
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
 * 
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
 * 
 */
int main(void) {
    char *input;
    char argv[25][50];
    bzero(argv, sizeof argv);

    printf("This is the launch terminal of our projet.                     \n" \
           "The commands are stats, shrink, clnup and sortn.               \n" \
           "Type `<command> --help' to get more information on the command.\n" \
           ">>> ");

    for (;;) {
        input = readSTDIN();
        if (input == NULL) {
            // error reading from stdin
            return 1;
        }
        splitByArg(input, argv);

        for (int i = 0; i < 25; i++) {
            printf("[%s]", argv[i]);
        }

        break;
    }
}

/*

            case 'h':
                if (!strcmp("stats", optarg))
                {
                    printf("Write <stats> to show all informations about this folder\n");
                }
                else if (!strcmp("shrink", optarg))
                {
                    printf("Write <shrink> to compress several files of this folder\n");
                }
                else if (!strcmp("clnup", optarg))
                {
                    printf("Write <clnup> to sort files of this folder in multiple folders according the type file \n");
                }
                else if (!strcmp("sortn", optarg)){
                        printf("Write <sortn> \n");
                }
                exit(EXIT_FAILURE);
                break;
                
            run commandes
            case 'r' :
                r =0;
                break;
            default:
            exit(EXIT_FAILURE);
                break;
        }
        
        if (r==0)
        {
            printf("Enter a path :");
            scanf("%s", str);
            
            Directory exists.
            DIR* dir = opendir(str);
            
            if (dir)
            {
                printf("Launch a command :");
                scanf("%s", test);
                
                if (!strcmp("shrink", test)) {
                    char min_size[50];
                    printf("Enter the minimal compressible size :");
                    scanf("%s", min_size);
                    shrink(atoi(min_size));
                }
                else if(!strcmp("sortn", test)) {
                    //sortn();
                }
                else if(!strcmp("stats", test)) {
                    stats(str);
                }
                else if(!strcmp("clnup", test)) {
                    clnup(str);
                }
                else if(!strcmp("quit", test) ) {
                    exit(0);
                }
                else{
                    printf("This command doesn't exist ! Try with stats, shrink, clnup or sortn.More infos in readme.m file!\n");
                }
            }
            
            // Directory doesn't exist.
            else if (ENOENT == errno)
            {
                printf("Enter a correct path :");
                DIR* dir = opendir(str);
                scanf("%s", str);
            }
        }
    }
}

*/



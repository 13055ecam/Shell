#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "stats.h"
#include "clnup.h"
#include "shrink.h"

/* terminal*/
int main(void)
{
    char test[15];
    char str[BUFSIZ];
    printf("Enter a path :");
    scanf("%s", str);
    while (1) {
        /* Directory exists. */
        DIR* dir = opendir(str);
        if (dir) {
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
        } else if (ENOENT == errno) {
            // Directory not exists.
            printf("Enter a correct path :");
            DIR* dir = opendir(str);
            scanf("%s", str);
        }
    }
}


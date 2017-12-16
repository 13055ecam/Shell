#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "stats.h"
#include "clnup.h"
#include "shrink.h"
#include <unistd.h>
#include <getopt.h>



/* terminal*/
int main(int argc, char* argv[] )
{
    char test[15];
    char str[BUFSIZ];
    int option = 0;
    int h = -1;
    int r = -1;
   
    while(1){
      
        if ((option = getopt(argc, argv,"rh:h:")) != -1) {
        switch (option) {
            case 'h':
                if (!strcmp("stats", optarg)){
                        printf("Write <stats> to show all informations about this folder\n");
                }
                else if (!strcmp("shrink", optarg)){
                        printf("Write <shrink> to compress several files of this folder\n");
                }
                else if (!strcmp("clnup", optarg)){
                        printf("Write <clnup> to sort files of this folder in multiple folders according the type file \n");
                }
                else if (!strcmp("sort", optarg)){
                        printf("Write <sort> \n");
                }
                exit(EXIT_FAILURE);
                break;
            exit(EXIT_FAILURE);
            case 'r' : r =0;
                printf("Enter a path :");
                scanf("%s", str);
                break;
            default:
            exit(EXIT_FAILURE);
                break;
        }
    }
        // Help the user

        else if (r==0){
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
}



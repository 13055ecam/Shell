#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "stats.h"
#include "clnup.h"



/* terminal*/
int main(void)
{
    
    char test[15];
    char str[BUFSIZ];
    printf("Enter a path :");
    scanf("%s", str);
        while(1){
            /* Directory exists. */
            DIR* dir = opendir(str);
            if (dir){
            scanf("%s", test);
            int ret = strcmp("shrink", test);
            int ret1 = strcmp("sortn", test);
            int ret2 = strcmp("stats", test);
            int ret3 = strcmp("clnup", test);

            if (ret == 0){
                //shrink();
            }
            else if(ret1 == 0){
                //sortn();
            }
            else if(ret2 == 0){
                stats(str);
            }
            else if(ret3 == 0){
                clnup(str);
            }
        }
            /* Directory not exists. */
            else if (ENOENT == errno){
                printf("Enter a correct path :");
                DIR* dir = opendir(str);
                scanf("%s", str);
            }
        }
}


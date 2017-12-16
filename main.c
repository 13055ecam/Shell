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
    int h = -1;
    int r = -1;
   
    while(1){
        
        int option = getopt(argc, argv,"rh:hr:");
        switch (option)
        
        {
            /* Help commandes */
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
                
            /* run commandes */
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
            
            /* Directory exists. */
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



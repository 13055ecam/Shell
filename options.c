#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

/** Program to return specific informations about files
 */

rectangle a -l 12 -b 34: will calculate the area of the rectangle

void print_usage() {
    printf("Usage: --help [abcd]);
}

int main(int argc, char *argv[]) {
    int option = 0;
    int stats = -1;
    int clnup = -1;
    int shrink = -1;
    int sort = -1;

    //Specifying the expected options
    //The two options l and b expect numbers as argument
    while ((option = getopt(argc, argv,"apl:b:")) != -1) {
        switch (option) {
             case 'stats' : stats = 0;
                 break;
             case 'shrink' : shrink = 0;
                 break;
             case 'sort' : sort = 0;
                 break;
             case 'clnup' : clnup = 0;
                 break;
             default: print_usage(); 
                 exit(EXIT_FAILURE);
        }
    }

    // Help the user 
    if (stats == 0) {
       printf("Write <stats> to show all informations about this folder\n");
       }
    else if (shrink){
       printf("Write <shrink> to compress several files of this folder\n");
       }
    else if (clnup){
       printf("Write <clnup> to sort files of this folder in multiple folders according the type file \n");
    }
    else if (sort){
           printf("Write <sort>  \n");
    }
    return 0;
}

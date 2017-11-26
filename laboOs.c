#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <regex.h>
#include <inttypes.h>
#include "stats.h"
#include <wchar.h>

void shrink();
void sortn();
void cnlup();

/* terminal*/
int main(void)
{
    char test[15];
    while(1){
        scanf("%s", test);
        int ret = strcmp("shrink", test);
        int ret1 = strcmp("sortn", test);
        int ret2 = strcmp("stats", test);
        int ret3 = strcmp("cnlup", test);

        if (ret == 0){
            shrink();
        }
        else if(ret1 == 0){
            sortn();
        }
        else if(ret2 == 0){
            stats();
        }
        else if(ret3 == 0){
            cnlup();
        }
    }
}
void shrink(){};
void sortn(){};
void cnlup(){};
